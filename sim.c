#include "sim.h"



int btoi(char *a,int num)
{
	int res=0,i=0;
	for(i=0;i<num;++i)
	{res=2*res + (a[i]-'0');}
	
	return res;
}

//1 has to read
//2 has to be written

//str is 32 bits	[0...31]
void decode(char * str,int i)
{
	int type=-1;
	int rs=-1,rt=-1,rd=-1;
	int s=-1,t=-1,d=-1;
	int offset=-1;

	if(strcmp(subst(str,0,6),"100011")==0)			//0x23------lw rt,address
	{
		type=1;
		
		rs=btoi(subst(str,6,5),5);		s=1;	
		rt=btoi(subst(str,11,5),5);		t=2;

		offset=btoi(subst(str,16,16),16);
	}
	else if (strcmp(subst(str,0,6),"101011")==0)	//0x2b------st rt,address
	{
		type=2;

		rs=btoi(subst(str,6,5),5);		s=1;
		rt=btoi(subst(str,11,5),5);		t=1;
		
		offset=btoi(subst(str,16,16),16);
	}
	else if (strcmp(subst(str,0,6),"000000")==0 && strcmp(subst(str,21,5),"00000")==0 && strcmp(subst(str,26,6),"100000")==0)	//0x00------add rd,rs,rt
	{
		type=3;

	rs=btoi(subst(str,6,5),5);			s=1;
	rt=btoi(subst(str,11,5),5);			t=1;
	rd=btoi(subst(str,16,5),5);			d=2;
	
	}
	else if (strcmp(subst(str,0,6),"000000")==0 && strcmp(subst(str,21,5),"00000")==0 && strcmp(subst(str,26,6),"100010")==0)	//0x00------sub rd,rs,rt
	{
		type=4;

	rs=btoi(subst(str,6,5),5);			s=1;
	rt=btoi(subst(str,11,5),5);			t=1;
	rd=btoi(subst(str,16,5),5);			d=2;
	
	}
	else if (strcmp(subst(str,0,6),"001000")==0)	//------addi rt,rs,imm
	{
		type=5;

	rs=btoi(subst(str,6,5),5);			s=1;
	rt=btoi(subst(str,11,5),5);			t=2;

	offset=btoi(subst(str,16,16),16);
	}
	else if(strcmp(subst(str,0,6),"000000")==0 && strcmp(subst(str,21,5),"00000")==0 && strcmp(subst(str,26,6),"100100")==0)//and 
	{
		type=6;

	rs=btoi(subst(str,6,5),5);			s=1;
	rt=btoi(subst(str,11,5),5);			t=1;
	rd=btoi(subst(str,16,5),5);			d=2;
		
	}
	else if(strcmp(subst(str,0,6),"000000")==0 && strcmp(subst(str,21,5),"00000")==0 && strcmp(subst(str,26,6),"100101")==0)//or 
	{
		type=7;

	rs=btoi(subst(str,6,5),5);			s=1;
	rt=btoi(subst(str,11,5),5);			t=1;
	rd=btoi(subst(str,16,5),5);			d=2;
		
	}
	else if (strcmp(subst(str,0,6),"001101")==0)	//------ori rt,rs,imm
	{
		type=8;

	rs=btoi(subst(str,6,5),5);			s=1;
	rt=btoi(subst(str,11,5),5);			t=2;

	offset=btoi(subst(str,16,16),16);
	}
	else if (strcmp(subst(str,0,6),"001111")==0 && strcmp(subst(str,6,5),"00000")==0)	//------lui rt,rs,imm
	{
		type=9;

	rs=btoi(subst(str,6,5),5);			s=1;
	rt=btoi(subst(str,11,5),5);			t=2;

	offset=btoi(subst(str,16,16),16);
	}
	else if (strcmp(subst(str,0,6),"000000")==0 && strcmp(subst(str,16,10),"0000000000")==0 && strcmp(subst(str,26,6),"011000")==0)	//------mult rs,rt
	{
		type=10;

	rs=btoi(subst(str,6,5),5);			s=1;	
	rt=btoi(subst(str,11,5),5);			t=1;

	}
	else if (strcmp(subst(str,0,6),"000000")==0 && strcmp(subst(str,16,10),"0000000000")==0 && strcmp(subst(str,26,6),"011000")==0)	//TODO------madd rs,rt
	{
		type=11;

	rs=btoi(subst(str,6,5),5);			s=1;
	rt=btoi(subst(str,11,5),5);			t=1;

	}
	else if(strcmp(subst(str,0,6),"000000")==0 && strcmp(subst(str,21,5),"00000")==0 && strcmp(subst(str,26,6),"100111")==0) //--nor rd,rs,rt
	{
		type=12;

	rs=btoi(subst(str,6,5),5);			s=1;
	rt=btoi(subst(str,11,5),5);			t=1;
	rd=btoi(subst(str,16,5),5);			d=2;
		
	} 		
	else if(strcmp(subst(str,0,6),"100000")==0)			//0x20------lb rt,address
	{
		type=13;
		
		rs=btoi(subst(str,6,5),5);		s=1;	
		rt=btoi(subst(str,11,5),5);		t=2;

		offset=btoi(subst(str,16,16),16);
	}
	else if (strcmp(subst(str,0,6),"101000")==0)	//0x28------sb rt,address
	{
		type=14;

		rs=btoi(subst(str,6,5),5);		s=1;
		rt=btoi(subst(str,11,5),5);		t=1;
		
		offset=btoi(subst(str,16,16),16);
	}


	if(type==-1)
	{printf("Error - unable to decode instruction %d\n",i);}

	decoded[i].type=type;
	
	decoded[i].Rs=rs;
	decoded[i].Rt=rt;
	decoded[i].Rd=rd;

	decoded[i].s=s;
	decoded[i].t=t;
	decoded[i].d=d;

	decoded[i].Offset=offset;

}

