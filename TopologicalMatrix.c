#include "GRAPHmatrix.h"

int main () {
    FILE *in = fopen ("rootedForest.txt", "r");
    Graph G = GRAPHinputArcs (in);
    int p[] = {5, 5, 0, 0, 4, 4, 11, 11, 7, 7, 7, 11};
    vertex v, w;
    int error = 0;

    GRAPHshow (G);
    printf ("Maximum heigth: %d\n", GRAPHrootedForestHeight (G, p));
    printf ("Insert 2 vertices: ");
    error |= scanf (" %d %d", &v, &w);
    printf ("%d reaches %d?\n", v, w);
    printf (GRAPHreach (G, v, w) ? "Yes\n" : "No\n");
    GRAPHdfs (G);
    for (v = 0; v < G->V; v++) printf ("%d ", G->pre[v]);
    printf ("\n");
    return 0;
}
