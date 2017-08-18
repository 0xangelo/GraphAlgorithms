#include <string.h>
#include "GRAPHlists.h"

int main () {
    Graph G1;
    vertex v, w;
    int error = 0;
    char c[100];
    
    printf ("Arcs or lists? ");
    while (scanf (" %s", c) != EOF) {
        if (strcmp (c, "arcs") == 0)
            G1 = GRAPHinputArcs ();
        else if (strcmp (c, "lists") == 0)
            G1 = GRAPHinputLists ();
        else {
            printf ("Invalid input (arcs/lists)\n");
            continue;
        }

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
        printf ("Arcs or lists? ");
    }
    return 0;
}
