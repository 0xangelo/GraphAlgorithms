#include <string.h>
#include "GRAPHlists.h"

int main (int argc, char **argv) {
    FILE *in;
    Graph G;
    vertex v, w;
    if (argc < 2) {
        fprintf (stderr, "error: no input file specified\n");
        return 1;
    }
    
    in = fopen (argv[1], "r");
    if (strcmp ("arcos.txt", argv[1]) == 0)
        G = GRAPHinputArcs (in);
    else
        G = GRAPHinputLists (in);

    GRAPHshow (G);
    if (GRAPHisUndirected (G)) printf ("Undirected\n");
    else                       printf ("Directed\n");

    printf ("Vertex for degree checking: ");
    scanf (" %d", &v);
    printf ("Indegree for vertex %d: %d\n", v, GRAPHindeg (G, v));
    printf ("Outdegree for vertex %d: %d\n", v, GRAPHoutdeg (G, v));

    printf ("Vertex for isolation checking: ");
    scanf (" %d", &v);
    if (GRAPHisolated (G, v)) printf ("Vertex %d is isolated.\n", v);
    else                      printf ("Vertex %d is not isolated.\n", v);
    
    printf ("Vertices for adjacency test: ");
    scanf (" %d %d", &v, &w);
    if (GRAPHadj (G, v, w)) printf ("Vertices %d and %d are adjacent.\n", v, w);
    else                    printf ("Vertices %d and %d are not adjacent.\n", v, w);

    free (G);
    return 0;
}
