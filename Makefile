CFLAGS= -Wall -std=c99 -ansi -pedantic -O2
CC= gcc

.PRECIOUS: bin/%Matrix.out bin/%Lists.out

%M: bin/%Matrix.out
	./$<

bin/%Matrix.out: %Matrix.c GRAPHmatrix.c GRAPHmatrix.h
	${CC} -o $@ $^ ${CFLAGS}

%L: bin/%Lists.out
	./$<

bin/%Lists.out: %Lists.c GRAPHlists.c GRAPHlists.h
	${CC} -o $@ $^ ${CFLAGS}
