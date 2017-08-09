#include "GRAPHlists.h"

int main () {
    int V;
    Graph G;
    printf ("Enter the number of vertices: ");
    scanf (" %d", &V);
    G = GRAPHbuildComplete (V);
    GRAPHshow (G);
    return 0;
}
