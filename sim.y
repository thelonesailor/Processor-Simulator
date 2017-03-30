%{
#include "sim.h"

    
extern FILE *yyin;
void yyerror (char *s);
int yylex();
%}

%union {int addr;int num;char * s;}         
%token MEMDUMP REGDUMP
%token <addr> ADDR 
%token <num> NUM
%token er END 
%token STEP QUIT GOTOEND
%start Input
%%

Input: Line  
	| Line Input 
;

Line: END	      {/*printf("Got only end\n");*/}
     | Expression {/*printf("Got only expression\n");*/}
;

Expression:
  REGDUMP END               {print_regdump();printf("Shell>>");}
| MEMDUMP ADDR NUM END      {print_memdump($2,$3);printf("Shell>>");}
| STEP END                  {return 50;}        
| QUIT END                  {return 100;}
| GOTOEND END               {return 150;}
;

| REGDUMP er {/*printf("Got and error\n");*/}
| MEMDUMP ADDR NUM er {}
| MEMDUMP ADDR er {}
| MEMDUMP er {}
| STEP er {}
| er {/*printf("Got and error\n");*/}
;

%%                    

void initialise()
{
    iacc=dacc=numins=numcycles=0;
    
    int i=0;
    for(i=0;i<34;++i)
    {reg[i]=0;}
    reg[34]=0x00400000;//pc=0x00400000

    for(i=0;i<64000005;++i)
    {mem[i]=0;}
}

void print_regdump()
{
    int i;
    for(i=0;i<32;++i)
    {printf("$%02d: 0x%08x \n",i,reg[i]);}
    
    printf("hi: 0x%08x \n",reg[32]);
    printf("lo: 0x%08x \n",reg[33]);
    printf("pc: 0x%08x \n",reg[34]);
}

void print_memdump(int addr,int num)
{
    if(addr<0x10010000)
    {fprintf(stderr,"Error - Address given is out of range\n");}
    else if(addr>0x10010000+64000000)
    {fprintf(stderr,"Error - Address given is out of range\n");}
    else 
    {
        int i=0;
        for(i=0;i<num;++i)
        {printf("0x%08x: 0x%02x\n",addr+i,mem[addr-0x10010000+i]);}
    }
}

void llinttobinary(long long int a,int num)
{
    long long int b=a;
    int j;
    for(j=31;j>=0;--j)
    {ins_string[num][j]=b%2+'0';b/=2;}
    //ins_string[num][32]='\0';  
}

void input_hexin()
{
    if (hexin == NULL) {
        fprintf(stderr,"Error - Input hex file not found\n");
        exit(-1);
    }

    int x=1;
    char str[1000];

    ins=(long long int *)calloc((1e7+10),sizeof(long long int));
    ins_string = (char**)calloc((1e7+10), sizeof(char*));
  

    numins=0;
    while(fscanf(hexin,"%s",str)!=EOF)
    {
        if(strlen(str)==8)
        {
            int i=0;
            for(i=0;i<8;++i)
            {
                str[i]=toupper(str[i]);
                if(!( ('0'<=str[i] && str[i]<='9')||('A'<=str[i] && str[i]<='F') ))
                {fprintf(stderr,"Error - Invalid instruction number %d\n",x);
                goto label;}
            }
                   

            ins[numins]=(long long int)strtol(str, NULL, 16);//hex string to long long int
            ins_string[numins] = (char*)calloc(32, sizeof(char));            
            llinttobinary(ins[numins],numins);


    //printf("ins_string[%d]=\"%s\"  len=%lu  ins[%d]=%lld\n",numins,ins_string[numins],strlen(ins_string[numins]),numins,ins[numins]);
            ++numins;
        }
        else
        {fprintf(stderr,"Error - Invalid instruction number %d\n",x);}

    label:;

    ++x;
    }
}

void test_hexin()
{
    printf("numins=%d\n",numins);
    int i=0;
    for(i=0;i<numins;++i)
    {
        printf("ins[%d]=%lld\n",i,ins[i]);
    }
}

