#include "../Machine.h"
#include <malloc.h>
#include "../Symbols.h"

Machine* createMachine_uniform() {

    StringVector* states = StringVector_new();
    StringVector_append(states, "Initial");
    StringVector_append(states, "A");
    StringVector_append(states, "B");
    StringVector_append(states, "C");
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
    TransitionFunction_addRule(function, "Initial",          'a',      "A",          'a', RIGHT);
    TransitionFunction_addRule(function, "Initial",          'b',      "B",          'b', RIGHT);
    TransitionFunction_addRule(function, "Initial",          'c',      "C",          'c', RIGHT);
    TransitionFunction_addRule(function,       "A",          'a',      "A",          'a', RIGHT);
    TransitionFunction_addRule(function,       "B",          'b',      "B",          'b', RIGHT);
    TransitionFunction_addRule(function,       "C",          'c',      "C",          'c', RIGHT);
    TransitionFunction_addRule(function,       "A", BLANK_SYMBOL, "Accept", BLANK_SYMBOL, RIGHT);
    TransitionFunction_addRule(function,       "B", BLANK_SYMBOL, "Accept", BLANK_SYMBOL, RIGHT);
    TransitionFunction_addRule(function,       "C", BLANK_SYMBOL, "Accept", BLANK_SYMBOL, RIGHT);

    Machine* machine = Machine_new("Uniform", states, input_alphabet, tape_alphabet,
                                   initial_state, accepting_states, function);

    StringVector_delete(states);
    CharVector_delete(input_alphabet);
    CharVector_delete(tape_alphabet);
    StringVector_delete(accepting_states);
    TransitionFunction_delete(function);

    return machine;
}
