#!/bin/bash
lex lsd12.l
bison -dty lsd12.y
gcc *.c
