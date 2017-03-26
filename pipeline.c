#include "sim.h"

const int base_pc=0x00400000;

struct IF inf[2];
struct ID id[2];
struct EX ex[2];
struct MA ma[2];

void IF(int insnum)
{
	inf[0].Ins=decoded[insnum];
}

void ID()
{

	int rs=inf[1].Ins.Rs , rt=inf[1].Ins.Rt , rd=inf[1].Ins.Rd;
	
	int s=inf[1].Ins.s , t=inf[1].Ins.t , d=inf[1].Ins.d;


	if(s==1)
	{
		id[0].vrs=reg[rs];
	}
	if(t==1)
	{
		id[0].vrt=reg[rt];
	}
	if(d==1)
	{
		id[0].vrd=reg[rd];
	}

}

void EX()
{
	ex[0].vrs=id[1].vrs;
	ex[0].vrt=id[1].vrt;
	ex[0].vrd=id[1].vrd;
	ex[0].address=-1;

int type=id[1].Ins.type;

	if(type==1)
	{
		int address=id[1].vrs+id[1].Ins.Offset;
		ex[0].address=address;

		// char ch1=mem[address+0-0x10010000];
		// char ch2=mem[address+1-0x10010000];
		// char ch3=mem[address+2-0x10010000];
		// char ch4=mem[address+3-0x10010000];

		// int e=256;
		// reg[rt]=(int)(ch1*e*e*e+ch2*e*e+ch3*e+ch4);
		// ++dacc;

	}
	else if(type==2)
	{
		int address=id[1].vrs+id[1].Ins.Offset;
		ex[0].address=address;
	}
	else if(type==3)
	{

	}
	else//NO ALU work, just pass forward
	{}	
}

void MA()
{
	ma[0].vrs=ex[1].vrs;
	ma[0].vrt=ex[1].vrt;
	ma[0].vrd=ex[1].vrd;

int type=ex[1].Ins.type;

	if(type==1)
	{
		int address=ex[1].address;

		char ch1=mem[address+0-0x10010000];
		char ch2=mem[address+1-0x10010000];
		char ch3=mem[address+2-0x10010000];
		char ch4=mem[address+3-0x10010000];

		int e=256;
		ma[0].vrt=(int)(ch1*e*e*e+ch2*e*e+ch3*e+ch4);

		++dacc;
	}
	else if(type==2)
	{
		int t=ex[1].vrt;
		char ch4=t%256;t/=256;
		char ch3=t%256;t/=256;
		char ch2=t%256;t/=256;
		char ch1=t%256;t/=256;

		int address=ex[1].address;
		mem[address+0-0x10010000]=ch1;
		mem[address+1-0x10010000]=ch2;
		mem[address+2-0x10010000]=ch3;
		mem[address+3-0x10010000]=ch4;			
	
		++dacc;
	}
	else if(type==13)//TODO----sign extended
	{
		int address=ex[1].address;
		char ch1=mem[address+0-0x10010000];

		ma[0].vrt=(int)(ch1);

		++dacc;
	}
	else if(type==14)
	{
		int t=ex[1].vrt;
		char ch4=t%256;//t&255

		int address=ex[1].address;
		mem[address+0-0x10010000]=ch4;
	
		++dacc;
	}
	else//NO Memory work, just pass forward
	{}
}

void transfer()
{
	inf[1]=inf[0];//TODO-------check
	id[1]=id[0];
	ex[1]=ex[0];
	ma[1]=ma[0];
}

void execute2()
{
	int curr=0,pc;

	while(curr<numins)//NO branch
	{
		pc=base_pc+4*curr;

		 IF(curr);
		 ID();
		 EX();
		// MEM();
		// WB();
		// transfer();
		 ++curr;
	}

}