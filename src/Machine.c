#include "Machine.h"
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "Assert.h"
#include "CharVector.h"
#include "Symbols.h"


struct Machine {
    char*               name;
    StringVector*       states;
    CharVector*         input_alphabet;
    CharVector*         tape_alphabet;
    char*               initial_state;
    char*               current_state;
    StringVector*       accepting_states;
    TransitionFunction* function;
    int                 head_position;
    CharVector*         tape;
};

void Machine_validateStates(Machine* this) {

    // The set of machine states must be non-empty
    ASSERT(0 < StringVector_size(this->states), "Invalid number of states");

    // The set of machine states must contain unique elements
    bool uniqueStates = StringVector_uniqueElements(this->states);
    ASSERT(uniqueStates, "The StringVector corresponding to the set of all machine states includes duplicates");

    // The set of accepting states must be unique
    bool uniqueAcceptingStates = StringVector_uniqueElements(this->accepting_states);
    ASSERT(uniqueAcceptingStates, "The StringVector corresponding to the set of all accepting states includes duplicates");
    
    // The set of accepting states must be a subset of the set of machine states
    bool subset = StringVector_isSubset(this->accepting_states, this->states);
    ASSERT(subset, "The set of accepting states is not a subset of the set of machine states");

    // Initial state must be in the set of all machine states
    bool validInitialState = StringVector_in(this->states, this->initial_state);
    ASSERT(validInitialState, "Initial state is not in the set of all machine states");
}

void Machine_validateAlphabets(Machine* this) {

    // Tape alphabet must be non-empty
    ASSERT(0 < CharVector_size(this->tape_alphabet), "Invalid empty tape alphabet");

    // The BLANK_SYMBOL must be in tape alphabet
    ASSERT(CharVector_in(this->tape_alphabet, BLANK_SYMBOL), "Tape alphabet doesn't contain blank symbol");

    // The BLANK_SYMBOL must not be in the input alphabet
    ASSERT(!CharVector_in(this->input_alphabet, BLANK_SYMBOL), "Input alphabet contains blank symbol");

    // The WILDCARD_SYMBOL must not be in the input alphabet
    ASSERT(!CharVector_in(this->input_alphabet, WILDCARD_SYMBOL), "Input alphabet contains wildcard symbol");

    // Characters in the tape alphabet vector must be unique
    bool uniqueTapeAlphabet = CharVector_uniqueElements(this->tape_alphabet);
    ASSERT(uniqueTapeAlphabet, "The CharVector corresponding to the tape alphabet includes duplicates");
    
    // Characters in the input alphabet vector must be unique
    bool uniqueInputAlphabet = CharVector_uniqueElements(this->input_alphabet);
    ASSERT(uniqueInputAlphabet, "The CharVector corresponding to the input alphabet includes duplicates");
    
    // The input alphabet must be a strict subset of the tape alphabet
    bool subset = CharVector_isSubset(this->input_alphabet, this->tape_alphabet);
    ASSERT(subset, "Input alphabet is not a subset of the tape alphabet");
}

void Machine_validate(Machine* this) {

    // Since the states and alphabets are given directly to the machine, we can
    // perform validation on them from with the machine "class"
    Machine_validateStates(this);
    Machine_validateAlphabets(this);

    // Here, we remain ignorant to the actual rules of the transition function.
    // Thus we have to rely on the transition function to validate or
    // invalidate itself, based on the states and alphabets given.
    TransitionFunction_validateAgainst(this->function, this->states, this->accepting_states, this->tape_alphabet);
}

void Machine_print(Machine* this, int ms_delay) {

    int i;
    bool twoLine = false;
    bool spaces = true;

    if (twoLine) {
        printf(":");
        for (i = 0; i < CharVector_size(this->tape); ++i) {
            printf("%c", CharVector_at(this->tape, i));
        }
        printf("\n:");
        for (i = 0; i < this->head_position; ++i) {
            printf(" ");
        }
        printf("%c\n\n", TAPEHEAD_SYMBOL);
    }
    else {
        printf("\r\033[K|");
        for (i = 0; i < this->head_position; ++i) {
            if (spaces) {
                printf(" ");
            }
            printf("%c", CharVector_at(this->tape, i));
        }
        printf("%c", TAPEHEAD_SYMBOL);
        for (i = this->head_position; i < CharVector_size(this->tape); ++i) {
            printf("%c", CharVector_at(this->tape, i));
            if (spaces && i + 1 < CharVector_size(this->tape)) {
                printf(" ");
            }
        }
    }

    fflush(stdout);
    usleep(1000 * ms_delay);
}

Machine* Machine_new(char* name, StringVector* states, CharVector* input_alphabet,
                     CharVector* tape_alphabet, char* initial_state,
                     StringVector* accepting_states, TransitionFunction* function) {

    Machine* machine = (Machine*) malloc(sizeof(Machine));
    machine->name = (char*) malloc(strlen(name) + 1);
    strcpy(machine->name, name);
    machine->states = StringVector_clone(states);
    machine->input_alphabet = CharVector_clone(input_alphabet);
    machine->tape_alphabet = CharVector_clone(tape_alphabet);
    machine->initial_state = (char*) malloc(strlen(initial_state) + 1);
    strcpy(machine->initial_state, initial_state);
    machine->current_state = (char*) malloc(strlen(initial_state) + 1);
    strcpy(machine->current_state, initial_state);
    machine->accepting_states = StringVector_clone(accepting_states);
    machine->function = TransitionFunction_clone(function);
    machine->head_position = 0;
    machine->tape = CharVector_new();

    Machine_validate(machine);

    return machine;
}

void Machine_delete(Machine* this) {
    free(this->name);
    StringVector_delete(this->states);
    CharVector_delete(this->input_alphabet);
    CharVector_delete(this->tape_alphabet);
    free(this->initial_state);
    free(this->current_state);
    StringVector_delete(this->accepting_states);
    TransitionFunction_delete(this->function);
    CharVector_delete(this->tape);
    free(this);
}

const char* Machine_getName(Machine* this) {
    return this->name;
}
                     
bool Machine_run(Machine* this, char* input, bool show_visual, int ms_delay) {

    // Reset the machine
    this->head_position = 0;
    CharVector_delete(this->tape);
    this->tape = CharVector_new();
    free(this->current_state);
    this->current_state = (char*) malloc(strlen(this->initial_state) + 1);
    strcpy(this->current_state, this->initial_state);

    int i;
    int len = strlen(input);
    for (i = 0; i < len; ++i) {
        ASSERT(CharVector_in(this->input_alphabet, input[i]), "Invalid input - input symbol not in input alphabet");
        CharVector_append(this->tape, input[i]);
    }

    // Execute the simulation
    while (!StringVector_in(this->accepting_states, this->current_state)) {

        if (show_visual) {
            Machine_print(this, ms_delay);
        }

        if (this->head_position == CharVector_size(this->tape)) {
            CharVector_append(this->tape, BLANK_SYMBOL);
        }

        TransitionFunctionResult result
            = TransitionFunction_getResult(this->function, this->current_state,
                                           CharVector_at(this->tape, this->head_position));
        
        if (result.terminate) {
            return false;
        }

        free(this->current_state);
        this->current_state = (char*) malloc(strlen(result.to_state) + 1);
        strcpy(this->current_state, result.to_state);
        CharVector_set(this->tape, this->head_position, result.out_char);
        this->head_position += (result.dir == RIGHT ? 1 : (0 < this->head_position ? -1 : 0));
    }

    return true;
}
