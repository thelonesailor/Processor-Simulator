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
char mem[64000005];
int iacc,dacc;

struct INST{
  int type; 
  int Rs,Rt,Rd;
  int s,t,d;
  int Offset;
};
struct INST *decoded;


struct IF{
  int pc;
  struct INST Ins;
};

struct ID{
  int pc;
  int branch_target;
  
  int vrs,vrt,vrd;

  struct INST Ins;
};

struct EX{
  int pc;
  int aluresult;
  
  int vrs,vrt,vrd;

  int address;
  int op2;
  struct INST Ins;
};

struct MA{
  int pc;
  int vrs,vrt,vrd;

  struct INST Ins;
};


void yyerror(char* );
void print_regdump();
void print_memdump(int addr,int num);
void print_result();
void input_hexin();
void test_hexin();
void test_decode();
char * subst(char *a, int start,int num);
void llinttobinary(long long int a,int num);


void simulate();
void execute();


#endif
