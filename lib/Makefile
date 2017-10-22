default:
	rm -f *.a
	gcc -c *.c -Wall -std=c99 -ansi -pedantic
	ar -cvq libgraphm.a graphm.o
	ar -cvq libgraphl.a graphl.o
	ar -cvq libprompt.a prompt.o
	ar -cvq libqueue.a queue.o
	ar -cvq libstack.a stack.o
	ar -cvq libwgraphl.a wgraphl.o
	ar -cvq libwgraphm.a wgraphm.o
	ar -cvq libpriority_queue.a priority_queue.o
	ranlib libgraphm.a
	ranlib libgraphl.a
	ranlib libprompt.a
	ranlib libqueue.a
	ranlib libstack.a
	ranlib libwgraphl.a
	ranlib libwgraphm.a
	ranlib libpriority_queue.a
