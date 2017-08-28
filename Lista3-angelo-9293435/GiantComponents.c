#ifndef GRAPH
#define GRAPH "graphl.h"
#endif
#include <time.h>
#include <math.h>
#include GRAPH

const int T = 1e3;
const int V[] = {10, 50, 100, 500, 1000, 5000, 10000};
const double E[] = {0.2, 0.5, 1, 2, 5, 10, 20};

int mean (int *i) {
    double avg = 0;
    int t;
    for (t = 0; t < T; t++) {
        avg += 1 / (double) T * i[t];
    }
    return (int) avg;
}

int main () {
    int v, e, *arr, i[1000], t;
    UGraph G;
    printf ("   V\\E");
    for (e = 0; e < 7; e++) printf ("%5.1fV", E[e]);
    printf ("\n");
    for (v = 0; v < 7; v++) {
        arr = malloc (V[v] * sizeof (int));
        printf ("%6d", V[v]);
        for (e = 0; e < 7; e++) {
            for (t = 0; t < T; t++) {
                srand (time (NULL));
                G = UGRAPHrandU (V[v], E[e]*V[v]);
                i[t] = UGRAPHcc (G, arr);
                GRAPHfree (G);
            }
            printf ("%6d", mean (i));
        }
        printf ("\n");
    }
    
    return 0;
}
