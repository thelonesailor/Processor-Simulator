
struct IF{
	int pc;
	char ins[32];
}

struct ID{
	int pc;
	int branch_target;
	int A,B;
	int op2;
	char ins[32];
}

struct EX{
	int pc;
	int aluresult;
	int op2;
	char ins[32];
}

struct MA{
	int pc;
	int idresult;
	int aluresult;
	char ins[32];
}

struct RW{

}


/*
Following is the list of supported instructions (for part1):
The memory-reference instructions load word ( lw ) and store word ( sw )
The arithmetic-logical instructions add , sub , AND , OR , and slt
The instructions branch equal ( beq ) and jump (j)
*/

void simulate(int newinsid)// newinsid=-1 when when no more instructions 
{


}
