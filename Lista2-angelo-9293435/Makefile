CFLAGS= -Wall -std=c99 -ansi -pedantic -O2
CC= gcc

OBJDIR := bin

.PRECIOUS: bin/%M.out bin/%L.out

$(OBJDIR):
	mkdir -p $(OBJDIR)

%M: $(OBJDIR)/%M.out | $(OBJDIR)
	./$<

$(OBJDIR)/%M.out: %.c GRAPHmatrix.c GRAPHmatrix.h
	${CC} -o $@ $^ ${CFLAGS} -D GRAPHM

%L: $(OBJDIR)/%L.out | $(OBJDIR)
	./$<

$(OBJDIR)/%L.out: %.c GRAPHlists.c GRAPHlists.h
	${CC} -o $@ $^ ${CFLAGS} -D GRAPHL
