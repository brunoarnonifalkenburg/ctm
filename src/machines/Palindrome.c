#include "../Machine.h"
#include <malloc.h>
#include "../Symbols.h"

Machine* createMachine_palindrome() {

    StringVector* states = StringVector_new();
    StringVector_append(states, "New");
    StringVector_append(states, "Next");
    StringVector_append(states, "Accept");
    StringVector_append(states, "Reject");
    StringVector_append(states, "A");
    StringVector_append(states, "B");
    StringVector_append(states, "C");
    StringVector_append(states, "EndA");
    StringVector_append(states, "EndB");
    StringVector_append(states, "EndC");

    CharVector* input_alphabet = CharVector_new();
    CharVector_append(input_alphabet, 'a');
    CharVector_append(input_alphabet, 'b');
    CharVector_append(input_alphabet, 'c');

    CharVector* tape_alphabet = CharVector_clone(input_alphabet);
    CharVector_append(tape_alphabet, BLANK_SYMBOL);
    CharVector_append(tape_alphabet, WILDCARD_SYMBOL);
    CharVector_append(tape_alphabet, 'X');

    char* initial_state = "New";

    StringVector* accepting_states = StringVector_new();
    StringVector_append(accepting_states, "Accept");

    TransitionFunction* function = TransitionFunction_new();

    // Get a new character to inspect
    TransitionFunction_addRule(function,     "New",    BLANK_SYMBOL, "Accept", BLANK_SYMBOL, RIGHT);
    TransitionFunction_addRule(function,     "New",             'X', "Accept",          'X', RIGHT);
    TransitionFunction_addRule(function,     "New",             'a',      "A",          'X', RIGHT);
    TransitionFunction_addRule(function,     "New",             'b',      "B",          'X', RIGHT);
    TransitionFunction_addRule(function,     "New",             'c',      "C",          'X', RIGHT);

    // Now find the end character
    TransitionFunction_addRule(function,       "A",    BLANK_SYMBOL,   "EndA",    BLANK_SYMBOL, LEFT);
    TransitionFunction_addRule(function,       "B",    BLANK_SYMBOL,   "EndB",    BLANK_SYMBOL, LEFT);
    TransitionFunction_addRule(function,       "C",    BLANK_SYMBOL,   "EndC",    BLANK_SYMBOL, LEFT);
    TransitionFunction_addRule(function,       "A",             'X',   "EndA",             'X', LEFT);
    TransitionFunction_addRule(function,       "B",             'X',   "EndB",             'X', LEFT);
    TransitionFunction_addRule(function,       "C",             'X',   "EndC",             'X', LEFT);
    TransitionFunction_addRule(function,       "A", WILDCARD_SYMBOL,      "A", WILDCARD_SYMBOL, RIGHT);
    TransitionFunction_addRule(function,       "B", WILDCARD_SYMBOL,      "B", WILDCARD_SYMBOL, RIGHT);
    TransitionFunction_addRule(function,       "C", WILDCARD_SYMBOL,      "C", WILDCARD_SYMBOL, RIGHT);

    // If the character prior to the end is uppercase, we've checked every character
    TransitionFunction_addRule(function,    "EndA",             'X', "Accept",          'X', RIGHT);
    TransitionFunction_addRule(function,    "EndB",             'X', "Accept",          'X', RIGHT);
    TransitionFunction_addRule(function,    "EndC",             'X', "Accept",          'X', RIGHT);

    // If the character prior to the end is lowercase, we still have characters to check
    TransitionFunction_addRule(function,    "EndA",             'a',   "Next",          'X', LEFT);
    TransitionFunction_addRule(function,    "EndB",             'b',   "Next",          'X', LEFT);
    TransitionFunction_addRule(function,    "EndC",             'c',   "Next",          'X', LEFT);

    // Proceed to the beginning again so that we can check the next character
    TransitionFunction_addRule(function,    "Next",             'a',   "Next",          'a', LEFT);
    TransitionFunction_addRule(function,    "Next",             'b',   "Next",          'b', LEFT);
    TransitionFunction_addRule(function,    "Next",             'c',   "Next",          'c', LEFT);

    // Once we've found the beginning, check a new character
    TransitionFunction_addRule(function,    "Next",             'X',    "New",          'X', RIGHT);

    Machine* machine = Machine_new("Palindrome", states, input_alphabet, tape_alphabet,
                                   initial_state, accepting_states, function);

    StringVector_delete(states);
    CharVector_delete(input_alphabet);
    CharVector_delete(tape_alphabet);
    StringVector_delete(accepting_states);
    TransitionFunction_delete(function);

    return machine;
}
