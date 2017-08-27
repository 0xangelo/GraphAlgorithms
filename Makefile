CFLAGS= -Wall -std=c99 -ansi -pedantic -O2 -iquote lib/ -L./lib/ -lprompt -lreadline
CC= gcc

OBJDIR := bin

.PRECIOUS: bin/%M.out bin/%L.out

$(OBJDIR):
	mkdir -p $(OBJDIR)

%M: $(OBJDIR)/%M.out | $(OBJDIR)
	./$<

$(OBJDIR)/%M.out: %.c
	${CC} -o $@ $^ -D GRAPHM ${CFLAGS} -lgraphm

%L: $(OBJDIR)/%L.out | $(OBJDIR)
	./$<

$(OBJDIR)/%L.out: %.c
	${CC} -o $@ $^ -D GRAPHL ${CFLAGS} -lgraphl
