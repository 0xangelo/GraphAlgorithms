/* Nome: Ângelo Gregório Lovatto */
/* NUSP: 9293435 */
#include "GRAPHmatrix.h"

int main (int argc, char **argv) {
    FILE * pidigits = fopen ("pidigits.txt", "r");
    int i, n, err = 0;
    char curr, prev;
    Graph G;

    if (argc > 1) n = atoi (argv[1]);
    else {
        fprintf (stderr, "error: no number of digits of pi specified\n");
        return 1;
    }
    G = GRAPHinit (10);

    err |= fscanf (pidigits, "%c", &prev);
    for (i = 1; i < n; i++) {
        err |= fscanf (pidigits, "%c", &curr);
        GRAPHinsertArc (G, prev - '0', curr - '0');
        prev = curr;
    }

    GRAPHshow (G);
    return 0;
}
