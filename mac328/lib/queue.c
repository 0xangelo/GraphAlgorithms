#include "queue.h"

struct queue {
    int N;
    int size;
    int first;
    int last;
    int *cont;
};

Queue QUEUEinit (int size) {
    Queue Q = malloc (sizeof (*Q));
    Q->N = size;
    Q->size = 0;
    Q->first = 0;
    Q->last = 0;
    Q->cont = malloc (size * sizeof (vertex));
    return Q;
}

void QUEUEput (Queue Q, vertex v) {
    Q->cont[Q->last++] = v;
    if (Q->last == Q->N) Q->last = 0;
    Q->size++;
}
vertex QUEUEget (Queue Q) {
    vertex v = Q->cont[Q->first++];
    if (Q->first == Q->N) Q->first = 0;
    Q->size--;
    return v;
}

bool QUEUEempty (Queue Q) {
    return Q->size == 0;
}

void QUEUEfree (Queue Q) {
    free (Q->cont);
    free (Q);
}
