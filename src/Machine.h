#ifndef TM_MACHINE
#define TM_MACHINE

#include "Bool.h"
#include "CharVector.h"
#include "StringVector.h"
#include "TransitionFunction.h"

typedef struct Machine Machine;

Machine* Machine_new(char* name, StringVector* states, CharVector* input_alphabet,
                     CharVector* tape_alphabet, char* initial_state,
                     StringVector* accepting_states, TransitionFunction* function);

void Machine_delete(Machine* this);

const char* Machine_getName(Machine* this);
                     
bool Machine_run(Machine* this, char* input, bool show_visual, int ms_delay);

#endif // TM_MACHINE
