#include <string.h>
#include "GRAPHmatrix.h"

int main () {
    FILE *in1, *in2;
    Graph G1, G2;
    vertex v, w;
    int error = 0;
    
    in1 = fopen ("arcos.txt", "r");
    in2 = fopen ("listas.txt", "r");
    G1 = GRAPHinputArcsFile (in1);
    G2 = GRAPHinputListsFile (in2);

    GRAPHshow (G1);
    if (GRAPHisUndirected (G1)) printf ("Undirected\n");
    else                       printf ("Directed\n");

    printf ("Vertex for degree checking: ");
    error |= scanf (" %d", &v);
    printf ("Indegree for vertex %d: %d\n", v, GRAPHindeg (G1, v));
    printf ("Outdegree for vertex %d: %d\n", v, GRAPHoutdeg (G1, v));

    printf ("Vertex for isolation checking: ");
    error |= scanf (" %d", &v);
    if (GRAPHisolated (G1, v)) printf ("Vertex %d is isolated.\n", v);
    else                      printf ("Vertex %d is not isolated.\n", v);

    printf ("Vertices for adjacency test: ");
    error |= scanf (" %d %d", &v, &w);
    if (GRAPHadj (G1, v, w)) printf ("Vertices %d and %d are adjacent.\n", v, w);
    else                    printf ("Vertices %d and %d are not adjacent.\n", v, w);

    free (G1);
    
    printf ("###############################################################\n");

    GRAPHshow (G2);
    if (GRAPHisUndirected (G2)) printf ("Undirected\n");
    else                       printf ("Directed\n");

    printf ("Vertex for degree checking: ");
    error |= scanf (" %d", &v);
    printf ("Indegree for vertex %d: %d\n", v, GRAPHindeg (G2, v));
    printf ("Outdegree for vertex %d: %d\n", v, GRAPHoutdeg (G2, v));

    printf ("Vertex for isolation checking: ");
    error |= scanf (" %d", &v);
    if (GRAPHisolated (G2, v)) printf ("Vertex %d is isolated.\n", v);
    else                      printf ("Vertex %d is not isolated.\n", v);

    printf ("Vertices for adjacency test: ");
    error |= scanf (" %d %d", &v, &w);
    if (GRAPHadj (G2, v, w)) printf ("Vertices %d and %d are adjacent.\n", v, w);
    else                    printf ("Vertices %d and %d are not adjacent.\n", v, w);

    free (G2);
    return 0;
}
