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
char* svgfile;     

int numins;//number of instructions
long long int* ins;// ins as ints
char** ins_string;// ins as bit strings

int reg[35];
char mem[74000005];
int iacc,dacc,numcycles,icache;

int curr,st;
int p11,p12,p21,p22,p3;

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

//nothing for type=0
//type=[1..23]
//char * operaons[24]={"","lw","sw","add","sub","addi","and","or","ori","lui","mult","madd","nor","lb","sb","sllv","sltu","slti","sll","beq","bgez","bgtz","blez","bltz"};


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


void stalling();
void forwarding();
void step();
void printsvg();
void simulate();
void execute();
void execute2();


#endif
