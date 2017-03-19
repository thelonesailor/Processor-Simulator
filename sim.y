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
%token er END STEP
%start Input
%%

Input: Line  
	| Line Input 
;

Line: END	      {/*printf("Got only end\n");*/}
     | Expression {/*printf("Got only expression\n");*/}
;

Expression:
  REGDUMP END               {}
| MEMDUMP ADDR NUM END      {}
| STEP END                  {}        

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
    numins=0;

}
void input_hexin()
{
    if (hexin == NULL) {
        fprintf(stderr,"Error - Input hex file not found\n");
        exit(-1);
    }

    int x=1;
    char str[1000];
    
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

            ins[numins++]=(long long int)strtol(str, NULL, 16);

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

int main(int argc, char* argv[]) //TODO take file names from command line
{
    initialise();
    int printres=0;

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
    
    yyin = stdin;
    if (yyin == NULL) {
        fprintf(stderr,"Error - yyin is null\n");
        exit(-2);
    }


    input_hexin();
//    test_hexin();



/*
    //change to keep parsing multiple times because we just want to ignore the wrong line
    do {
        yyparse();
    } while (!feof(yyin));

    //	test_print();	//debug



 	for(i=0;i<numnets;++i)
 	{
 		
        if(times[i]==1)
 		{
            fprintf(stderr,"Error - Net: \"%s\" is connected to only one component\n",arr[i]);
        }
 	}

    int is_draw_ground = 0;

    if(!check_ground())
    {
        fprintf(stderr,"Error - No ground net found\n");
    }
    else
    {
        is_draw_ground = 1;
    }

    start_svg(numnets,numcmp,outfile);


    end_svg(outfile);

    solve_circuit();
*/

    return 0;
}

//print error but don't exit
void yyerror(char * s) {

    if (strcmp(s, "syntax error") == 0) {
        fprintf(stderr,"Error - Format of input is wrong\n");
    } else {
        fprintf(stderr,"%s\n", s);
    }

}
