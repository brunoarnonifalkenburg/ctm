#include "Assert.h"
#include <stdio.h>
#include <stdlib.h>

void ASSERT(bool condition, char* err_msg) {
    if (!condition) {
        printf("ASSERTION FAILED: %s\n", err_msg);
        exit(0);
    }
}
