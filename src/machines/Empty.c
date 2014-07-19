#include "../Machine.h"
#include <malloc.h>
#include "../Symbols.h"

Machine* createMachine_empty() {

    StringVector* states = StringVector_new();
    StringVector_append(states, "Initial");
    StringVector_append(states, "Accept");

    CharVector* input_alphabet = CharVector_new();
    CharVector_explodeAppend(input_alphabet, "abc");

    CharVector* tape_alphabet = CharVector_clone(input_alphabet);
    CharVector_append(tape_alphabet, BLANK_SYMBOL);

    char* initial_state = "Initial";

    StringVector* accepting_states = StringVector_new();
    StringVector_append(accepting_states, "Accept");

    TransitionFunction* function = TransitionFunction_new();
    TransitionFunction_addRule(function, "Initial", BLANK_SYMBOL, "Accept", BLANK_SYMBOL, RIGHT);

    Machine* machine = Machine_new("Empty", states, input_alphabet, tape_alphabet,
                                   initial_state, accepting_states, function);

    StringVector_delete(states);
    CharVector_delete(input_alphabet);
    CharVector_delete(tape_alphabet);
    StringVector_delete(accepting_states);
    TransitionFunction_delete(function);

    return machine;
}
