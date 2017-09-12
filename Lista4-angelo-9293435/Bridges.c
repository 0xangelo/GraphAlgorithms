#ifndef GRAPH
#define GRAPH "graphl.h"
#endif
#include GRAPH
#include <unistd.h>

int main () {
    FILE * in;
    char file[1000];
    UGraph G;

    printf ("Insira o nome de um arquivo de listas de adjacências: ");
    if (scanf (" %s", file) == EOF) {
        fprintf (stderr, "erro de leitura\n");
        return 1;
    }
    if( access( file, F_OK ) == -1 ) {
        printf ("Arquivo não existe\n");
        return 1;
    }
    in = fopen (file, "r");
    G = GRAPHinputListsFile (in);

    if (GRAPHisUndirected (G)) {
        printf ("As pontes do grafo são: \n");
        UGRAPHbridges (G);
    }
    else {
        printf ("O grafo de entrada deve ser não-direcionado!\n");
    }

    GRAPHfree (G);
    fclose (in);
    return 0;
}
