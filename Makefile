CFLAGS= -Wall -std=c99 -ansi -pedantic -O2 -lreadline
CC= gcc

OBJDIR := bin

.PRECIOUS: bin/%Matrix.out bin/%Lists.out

$(OBJDIR):
	mkdir -p $(OBJDIR)

%M: $(OBJDIR)/%Matrix.out | $(OBJDIR)
	./$<

$(OBJDIR)/%Matrix.out: %Matrix.c GRAPHmatrix.c GRAPHmatrix.h prompt.c prompt.h
	${CC} -o $@ $^ ${CFLAGS}

%L: $(OBJDIR)/%Lists.out | $(OBJDIR)
	./$<

$(OBJDIR)/%Lists.out: %Lists.c GRAPHlists.c GRAPHlists.h
	${CC} -o $@ $^ ${CFLAGS}
