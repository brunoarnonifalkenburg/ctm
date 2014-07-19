#ifndef TM_STRINGVECTOR
#define TM_STRINGVECTOR

#include "Bool.h"

typedef struct StringVector StringVector;

StringVector* StringVector_new();
void StringVector_delete(StringVector* this);
StringVector* StringVector_clone(StringVector* this);

int StringVector_size(StringVector* this);
bool StringVector_in(StringVector* this, char* str);
char* StringVector_at(StringVector* this, int i);
void StringVector_set(StringVector* this, int i, char* str);
void StringVector_append(StringVector* this, char* str);
bool StringVector_uniqueElements(StringVector* this);
bool StringVector_isSubset(StringVector* this, StringVector* other);
void StringVector_print(StringVector* this);

#endif // TM_STRINGVECTOR
