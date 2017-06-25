#include <stdio.h>
#include "Bool.h"
#include "CreateMachine.h"
#include "Machine.h"

void run(Machine* machine, char* input) {
    printf("Executing \"%s\" on input \"%s\"\n", Machine_getName(machine), input);
    bool accepted = Machine_run(machine, input, false, 0);
    printf( accepted ? "Accepted\n\n" : "Rejected\n\n" );
}

void runAndPrint(Machine* machine, char* input) {
    printf("Executing \"%s\" on input \"%s\"\n", Machine_getName(machine), input);
    bool accepted = Machine_run(machine, input, true, 150);
    printf( accepted ? "\nAccepted\n\n" : "\nRejected\n\n" );
}

int main(int argc, char** argv) {

    Machine* empty = createMachine_empty();
    Machine* goToEnd = createMachine_goToEnd();
    Machine* uniform = createMachine_uniform();
    Machine* shift = createMachine_shift();
    Machine* palindrome = createMachine_palindrome();

    runAndPrint(empty, "");
    runAndPrint(empty, "aabb");
    runAndPrint(goToEnd, "abcabcabcabc");
    runAndPrint(goToEnd, "aabb");
    runAndPrint(uniform, "aaaaaaa");
    runAndPrint(uniform, "aaaabaa");
    runAndPrint(shift, "aabc");
    runAndPrint(shift, "abcabcabca");
    runAndPrint(palindrome, "");
    runAndPrint(palindrome, "aaabbcaaa");
    runAndPrint(palindrome, "aabacbcabaa");

    Machine_delete(empty);
    Machine_delete(goToEnd);
    Machine_delete(uniform);
    Machine_delete(shift);
    Machine_delete(palindrome);

    return 0;
}
