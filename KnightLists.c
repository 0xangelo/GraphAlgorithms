#include "GRAPHlists.h"

int main () {
    int i, j;
    Graph G = UGRAPHknight();
    printf ("Enter knight's position: ");
    scanf (" %d %d", &i, &j);
    UGRAPHshowKnight (G, i, j);
    return 0;
}
