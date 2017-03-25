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
long long int* ins;// ins as ints
char** ins_string;// ins as bit strings

int reg[35];
char mem[64000005];


void yyerror(char* );
void print_regdump();
void print_memdump(int addr,int num);
void input_hexin();
void test_hexin();
void test_decode();
char * subst(char *a, int start,int num);
void llinttobinary(long long int a,int num);


void simulate();
void execute();


#endif
