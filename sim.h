#ifndef SIM_H
#define SIM_H

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* hexin;
FILE* svgout;
FILE* resout;
    

int numins;//number of instructions
long long int ins[10000000];// ins as ints
char ins_string[10000000][32];// ins as bit strings

void yyerror(char* );
void test_hexin();

#endif
