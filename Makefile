CFLAGS= -Wall -std=c99 -ansi -pedantic -O2 -iquote lib/ -L./lib/ -lprompt -lreadline -lqueue
CC= gcc

OBJDIR := bin
LIBDIR := lib/*.a

.PRECIOUS: bin/%M.out bin/%L.out

$(OBJDIR):
	mkdir -p $(OBJDIR)

%M: $(OBJDIR)/%M.out | $(OBJDIR) $(LIBDIR)
	./$<

$(OBJDIR)/%M.out: %.c
	${CC} -o $@ -D'GRAPH="graphm.h"' $^ -lgraphm ${CFLAGS}

%L: $(OBJDIR)/%L.out | $(OBJDIR) $(LIBDIR)
	./$<

$(OBJDIR)/%L.out: %.c
	${CC} -o $@ -D'GRAPH="graphl.h"' $^ -lgraphl ${CFLAGS}
