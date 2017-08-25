#include <time.h>
#include <math.h>
#ifdef GRAPHL
#include "GRAPHlists.h"
#else
#include "GRAPHmatrix.h"
#endif

const int T = 1e3;
const int V = 1e5;
const double M[] = {0.2, 0.5, 1, 2, 5, 10, 20, -1};

int main () {
    int v, e, *arr;
    UGraph G;
    for (v = 10; v < V; v++) {
        arr = malloc (v * sizeof (int));
        for (e = 0; M[e] > 0; e++) {
            srand (time (NULL));
            G = UGRAPHrandU (v, M[e]*v);
            printf (" %d", UGRAPHcc (G, arr));
        }
        printf ("\n");
    }
    
    return 0;
}
