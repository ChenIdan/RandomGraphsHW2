
prog: random.o RandomGraphs.o prog.o
	gcc -o prog random.o RandomGraphs.o prog.o -lm

prog.o: prog.c
	gcc -c -std=c99 prog.c 

RandomGraphs.o: RandomGraphs.c
	gcc -c -std=c99 RandomGraphs.c -lm

random.o: random.c
	gcc -c -std=c99 random.c -lm


clean: 
	rm prog.o RandomGraphs.o random.o



 
