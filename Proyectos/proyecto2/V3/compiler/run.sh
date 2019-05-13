#!/bin/bash
flex Compiler.l
yacc -d Compiler.y
g++ -o Runable lex.yy.c y.tab.c
./Runable