default:
	rm -f *.a
	gcc -c *.c -Wall -std=c99 -ansi -pedantic
	ar -cvq libqueue.a queue.o
	ar -cvq libgraphm.a graphm.o
	ar -cvq libgraphl.a graphl.o
	ar -cvq libprompt.a prompt.o
	ranlib libgraphm.a
	ranlib libgraphl.a
	ranlib libprompt.a
	ranlib libqueue.a
