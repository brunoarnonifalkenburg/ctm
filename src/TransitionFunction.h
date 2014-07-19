#ifndef TM_TRANSITIONFUNCTION
#define TM_TRANSITIONFUNCTION

#include "Bool.h"
#include "CharVector.h"
#include "Direction.h"
#include "StringVector.h"

typedef struct TransitionFunction TransitionFunction;

TransitionFunction* TransitionFunction_new();
void TransitionFunction_delete(TransitionFunction* this);
TransitionFunction* TransitionFunction_clone(TransitionFunction* this);

void TransitionFunction_addRule(TransitionFunction* this, char* from_state,
                                char in_char, char* to_state, char out_char,
                                DIRECTION dir);

void TransitionFunction_validateAgainst(TransitionFunction* this, StringVector* states,
                            StringVector* accepting_states, CharVector* tape_alphabet);

void TransitionFunction_print(TransitionFunction* this);

typedef struct {
    char*       to_state;
    char        out_char;
    DIRECTION   dir;
    bool        terminate;
} TransitionFunctionResult;

TransitionFunctionResult TransitionFunction_getResult(TransitionFunction* this, char* from_state, char in_char);

#endif // TM_TRANSITIONFUNCTION
