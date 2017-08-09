#include <time.h>
#include "GRAPHmatrix.h"

int main () {
    int V, A, seed;
    Graph G1, G2;
    printf ("Enter the number of vertices: ");
    scanf (" %d", &V);
    printf ("Enter the number of edges: ");
    scanf (" %d", &A);
    printf ("Enter seed: ");
    scanf (" %d", &seed);
    srand (clock ());
    G1 = GRAPHrand1 (V, A);
    GRAPHshow (G1);
    G2 = GRAPHrand2 (V, A);
    GRAPHshow (G2);
    return 0;
}
