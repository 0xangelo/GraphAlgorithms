#ifndef GRAPH
#define GRAPH "wgraphl.h"
#endif
#include "prompt.h"
#include GRAPH

char *func_names[] = {
    "init", 
    "inputArcs",
    "inputArcsFile",
    "rand1",
    "rand2",
    "randU",
    "randGrid",
    "insertArc",
    "insertEdge",
    "removeArc",
    "vertices",
    "arcs",
    "show",
    "save",
    "quit",
    NULL
};

int main () {
    Graph G = GRAPHinit (1);
    FILE * in, * out;
    vertex v, w;
    int V, A, E, func, i, cmin, cmax;
    char *file = NULL, *command = NULL;
    bool jump = false;
    prompt_init (func_names);
    
    while (!jump) {
        command = type_prompt (command);

        for (func = 0, i = 0; func_names[i] != NULL; i++) {
            if (strcmp (command, func_names[i]) == 0) {
                func = i + 1;
                break;
            }
        }

        switch (func) {
            
        case 1:
            printf ("Graph GRAPHinit (int V)\n");
            while (scanf (" %d", &V) != EOF) {
                if (V > 0) {
                    GRAPHfree (G);
                    G = GRAPHinit (V);
                    A = 0;
                    break;
                }
                printf ("Please insert an integer V > 0\n");
            }
            break;

        case 2:
            printf ("Graph GRAPHinputArcs (void)\n");
            GRAPHfree (G);
            G = GRAPHinputArcs ();
            V = GRAPHvertices (G);
            A = GRAPHarcs (G);
            break;
            
        case 3:
            printf ("Graph GRAPHinputArcsFile (FILE *in)\n");
            file = type_file (file);
            if (strlen (file) > 0) {
                in = fopen (file, "r");
                GRAPHfree (G);
                G = GRAPHinputArcsFile (in);
                V = GRAPHvertices (G);
                A = GRAPHarcs (G);
                fclose (in);
            }
            break;

        case 4:
            printf ("Graph GRAPHrand1 (int V, int A, int cmin, int cmax)\n");
            while (scanf (" %d %d %d %d", &V, &A, &cmin, &cmax) != EOF) {
                if (V > 0 && A >= 0) {
                    GRAPHfree (G);
                    G = GRAPHrand1 (V, A, cmin, cmax);
                    break;
                }
            }
            break;

        case 5:
            printf ("Graph GRAPHrand2 (int V, int A, int cmin, int cmax)\n");
            while (scanf (" %d %d %d %d", &V, &A, &cmin, &cmax) != EOF) {
                if (V > 0 && A >= 0) {
                    GRAPHfree (G);
                    G = GRAPHrand1 (V, A, cmin, cmax);
                    break;
                }
            }
            break;

        case 6:
            printf ("UGraph UGRAPHrandU (int V, int E, int cmin, int cmax)\n");
            while (scanf (" %d %d %d %d", &V, &E, &cmin, &cmax) != EOF) {
                if (V > 0 && E >= 0) {
                    GRAPHfree (G);
                    G = UGRAPHrandU (V, E, cmin, cmax);
                    break;
                }
            }
            break;
            

        case 7:
            printf ("UGRAPHrandGrid (int N, int cmin, int cmax)\n");
            while (scanf (" %d %d %d", &V, &cmin, &cmax) != EOF) {
                if (V > 0) {
                    GRAPHfree (G);
                    G = UGRAPHrandGrid (V, cmin, cmax);
                    break;
                }
            }
            

        case 8:
            printf ("void GRAPHinsertArc (Graph G, vertex v, vertex w, int cst)\n");
            while (scanf (" %d %d %d", &v, &w, &cmin) != EOF) {
                if (v >= 0 && w >= 0) {
                    GRAPHinsertArc (G, v, w, cmin);
                    A = GRAPHarcs (G);
                    break;
                }
            }
            break;

        case 9:
            printf ("void UGRAPHinsertEdge (Graph G, vertex v, vertex w, int cst)\n");
            while (scanf (" %d %d %d", &v, &w, &cmin) != EOF) {
                if (v >= 0 && w >= 0) {
                    UGRAPHinsertEdge (G, v, w, cmin);
                    A = GRAPHarcs (G);
                    break;
                }
            }
            break;

        case 10:
            printf ("void GRAPHremoveArc (Graph G, vertex v, vertex w)\n");
            while (scanf (" %d %d", &v, &w) != EOF) {
                if (v >= 0 && w >= 0) {
                    GRAPHremoveArc (G, v, w);
                    A = GRAPHarcs (G);
                    break;
                }
            }
            break;

        case 11:
            printf ("int GRAPHvertices (Graph G)\n");
            printf (" %d\n", GRAPHvertices (G));
            break;

        case 12:
            printf ("int GRAPHarcs (Graph G)\n");
            printf (" %d\n", GRAPHarcs (G));
            break;

        case 13:
            printf ("void GRAPHshow (Graph G)\n");
            GRAPHshow (G);
            break;

        case 14:
            printf ("void GRAPHsave (Graph G, FILE * out)\n");
            file = type_file (file);
            if (strlen (file) > 0) {
                out = fopen (file, "w");
                GRAPHsave (G, out);
                fclose (out);
            }
            break;

        case 15:
            jump = true;
        }
    }

    GRAPHfree (G);
    if (file) free (file);
    if (command) free (command);
    return 0;
}
