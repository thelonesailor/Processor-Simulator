%{
#include "y.tab.h"
#include "sim.h"
%}
sp [ \t]+
natural [0-9]+
hex [0-9A-F]+
%s TERMINAL1
%s TEMP
%s value
%s valuetemp
%s EXPECTINGEND
%s ERR
%%
[ \t]+			{/*printf("Consuming space - \"%s\"\n",yytext);*/}
<INITIAL>"memdump"		{  /*printf("Intial = \"%s\"\n",yytext);*/BEGIN TEMP; return MEMDUMP;}
<INITIAL>"regdump"		 {  /*printf("Intial = \"%s\"\n",yytext);*/BEGIN EXPECTINGEND; return REGDUMP;}
<INITIAL>"run"		 {  /*printf("Intial = \"%s\"\n",yytext);*/BEGIN EXPECTINGEND; return GOTOEND;}
<INITIAL>"step"		 {  /*printf("Intial = \"%s\"\n",yytext);*/BEGIN EXPECTINGEND;/*printf("2\n");*/ return STEP;}
<INITIAL>("quit"|"QUIT"|"exit"|"EXIT")	{  /*printf("Intial = \"%s\"\n",yytext);*/BEGIN EXPECTINGEND;/*printf("2\n");*/ return QUIT;}
<TEMP>("0x"|"0X")  { /*printf("Consumed - \"%s\"\n",yytext);*/BEGIN TERMINAL1; }
<TEMP>[0-9]+	  { yylval.addr=atoi(yytext); /*printf("TEMP = \"%s\"\n",yytext);*/BEGIN valuetemp;/*printf("4\n");*/ return ADDR;}

<TERMINAL1>[0-9A-Fa-f]+	  { yylval.addr=(int)strtol(yytext, NULL, 16); /*printf("T1 = \"%s\"\n",yytext);*/BEGIN valuetemp;/*printf("4\n");*/ return ADDR;}

<valuetemp>("0x"|"0X") { /*	printf("Val = \"%s\"\n",yytext);*/BEGIN value;/*printf("8\n");*/ }
<valuetemp>[0-9]+	{ yylval.num=atoi(yytext);/*printf("Val = \"%s\"\n",yytext);*/BEGIN EXPECTINGEND;/*printf("8\n");*/ return NUM; }

<value>[0-9A-Fa-f]+		 { yylval.num=(int)strtol(yytext, NULL, 16);/*	printf("Val = \"%s\"\n",yytext);*/BEGIN EXPECTINGEND;/*printf("8\n");*/ return NUM; }

<TEMP>[^ xX\t\n]* {/* printf("Err match = \"%s\"\n",yytext);*/ BEGIN ERR;}
<value>[^ \t\n]* {/* printf("Err match = \"%s\"\n",yytext);*/ BEGIN ERR;}
<valuetemp>[^ xX\t\n]* {/* printf("Err match = \"%s\"\n",yytext);*/ BEGIN ERR;}
<ERR>[^ \t\n]* {/* printf("Err match = \"%s\"\n",yytext);*/ BEGIN ERR;}
<INITIAL>[^ \t\n]* {/* printf("Err match = \"%s\"\n",yytext);*/BEGIN ERR;}
<TERMINAL1>[^ \t\n]* {/* printf("Err match = \"%s\"\n",yytext);*/BEGIN ERR;}
<EXPECTINGEND>[\n] {/*printf("Matched End\n");*/BEGIN INITIAL;/*printf("12\n");*/ /*printf("%d\n",yylineno);*/yylineno++;return END;}
. 					{yyerror("Error - Format of input is wrong 2");}
[\n] {/*printf("Matched stray \"\\n\"\n");*/ BEGIN INITIAL; fprintf(stderr,"\tSyntax Error in input line %d\n",yylineno);/*printf("%d\n",yylineno);*/yylineno++; return er;}
%%

int yywrap (void) 
{return 1;}
//[ \t]+ 			{printf("Consuming space - \"%s\"\n",yytext);}
