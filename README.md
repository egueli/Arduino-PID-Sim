Run Arduino-PID tester without an Arduino
=========================================

I made this repo because I wanted to run br3ttb's [Arduino
PID](https://github.com/br3ttb/Arduino-PID-Library) library and its
[tester](https://github.com/br3ttb/arduino-pid-library-tester) without physically
have an Arduino, and running all the code on an x86 machine (Mac OS or another
system with `llvm`) instead.

The final objective is to compare the tester's output with its [Kotlin
port](https://github.com/egueli/Kotlin-PID-Library).

The repo contains a copy of the PID tester, modified to run in simulation time,
a minimal Arduino SDK and a makefile to compile the program and produce the
output.

In order to be built, it requires [my fork of the PID
library](https://github.com/egueli/Arduino-PID-Library) to be cloned in a
sibling directory named `Arduino-PID-Library`. See the makefile for reference.
