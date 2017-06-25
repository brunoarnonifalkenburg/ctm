ctm
===

A Turing machine simulator

![](https://github.com/mackorone/ctm/blob/master/demo.gif)


Introduction
============

From Wikipedia:

> A Turing machine is a hypothetical device that manipulates symbols on a
> strip of tape according to a table of rules. Despite its simplicity, a
> Turing machine can be adapted to simulate the logic of any computer
> algorithm, and is particularly useful in explaining the functions of a CPU
> inside a computer.
>
> The "Turing" machine was invented in 1936 by Alan Turing who called it an
> "a-machine" (automatic machine). The Turing machine is not intended as
> practical computing technology, but rather as a hypothetical device
> representing a computing machine. Turing machines help computer scientists
> understand the limits of mechanical computation.


Building and Running
====================

    make
    bin/a.out


Features
============

Vanilla C
---------
Written in plain C - no add-ons or libraries required.

Formal Specification
--------------------
The only mechanism for creating and executing a Turing Machine is to specify its
formal parameters. This means that Turing Machine writers cannot fall into the
trap of accidentally providing functionality (using variables, etc.) that a
Turing Machine doesn't inherently have.

No-Rule rejection
----------------
If a machine encounters a state and input symbol for which it has no explicit
rule, it simply rejects the input. This allows Turing Machine writers to only
concern themselves with acceptance criteria, as opposed to having to completely
specify every case in which input is rejected.

Wildcard matching
----------------
The *WILDCARD_SYMBOL* matches against any particular input character.
This makes fully specifying each Turing Machine less cumbersome. Since the
implementation guarantees that transition function rules are checked in the
same order that they were added to the Transition Function object, one can
simply write rules for special input characters, and then use the
*WILDCARD_SYMBOL* to match all other input characters. Additionally, if the
*WILDCARD_SYMBOL* is specified as the output character for a particular rule,
the input character is used as the output character. This allows us to traverse
a tape while wildcard matching and leaving the tape unmodified. See the
`GoToEnd` machine for an example of this technique.

Valgrind approved
-----------------
The simulator was rigorously tested and verified with valgrind.


Creating your own machine
=========================

To create your own Turing Machine:

1. Write a `createMachine` function for the machine. Put that function in its
own `.c` file in the `machines` directory.
1. Put a declaration of your `createMachine` function in the `CreateMachines.h`
file.
1. Create, run, and cleanup the machine in the `Main.c` file


Contact
=======
Mack Ward - mward4@buffalo.edu
