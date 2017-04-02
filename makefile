all: 
	lex sim.l
	yacc -d sim.y
	gcc -g -Wall -o processor_simulator sim.c pipeline.c step.c printsvg.c y.tab.c lex.yy.c -lm -pthread
	rm *.tab.* *.yy.*
clean:
	rm processor_simulator a.out *.svg results*.txt