void test()
{
    char ch=-3;
    int a=(int)ch;
    printf("ch=%d  a=%d\n",ch,a);
}

int main(int argc, char* argv[])
{
    initialise();
    int printres=0;

    //test();

    if(argc == 3)
    {
        hexin=fopen(argv[1],"r");
        if (hexin == NULL) {
        fprintf(stderr,"Error - Input hex file \"%s\" not found\n",argv[1]);
        exit(-1);
        }

        svgout=fopen(argv[2],"w");
        if (svgout == NULL) {
        fprintf(stderr,"Error - Output svg file \"%s\" not found\n",argv[2]);
        exit(-1);
        }

        printres=0;
    }
    else if(argc == 4)
    {
        hexin=fopen(argv[1],"r");
        if (hexin == NULL) {
        fprintf(stderr,"Error - Input hex file \"%s\" not found\n",argv[1]);
        exit(-1);
        }

        svgout=fopen(argv[2],"w");
        if (svgout == NULL) {
        fprintf(stderr,"Error - Output svg file \"%s\" not found\n",argv[2]);
        exit(-1);
        }

        resout=fopen(argv[3],"w");
        if (resout == NULL) {
        fprintf(stderr,"Error - Output result file \"%s\" not found\n",argv[3]);
        exit(-1);
        }

        printres=1; 
    }
    else
    {
        fprintf(stderr, "Error - 3 or 4 arguments required! Now %d arguments given\n",argc);
        exit(-1);
    }
    
    /*hexin=fopen("in6.hex","r");
    if (hexin == NULL) {
    fprintf(stderr,"Error - Input hex file \"%s\" not found\n","");
    exit(-1);
    }    printres=1; 

    svgout=fopen("test6.svg","w");
    if (svgout == NULL) {
    fprintf(stderr,"Error - Output svg file \"%s\" not found\n","");
    exit(-1);
    }
    resout=fopen("results6.txt","w");
    if (resout == NULL) {
    fprintf(stderr,"Error - Output result file \"%s\" not found\n","");
    exit(-1);
    }*/

    yyin = stdin;
    if (yyin == NULL) {
        fprintf(stderr,"Error - yyin is null\n");
        exit(-2);
    }


//    printf("sim\n");
    simulate();
    
    printf("Shell>>");
    yyparse();
    //change to keep parsing multiple times because we just want to ignore the wrong line
    /*do {
        int temp=yyparse();
        if(temp==100)
        {break;}
    } while (!feof(yyin));
    */

    //	test_print();	//debug


    if(printres==1)//output the result file
    {
        print_result();
    }

    fclose(hexin);
    fclose(svgout);
    fclose(resout);

    return 0;
}

void print_result()//-------------TODO
{

    fprintf(resout,"Instructions,%d\n",iacc);
    fprintf(resout,"Cycles,%d\n",numcycles);
    double ipc=iacc*1.0/numcycles*1.0;
    fprintf(resout,"IPC,%.04lf\n",ipc);

    double Time=numcycles*0.5;
    fprintf(resout,"Time (ns),%.04lf\n",Time);
    
    double Idle_time=(numcycles-iacc)*0.5;
    fprintf(resout,"Idle time (ns),%.4lf\n",Idle_time);
    fprintf(resout,"Idle time (%%),%.04lf%%\n",(Idle_time/Time)*100.0);

    fprintf(resout,"Cache Summary\n");
    fprintf(resout,"Cache L1-I\n");
    fprintf(resout,"num cache accesses,%d\n",iacc);
    fprintf(resout,"Cache L1-D\n");
    fprintf(resout,"num cache accesses,%d\n",dacc);
}

//print error but don't exit
void yyerror(char * s) {

    if (strcmp(s, "syntax error") == 0) {
        fprintf(stderr,"Error - Format of input is wrong\n");
    } else {
        fprintf(stderr,"%s\n", s);
    }

}
