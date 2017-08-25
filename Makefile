CFLAGS= -Wall -std=c99 -ansi -pedantic -O2 -lreadline -L./lib/ -lprompt
CC= gcc

OBJDIR := bin

.PRECIOUS: bin/%M.out bin/%L.out

$(OBJDIR):
	mkdir -p $(OBJDIR)

%M: $(OBJDIR)/%M.out | $(OBJDIR)
	./$<

$(OBJDIR)/%M.out: %.c
	${CC} -o $@ $^ ${CFLAGS} -D GRAPHM -lgraphm

%L: $(OBJDIR)/%L.out | $(OBJDIR)
	./$<

$(OBJDIR)/%L.out: %.c
	${CC} -o $@ $^ ${CFLAGS} -D GRAPHL -lgraphl
