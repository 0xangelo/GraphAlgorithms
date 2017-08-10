#include "GRAPHlists.h"

int main (int argc, char **argv) {
    FILE * pidigits = fopen ("pidigits.txt", "r");
    int i, n;
    char curr, prev;
    Graph G;

    /* if (argc > 1) n = atoi (argv[1]); */
    /* else { */
    /*     fprintf (stderr, "error: no number of digits of pi specified\n"); */
    /*     return 1; */
    /* } */
    printf ("Insert number of digits of pi: ");
    scanf (" %d", &n);
    G = GRAPHinit (10);
    fscanf (pidigits, "%c", &prev);
    for (i = 1; i < n; i++) {
        fscanf (pidigits, "%c", &curr);
        UGRAPHinsertArc (G, prev - '0', curr - '0');
        prev = curr;
    }

    GRAPHshow (G);
    return 0;
}
