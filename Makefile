CFLAGS= -Wall -std=c99 -ansi -pedantic -O2 -iquote lib/ -L./lib/ -lprompt -lreadline
CC= gcc

OBJDIR := bin

.PRECIOUS: bin/%M.out bin/%L.out

$(OBJDIR):
	mkdir -p $(OBJDIR)

GraphL: $(OBJDIR)/GraphL.out | $(OBJDIR)
	./$<

$(OBJDIR)/GraphL.out: Graph.c
	${CC} -o $@ -D'GRAPH="graphl.h"' $^ -lgraphl ${CFLAGS} -lqueue -lstack

GraphM: $(OBJDIR)/GraphM.out | $(OBJDIR)
	./$<

$(OBJDIR)/GraphM.out: Graph.c
	${CC} -o $@ -D'GRAPH="graphm.h"' $^ -lgraphm ${CFLAGS} -lqueue -lstack

WGraphL: $(OBJDIR)/WGraphL.out | $(OBJDIR)
	./$<

$(OBJDIR)/WGraphL.out: WGraph.c
	${CC} -o $@ -D'GRAPH="wgraphl.h"' $^ -lwgraphl ${CFLAGS} -lpriority_queue

WGraphM: $(OBJDIR)/WGraphM.out | $(OBJDIR)
	./$<

$(OBJDIR)/WGraphM.out: WGraph.c
	${CC} -o $@ -D'GRAPH="wgraphm.h"' $^ -lwgraphm ${CFLAGS} -lpriority_queue
