#include "sim.h"

const int base_pc=0x00400000;

struct IF inf[2];
struct ID id[2];
struct EX ex[2];
struct MA ma[2];

void IF(int insnum)
{
	++iacc;
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

	id[0].Ins=inf[1].Ins;

	//printf("ID: Rs=%d vrs=%d s=%d\n",id[0].Ins.Rs,id[0].vrs,id[0].Ins.s);
}

void EX()
{
	ex[0].vrs=id[1].vrs;
	ex[0].vrt=id[1].vrt;
	ex[0].vrd=id[1].vrd;
	ex[0].address=-1;
	ex[0].Ins=id[1].Ins;

	int type=id[1].Ins.type;

	if(type==1)
	{
		int address=id[1].vrs+id[1].Ins.Offset;
		ex[0].address=address;
	}
	else if(type==2)
	{
		int address=id[1].vrs+id[1].Ins.Offset;
		ex[0].address=address;
	}
	else if(type==3)
	{
		ex[0].vrd=id[1].vrs+id[1].vrt;
		//printf("%d + %d \n",id[1].vrs,id[1].vrt);
	}
	else if(type==4)
	{
		ex[0].vrd=id[1].vrs-id[1].vrt;
	}
	else if(type==5)
	{
		ex[0].vrt=id[1].vrs-id[1].Ins.Offset;
	}
	else if(type==6)
	{
		ex[0].vrd=id[1].vrs & id[1].vrt;	
	}
	else if(type==7)
	{
		ex[0].vrd=id[1].vrs | id[1].vrt;
	}
	else if(type==8)
	{
		ex[0].vrt=id[1].vrs | id[1].Ins.Offset;
		//printf("%d = %d | %d \n",ex[0].vrd,id[1].vrs,id[1].Ins.Offset);

	}
	else if(type==9)
	{
		ex[0].vrt=(id[1].Ins.Offset<<16);
	}
	else if(type==10)//CAUTION
	{
		long long int temp=(long long int)id[1].vrs*(long long int)id[1].vrt;	
		//hi is 32 , lo is 33
		ex[0].vrt=temp%(1LL<<32);ex[0].Ins.Rt=33;ex[0].Ins.t=2;
		ex[0].vrd=(temp>>32);	 ex[0].Ins.Rd=32;ex[0].Ins.d=2;				
	}
	else if(type==11)//TODO carry//CAUTION
	{
		long long int temp=(long long int)id[1].vrs*(long long int)id[1].vrt;	
		//hi is 32 , lo is 33
		
	}
	else if(type==12)
	{
		ex[0].vrd= ~(id[1].vrs | id[1].vrt);	// '~' is bitwise not operator 
	}
	else if(type==13)//TODO----sign extended
	{
		int address=id[1].vrs+id[1].Ins.Offset;
		char ch1=mem[address+0-0x10010000];

		ex[0].vrt=(int)(ch1);

	}
	else if(type==14)
	{
		int t=ex[0].vrt;
		char ch4=t%256;//t&255

		int address=id[1].vrs+id[1].Ins.Offset;
		mem[address+0-0x10010000]=ch4;
	
	}
	else if(type==15)
	{
		ex[0].vrd= (id[1].vrt << id[1].vrs);	
	}
	else if(type==16)
	{
		ex[0].vrd= ( (unsigned int)id[1].vrs < (unsigned int)id[1].vrt )?1:0;
	}
	else if(type==17)
	{
		ex[0].vrt= ( (unsigned int)id[1].vrs < (unsigned int)id[1].Ins.Offset )?1:0;
	}
	else if(type==18)
	{
		ex[0].vrd= (id[1].vrt << id[1].Ins.Offset);	
	}
	else if(type==19)
	{
		if(id[1].vrt == id[1].vrs)
		{
			curr+=id[1].Ins.Offset;
			if(curr<0)
			{fprintf(stderr,"Error - Invalid branch instruction\n");}	
		}	
	}
	else if(type==20)
	{
		if(id[1].vrs >= 0)
		{
			curr+=id[1].Ins.Offset;
			if(curr<0)
			{fprintf(stderr,"Error - Invalid branch instruction\n");}	

			inf[0].Ins.invalid=1;
			inf[1].Ins.invalid=1;
			id[0].Ins.invalid=1;
		}	
	}
	else if(type==21)
	{
		if(id[1].vrt > 0)
		{
			curr+=id[1].Ins.Offset;
			if(curr<0)
			{fprintf(stderr,"Error - Invalid branch instruction\n");}	

			inf[0].Ins.invalid=1;
			inf[1].Ins.invalid=1;
			id[0].Ins.invalid=1;
		}	
	}
	else if(type==22)
	{
		if(id[1].vrt <= 0)
		{
			curr+=id[1].Ins.Offset;
			if(curr<0)
			{fprintf(stderr,"Error - Invalid branch instruction\n");}	
		
			inf[0].Ins.invalid=1;
			inf[1].Ins.invalid=1;
			id[0].Ins.invalid=1;
		}	
	}
	else if(type==23)
	{
		if(id[1].vrt < 0)
		{
			curr+=id[1].Ins.Offset;
			if(curr<0)
			{fprintf(stderr,"Error - Invalid branch instruction\n");}	
		
			inf[0].Ins.invalid=1;
			inf[1].Ins.invalid=1;
			id[0].Ins.invalid=1;
		}	
	}
	else//NO ALU work, just pass forward
	{}	
}

void MA()
{
	ma[0].vrs=ex[1].vrs;
	ma[0].vrt=ex[1].vrt;
	ma[0].vrd=ex[1].vrd;

	ma[0].Ins=ex[1].Ins;

	int type=ex[1].Ins.type;

	if(ex[1].Ins.invalid==0)//notinvalid
	{

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
	else if(type==13)//TODO----sign extended----probably done
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
}

void WB()
{
	//printf("%d\n",ma[1].vrd);
	if(ma[1].Ins.invalid==0)//notinvalid
	{

	if(ma[1].Ins.s==2)
	{reg[ma[1].Ins.Rs]=ma[1].vrs;}

	if(ma[1].Ins.t==2)
	{reg[ma[1].Ins.Rt]=ma[1].vrt;}

	if(ma[1].Ins.d==2)
	{reg[ma[1].Ins.Rd]=ma[1].vrd;}

	//printf("Rd=%d vrd=%d d=%d\n",ma[1].Ins.Rd,ma[1].vrd,ma[1].Ins.d);
	}
	//printf("%d %d %d\n",ma[1].vrs,ma[1].vrt,ma[1].vrd);

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
	int pc;
	curr=0;

	while(curr<numins)//NO branch
	{
		pc=base_pc+4*curr;

		IF(curr);
		//transfer();
		
		WB();
		ID();
		//transfer();		
		EX();
		//transfer();		
		MA();
		//transfer();		
		
		transfer();
		reg[34]=pc;

		 ++curr;
	}

}
