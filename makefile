all: 
	lex sim.l
	yacc -d sim.y
	gcc -Wall -o processor_simulator sim.c y.tab.c lex.yy.c -lm
	rm *.tab.* *.yy.*
clean:
	rm processor_simulator a.out *.svg results*.txt