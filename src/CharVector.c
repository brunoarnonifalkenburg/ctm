#include "CharVector.h"
#include <malloc.h>
#include <string.h>
#include "Assert.h"

struct CharVector {
    int   size;
    int   capacity;
    char* data;
};

CharVector* CharVector_new() {
    CharVector* vector = (CharVector*) malloc(sizeof(CharVector));
    vector->data = (char*) malloc(sizeof(char));
    vector->size = 0;
    vector->capacity = 1;
    return vector;
}

void CharVector_delete(CharVector* this) {
    free(this->data);
    free(this);
}

CharVector* CharVector_clone(CharVector* this) {
    CharVector* clone = CharVector_new();
    int i;
    for (i = 0; i < this->size; ++i) {
        CharVector_append(clone, this->data[i]);
    }
    return clone;
}

int CharVector_size(CharVector* this) {
    return this->size;
}

bool CharVector_in(CharVector* this, char c) {
    int i;
    for (i = 0; i < this->size; ++i) {
        if (this->data[i] == c) {
            return true;
        }
    }
    return false;
}

char CharVector_at(CharVector* this, int i) {
    ASSERT(0 <= i && i < this->size, "Index out of bounds");
    return this->data[i];
}

void CharVector_set(CharVector* this, int i, char c) {
    ASSERT(0 <= i && i < this->size, "Index out of bounds");
    this->data[i] = c;
}

void CharVector_append(CharVector* this, char c) {
    if (this->size == this->capacity) {
        this->capacity *= 2;
        char* new = (char*) malloc(sizeof(char) * this->capacity);
        int i;
        for (i = 0; i < this->size; ++i) {
            new[i] = this->data[i];
        }
        free(this->data);
        this->data = new;
    }
    this->data[this->size] = c;
    this->size += 1;
}

void CharVector_explodeAppend(CharVector* this, char* chars) {
    int i;
    int len = strlen(chars);
    for (i = 0; i < len; ++i) {
        CharVector_append(this, chars[i]);
    }
}

bool CharVector_uniqueElements(CharVector* this) {
    int i, j;
    int len = CharVector_size(this);
    for (i = 0; i < len; ++i) {
        for (j = i + 1; j < len; ++j) {
            if (CharVector_at(this, i) == CharVector_at(this, j)) {
                return false;
            }
        }
    }
    return true;    
}

bool CharVector_isSubset(CharVector* this, CharVector* other) {
    int i;
    bool subset = true;
    int len = CharVector_size(this);
    for (i = 0; i < len; ++i) {
        if (!CharVector_in(other, CharVector_at(this, i))) {
            subset = false;
            break;
        }
    }
    return subset;
}

void CharVector_print(CharVector* this) {
    int i;
    for (i = 0; i < this->size; ++i) {
        printf("%s", (i == 0 ? "<" : " "));
        printf("%c", CharVector_at(this, i));
        printf("%s", (i + 1 < this->size ? "," : ">"));
    }
    printf("\n");
}