/*
Following is the list of supported instructions (for part1):
The memory-reference instructions load word ( lw ) and store word ( sw )
The arithmetic-logical instructions add , sub , AND , OR , and slt
The instructions branch equal ( beq ) and jump (j)
*/

void simulate()
{

    input_hexin();
	//test_hexin();

	decoded=(struct INST*)calloc((numins+10),sizeof(struct INST));


	int i=0;
	for(i=0;i<numins;++i)
	{
		decode(ins_string[i],i);
	}
	test_decode();

	execute();

}

void execute()
{
	int curr=0;
	while(curr<numins)
	{
		++iacc;

		int type=decoded[curr].type;
		int rd=decoded[curr].Rd,rs=decoded[curr].Rs,rt=decoded[curr].Rt;
		int offset=decoded[curr].Offset;

		if(type==1)
		{
			int address=reg[rs]+offset;
			char ch1=mem[address+0-0x10010000];
			char ch2=mem[address+1-0x10010000];
			char ch3=mem[address+2-0x10010000];
			char ch4=mem[address+3-0x10010000];

			int e=256;
			reg[rt]=(int)(ch1*e*e*e+ch2*e*e+ch3*e+ch4);

			++dacc;
		}
		else if(type==2)
		{
			int t=reg[rt];
			char ch4=t%256;t/=256;
			char ch3=t%256;t/=256;
			char ch2=t%256;t/=256;
			char ch1=t%256;t/=256;

			int address=reg[rs]+offset;
			mem[address+0-0x10010000]=ch1;
			mem[address+1-0x10010000]=ch2;
			mem[address+2-0x10010000]=ch3;
			mem[address+3-0x10010000]=ch4;			
		
			++dacc;
		}
		else if(type==3)
		{
			reg[rd]=reg[rs]+reg[rt];
		}
		else if(type==4)
		{
			reg[rd]=reg[rs]-reg[rt];			
		}
		else if(type==5)
		{
			reg[rt]=reg[rs]+offset;
		}
		else if(type==6)
		{
			reg[rd]=reg[rs] & reg[rt];	
		}
		else if(type==7)
		{
			reg[rd]=reg[rs] | reg[rt];	
		}
		else if(type==8)
		{
			reg[rt]=reg[rs] | offset;	
		}
		else if(type==9)
		{
			reg[rt]=65536*offset;	
		}
		else if(type==10)
		{
			long long int temp=(long long int)reg[rt]*(long long int)reg[rt];	
			//hi is 32 , lo is 33
			reg[33]=temp%(1LL<<32);
			reg[32]=(temp>>32);				
		}
		else if(type==11)//TODO carry
		{
			long long int temp=(long long int)reg[rt]*(long long int)reg[rt];	
			//hi is 32 , lo is 33
			
		}
		else if(type==12)
		{
			reg[rd]= ~(reg[rs] | reg[rt]);	// '~' is bitwise not operator 
		}
		else if(type==13)//TODO----sign extended
		{
			int address=reg[rs]+offset;
			char ch1=mem[address+0-0x10010000];

			reg[rt]=(int)(ch1);

			++dacc;
		}
		else if(type==14)
		{
			int t=reg[rt];
			char ch4=t%256;//t&255

			int address=reg[rs]+offset;
			mem[address+0-0x10010000]=ch4;
		
			++dacc;
		}


		++curr;

	}
}

void test_decode()
{
	int i=0;
	for(i=0;i<numins;++i)
	{

	}
}

char * subst(char *a, int start,int num)
{
	char * res;res=(char * )calloc(num,sizeof(char));
	int i=0;
	for(i=0;i<num;++i)
	{res[i]=a[start+i];}
	
	return res;
}
