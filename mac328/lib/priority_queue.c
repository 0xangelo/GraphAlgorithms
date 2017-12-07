#include "priority_queue.h"

struct priority_queue {
    int *cont;
    int *pos;
    int N;
};

/* static bool less (PriorityQueue Q, int i, int j) { */
/*     return Q->cont[i][1] < Q->cont[j][1]; */
/* } */

static bool more (PriorityQueue Q, int i, int j, int *dist) {
    return dist[Q->cont[i]] > dist[Q->cont[j]];
}

static void swap (PriorityQueue Q, int i, int j) {
    int exch = Q->cont[i];
    Q->cont[i] = Q->cont[j];
    Q->pos[Q->cont[i]] = i;
    Q->cont[j] = exch;
    Q->pos[Q->cont[j]] = j;
}

PriorityQueue PQinit (int size) {
    PriorityQueue Q = malloc (sizeof (*Q));
    Q->N = 0;
    Q->cont = malloc ((size + 1) * sizeof (int));
    Q->pos = malloc ((size + 1) * sizeof (int));
    return Q;
}

bool PQempty (PriorityQueue Q) {
    return Q->N == 0;
}

int PQsize (PriorityQueue Q) {
    return Q->N;
}

static void swim (PriorityQueue Q, int k, int *dist) {
    while (k > 1 && more (Q, k >> 1, k, dist)) {
        swap (Q, k >> 1, k);
        k >>= 1;
    }
}

void PQinsert (PriorityQueue Q, vertex v, int *dist) {
    Q->cont[++Q->N] = v;
    Q->pos[v] = Q->N;
    swim (Q, Q->N, dist);
}

static void sink (PriorityQueue Q, int k, int *dist) {
    int j;
    while (k << 1 <= Q->N) {
        j = k << 1;
        if (j < Q->N && more (Q, j, j+1, dist)) j++;
        if (!more (Q, k, j, dist)) break;
        swap (Q, k, j);
        k = j;
    }
}

vertex PQdelMin (PriorityQueue Q, int *dist) {
    vertex min = Q->cont[1];
    swap (Q, 1, Q->N--);
    sink (Q, 1, dist);
    return min;
}

void PQdec (PriorityQueue Q, vertex v, int *dist) {
    swim (Q, Q->pos[v], dist);
}

void PQfree (PriorityQueue Q) {
    free (Q->cont);
    free (Q->pos);
    free (Q);
}
