#include <stdio.h>

int main()
{
	int i;


	FILE* t3=fopen("./Tests/1000.hex","w");
	FILE* s3=fopen("./Tests/step3","w");
	
	for(i=0;i<1000;++i)
	{
		fprintf(t3,"014b4820\n");
		fprintf(s3,"step\n");
	}
	for(i=0;i<10;++i)
	{
		fprintf(s3,"step\n");
	}
	fclose(t3);
	fclose(s3);

	
	FILE* t4=fopen("./Tests/10000.hex","w");
	FILE* s4=fopen("./Tests/step4","w");
	
	for(i=0;i<10000;++i)
	{
		fprintf(t4,"014b4820\n");
		fprintf(s4,"step\n");
	}
	for(i=0;i<10;++i)
	{
		fprintf(s4,"step\n");
	}
	fclose(t4);
	fclose(s4);

	
	FILE* t5=fopen("./Tests/100000.hex","w");
	FILE* s5=fopen("./Tests/step5","w");
	
	for(i=0;i<100000;++i)
	{
		fprintf(t5,"014b4820\n");
		fprintf(s5,"step\n");
	}
	for(i=0;i<10;++i)
	{
		fprintf(s5,"step\n");
	}
	fclose(t5);
	fclose(s5);


	FILE* t6=fopen("./Tests/1000000.hex","w");
	FILE* s6=fopen("./Tests/step6","w");
	
	for(i=0;i<1000000;++i)
	{
		fprintf(t6,"014b4820\n");
		fprintf(s6,"step\n");
	}
	for(i=0;i<10;++i)
	{
		fprintf(s6,"step\n");
	}
	fclose(t6);
	fclose(s6);

	
	FILE* t7=fopen("./Tests/10000000.hex","w");
	FILE* s7=fopen("./Tests/step7","w");
	
	for(i=0;i<10000000;++i)
	{
		fprintf(t7,"014b4820\n");
		fprintf(s7,"step\n");
	}
	for(i=0;i<10;++i)
	{
		fprintf(s7,"step\n");
	}
	fclose(t7);
	fclose(s7);

	
	FILE* t8=fopen("./Tests/100000000.hex","w");
	FILE* s8=fopen("./Tests/step8","w");
	
	for(i=0;i<100000000;++i)
	{
		fprintf(t8,"014b4820\n");
		fprintf(s8,"step\n");
	}
	for(i=0;i<10;++i)
	{
		fprintf(s8,"step\n");
	}
	fclose(t8);
	fclose(s8);
}


/*
./processor_simulator 1000.hex 1000.svg 1000.txt <step3
./processor_simulator 10000.hex 10000.svg 10000.txt <step4
./processor_simulator 100000.hex 100000.svg 100000.txt <step5
./processor_simulator 1000000.hex 1000000.svg 1000000.txt <step6
./processor_simulator 10000000.hex 10000000.svg 10000000.txt <step7
./processor_simulator 100000000.hex 100000000.svg 100000000.txt <step8
*/
