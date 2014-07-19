#include "TransitionFunction.h"
#include <malloc.h>
#include <string.h>
#include "Assert.h"
#include "Direction.h"
#include "Symbols.h"

typedef struct {
    char* from_state;
    char in_char;
    char* to_state;
    char out_char;
    DIRECTION dir;
} Transition;

Transition* Transition_new(char* from_state, char in_char,
                           char* to_state, char out_char, DIRECTION dir) {
    Transition* transition = (Transition*) malloc(sizeof(Transition));
    transition->from_state = (char*) malloc(strlen(from_state) + 1);
    strcpy(transition->from_state, from_state);
    transition->to_state = (char*) malloc(strlen(to_state) + 1);
    strcpy(transition->to_state, to_state);
    transition->in_char = in_char;
    transition->out_char = out_char;
    transition->dir = dir;
    return transition;
};

void Transition_delete(Transition* transition) {
    free(transition->from_state);
    free(transition->to_state);
    free(transition);
};

struct TransitionFunction {
    int size;
    int capacity;
    Transition** data;
};

TransitionFunction* TransitionFunction_new() {
    TransitionFunction* vector = (TransitionFunction*) malloc(sizeof(TransitionFunction));
    vector->data = (Transition**) malloc(sizeof(Transition*));
    vector->size = 0;
    vector->capacity = 1;
    return vector;
}

void TransitionFunction_delete(TransitionFunction* this) {
    int i;
    for (i = 0; i < this->size; ++i) {
        Transition_delete(this->data[i]);
    }
    free(this->data);
    free(this);
}

TransitionFunction* TransitionFunction_clone(TransitionFunction* this) {
    TransitionFunction* clone = TransitionFunction_new();
    int i;
    for (i = 0; i < this->size; ++i) {
        TransitionFunction_addRule(clone, this->data[i]->from_state, this->data[i]->in_char,
            this->data[i]->to_state, this->data[i]->out_char, this->data[i]->dir);
    }
    return clone;
}

void TransitionFunction_addRule(TransitionFunction* this, char* from_state,
                                char in_char, char* to_state, char out_char,
                                DIRECTION dir) {
    int i;
    if (this->size == this->capacity) {
        this->capacity *= 2;
        Transition** new = (Transition**) malloc(sizeof(Transition*) * this->capacity);
        for (i = 0; i < this->size; ++i) {
            new[i] = this->data[i];
        }
        free(this->data);
        this->data = new;
    }
    this->data[this->size] = Transition_new(from_state, in_char, to_state, out_char, dir);
    this->size += 1;
}

void TransitionFunction_validateAgainst(TransitionFunction* this, StringVector* states,
                            StringVector* accepting_states, CharVector* tape_alphabet) {
    int i, j;
    for (i = 0; i < this->size; ++i) {
        Transition* transition = this->data[i];
        ASSERT(CharVector_in(tape_alphabet, transition->in_char),
               "Invalid function - in_char not in tape alphabet");
        ASSERT(CharVector_in(tape_alphabet, transition->out_char),
               "Invalid function - out_char not in tape alphabet");
        ASSERT(transition->dir == LEFT || transition->dir == RIGHT,
               "Invalid function - invalid direction in function rule");
        ASSERT(StringVector_in(states, transition->from_state),
               "Invalid function - from_state not in the set of states");
        ASSERT(!StringVector_in(accepting_states, transition->from_state),
               "Invalid function - from_state in the set of accepting states");
        ASSERT(StringVector_in(states, transition->to_state),
               "Invalid function - to_state not in the set of states");
        for (j = i + 1; j < this->size; ++j) {
            Transition* other = this->data[j];
            ASSERT(strcmp(transition->from_state, other->from_state) != 0 || transition->in_char != other->in_char,
                   "Invalid function - two rules have the same from-state and in-char");
        }
    }
}

void TransitionFunction_print(TransitionFunction* this) {
    int i;
    for (i = 0; i < this->size; ++i) {
        printf("(%s, %c) -> (%s, %c, %s)\n", this->data[i]->from_state, this->data[i]->in_char,
            this->data[i]->to_state, this->data[i]->out_char, (this->data[i]->dir == LEFT ? "L" : "R"));
    }
}

TransitionFunctionResult TransitionFunction_getResult(TransitionFunction* this, char* from_state, char in_char) {

    bool matchState;
    bool matchSymbol;
    bool matchWildcard;

    int i = 0;
    while (i < this->size) {
        matchState    = (strcmp(this->data[i]->from_state, from_state) == 0);
        matchSymbol   = (this->data[i]->in_char == in_char);
        matchWildcard = (this->data[i]->in_char == WILDCARD_SYMBOL);
        if (matchState && (matchSymbol || matchWildcard)) {
            break;
        }
        ++i;
    }

    TransitionFunctionResult result;
    if (i == this->size) {
        result.terminate = true;
    }
    else {
        result.to_state = this->data[i]->to_state;
        if (this->data[i]->out_char == WILDCARD_SYMBOL) {
            result.out_char = in_char;
        }
        else {
            result.out_char = this->data[i]->out_char;
        }
        result.dir = this->data[i]->dir;
        result.terminate = false;
    }
    return result;
}
