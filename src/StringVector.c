#include "StringVector.h"
#include <malloc.h>
#include <string.h>
#include "Assert.h"

struct StringVector {
    int    size;
    int    capacity;
    char** data;
};

StringVector* StringVector_new() {
    StringVector* vector = (StringVector*) malloc(sizeof(StringVector));
    vector->data = (char**) malloc(sizeof(char*));
    vector->size = 0;
    vector->capacity = 1;
    return vector;
}

void StringVector_delete(StringVector* this) {
    int i;
    for (i = 0; i < this->size; ++i) {
        free(this->data[i]);
    }
    free(this->data);
    free(this);
}

StringVector* StringVector_clone(StringVector* this) {
    StringVector* clone = StringVector_new();
    int i;
    for (i = 0; i < this->size; ++i) {
        StringVector_append(clone, this->data[i]);
    }
    return clone;
}

int StringVector_size(StringVector* this) {
    return this->size;
}

bool StringVector_in(StringVector* this, char* str) {
    int i;
    for (i = 0; i < this->size; ++i) {
        if (strcmp(this->data[i], str) == 0) {
            return true;
        }
    }
    return false;
}

char* StringVector_at(StringVector* this, int i) {
    ASSERT(0 <= i && i < this->size, "Index out of bounds");
    return this->data[i];
}

void StringVector_set(StringVector* this, int i, char* str) {
    ASSERT(0 <= i && i < this->size, "Index out of bounds");
    this->data[i] = str;
}

void StringVector_append(StringVector* this, char* str) {
    if (this->size == this->capacity) {
        this->capacity *= 2;
        char** new = (char**) malloc(sizeof(char*) * this->capacity);
        int i;
        for (i = 0; i < this->size; ++i) {
            new[i] = this->data[i];
        }
        free(this->data);
        this->data = new;
    }
    this->data[this->size] = (char*) malloc(strlen(str) + 1);
    strcpy(this->data[this->size], str);
    this->size += 1;
}

bool StringVector_uniqueElements(StringVector* this) {
    int i, j;
    bool unique = true;
    int len = StringVector_size(this);
    for (i = 0; i < len; ++i) {
        for (j = i + 1; j < len; ++j) {
            if (strcmp(StringVector_at(this, i), StringVector_at(this, j)) == 0) {
                unique = false;
                break;
            }
        }
        if (!unique) {
            break;
        }
    }
    return unique;
}

bool StringVector_isSubset(StringVector* this, StringVector* other) {
    int i;
    bool subset = true;
    int len = StringVector_size(this);
    for (i = 0; i < len; ++i) {
        if (!StringVector_in(other, StringVector_at(this, i))) {
            subset = false;
            break;
        }
    }
    return subset;
}

void StringVector_print(StringVector* this) {
    int i;
    for (i = 0; i < this->size; ++i) {
        printf("%s", (i == 0 ? "<" : " "));
        printf("%s", StringVector_at(this, i));
        printf("%s", (i + 1 < this->size ? "," : ">"));
    }
    printf("\n");
}
