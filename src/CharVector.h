#ifndef TM_CHARVECTOR
#define TM_CHARVECTOR

#include "Bool.h"

typedef struct CharVector CharVector;

CharVector* CharVector_new();
void CharVector_delete(CharVector* this);
CharVector* CharVector_clone(CharVector* this);

int CharVector_size(CharVector* this);
bool CharVector_in(CharVector* this, char c);
char CharVector_at(CharVector* this, int i);
void CharVector_set(CharVector* this, int i, char c);
void CharVector_append(CharVector* this, char c);
void CharVector_explodeAppend(CharVector* this, char* chars);
bool CharVector_uniqueElements(CharVector* this);
bool CharVector_isSubset(CharVector* this, CharVector* other);
void CharVector_print(CharVector* this);

#endif // TM_CHARVECTOR
