#ifndef SIM_H
#define SIM_H

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

FILE* hexin;
FILE* svgout;
FILE* resout;
    

int numins;//number of instructions
long long int* ins;// ins as ints
char** ins_string;// ins as bit strings

int reg[35];
char mem[74000005];
int iacc,dacc,numcycles;

int curr;

struct INST{
  int type; 
  int Rs,Rt,Rd;
  int s,t,d;
  int Offset;
  int invalid;
  int stall;
  int id;
};
struct INST *decoded;


struct IF{
  struct INST Ins;
};

struct ID{
  int branch_target;
  
  int vrs,vrt,vrd;

  struct INST Ins;
};

struct EX{
  int vrs,vrt,vrd;

  long long int address;
  struct INST Ins;
};

struct MA{
  int vrs,vrt,vrd;

  struct INST Ins;
};

struct IF inf[2];
struct ID id[2];
struct EX ex[2];
struct MA ma[2];


void yyerror(char* );
void print_regdump();
void print_memdump(int addr,int num);
void print_result();
void input_hexin();
void test_hexin();
void test_decode();
char * subst(char *a, int start,int num);
void llinttobinary(long long int a,int num);

int yyparse();

void step();
void printsvg();
void simulate();
void execute();
void execute2();


#endif
