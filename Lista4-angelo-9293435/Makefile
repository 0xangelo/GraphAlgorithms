CFLAGS= -Wall -std=c99 -ansi -pedantic -O2
CC= gcc

OBJDIR := bin

.PRECIOUS: bin/%M.out bin/%L.out

$(OBJDIR):
	mkdir -p $(OBJDIR)

%M: $(OBJDIR)/%M.out | $(OBJDIR)
	./$<

$(OBJDIR)/%M.out: %.c graphm.c graphm.h
	${CC} -o $@ -D'GRAPH="graphm.h"' $^ ${CFLAGS}

%L: $(OBJDIR)/%L.out | $(OBJDIR)
	./$<

$(OBJDIR)/%L.out: %.c graphl.c graphl.h
	${CC} -o $@ -D'GRAPH="graphl.h"' $^ ${CFLAGS}
