#include "../Machine.h"
#include <malloc.h>
#include "../Symbols.h"

Machine* createMachine_shift() {

    StringVector* states = StringVector_new();
    StringVector_append(states, "A");
    StringVector_append(states, "B");
    StringVector_append(states, "C");
    StringVector_append(states, "Accept");
    StringVector_append(states, "FindEndLeft");
    StringVector_append(states, "FindEndRight");
    StringVector_append(states, "FoundEnd");

    CharVector* input_alphabet = CharVector_new();
    CharVector_explodeAppend(input_alphabet, "abc");

    CharVector* tape_alphabet = CharVector_clone(input_alphabet);
    CharVector_append(tape_alphabet, BLANK_SYMBOL);

    char* initial_state = "FindEndRight";

    StringVector* accepting_states = StringVector_new();
    StringVector_append(accepting_states, "Accept");

    TransitionFunction* function = TransitionFunction_new();

    TransitionFunction_addRule(function, "FindEndRight",          'a', "FindEndRight",          'a', RIGHT);
    TransitionFunction_addRule(function, "FindEndRight",          'b', "FindEndRight",          'b', RIGHT);
    TransitionFunction_addRule(function, "FindEndRight",          'c', "FindEndRight",          'c', RIGHT);

    TransitionFunction_addRule(function,  "FindEndLeft",          'a',  "FindEndLeft",          'a',  LEFT);
    TransitionFunction_addRule(function,  "FindEndLeft",          'b',  "FindEndLeft",          'b',  LEFT);
    TransitionFunction_addRule(function,  "FindEndLeft",          'c',  "FindEndLeft",          'c',  LEFT);

    TransitionFunction_addRule(function, "FindEndRight", BLANK_SYMBOL,     "FoundEnd", BLANK_SYMBOL,  LEFT);
    TransitionFunction_addRule(function,  "FindEndLeft", BLANK_SYMBOL,     "FoundEnd", BLANK_SYMBOL,  LEFT);
    TransitionFunction_addRule(function,     "FoundEnd", BLANK_SYMBOL,       "Accept", BLANK_SYMBOL, RIGHT);

    TransitionFunction_addRule(function,     "FoundEnd",          'a',            "A", BLANK_SYMBOL, RIGHT);
    TransitionFunction_addRule(function,            "A", BLANK_SYMBOL,  "FindEndLeft",          'a',  LEFT);
    TransitionFunction_addRule(function,     "FoundEnd",          'b',            "B", BLANK_SYMBOL, RIGHT);
    TransitionFunction_addRule(function,            "B", BLANK_SYMBOL,  "FindEndLeft",          'b',  LEFT);
    TransitionFunction_addRule(function,     "FoundEnd",          'c',            "C", BLANK_SYMBOL, RIGHT);
    TransitionFunction_addRule(function,            "C", BLANK_SYMBOL,  "FindEndLeft",          'c',  LEFT);

    Machine* machine = Machine_new("Shift", states, input_alphabet, tape_alphabet,
                                   initial_state, accepting_states, function);

    StringVector_delete(states);
    CharVector_delete(input_alphabet);
    CharVector_delete(tape_alphabet);
    StringVector_delete(accepting_states);
    TransitionFunction_delete(function);

    return machine;
}
