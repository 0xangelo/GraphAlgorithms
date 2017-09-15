#ifndef GRAPH
#define GRAPH "graphl.h"
#endif
#include "prompt.h"
#include GRAPH

int main () {
    Graph G = GRAPHinit (1);
    FILE * in;
    vertex v, w;
    int error = 0, V, A, E, *arr, func, i;
    char *file = NULL, *command = NULL;
    bool jump = false;
    
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
                    break;
                }
                printf ("Please insert an integer V > 0\n");
            }
            break;

        case 2:
            printf ("Graph GRAPHinputArcs (void)\n");
            GRAPHfree (G);
            G = GRAPHinputArcs ();
            break;
            
        case 3:
            printf ("Graph GRAPHinputLists (void)\n");
            GRAPHfree (G);
            G = GRAPHinputLists ();
            break;

        case 4:
            printf ("Graph GRAPHinputArcsFile (FILE *in)\n");
            file = type_file (file);
            if (strlen (file) > 0) {
                in = fopen (file, "r");
                GRAPHfree (G);
                G = GRAPHinputArcsFile (in);
                fclose (in);
            }
            break;

        case 5:
            printf ("Graph GRAPHinputListsFile (FILE *in)\n");
            file = type_file (file);
            if (strlen (file) > 0) {
                in = fopen (file, "r");
                GRAPHfree (G);
                G = GRAPHinputListsFile (in);
                fclose (in);
            }
            break;

        case 6:
            printf ("Graph UGRAPHknight ()\n");
            GRAPHfree (G);
            G = UGRAPHknight ();
            break;

        case 7:
            printf ("Graph GRAPHbuildComplete (int V)\n");
            while (scanf (" %d", &V) != EOF) {
                if (V > 0) {
                    GRAPHfree (G);
                    G = GRAPHbuildComplete (V);
                    break;
                }
            }
            break;

        case 8:
            printf ("Graph GRAPHrand1 (int V, int A)\n");
            while (scanf (" %d %d", &V, &A) != EOF) {
                if (V > 0 && A >= 0) {
                    GRAPHfree (G);
                    G = GRAPHrand1 (V, A);
                    break;
                }
            }
            break;

        case 9:
            printf ("Graph GRAPHrand2 (int V, int A)\n");
            while (scanf (" %d %d", &V, &A) != EOF) {
                if (V > 0 && A >= 0) {
                    GRAPHfree (G);
                    G = GRAPHrand1 (V, A);
                    break;
                }
            }
            break;

        case 10:
            printf ("UGraph UGRAPHrandU (int V, int E)\n");
            while (scanf (" %d %d", &V, &E) != EOF) {
                if (V > 0 && E >= 0) {
                    GRAPHfree (G);
                    G = UGRAPHrandU (V, E);
                    break;
                }
            }
            break;
            

        case 11:
            printf ("void GRAPHinsertArc (Graph G, vertex v, vertex w)\n");
            while (scanf (" %d %d", &v, &w) != EOF) {
                if (v >= 0 && w >= 0) {
                    GRAPHinsertArc (G, v, w);
                    break;
                }
            }
            break;

        case 12:
            printf ("void UGRAPHinsertArc (Graph G, vertex v, vertex w)\n");
            while (scanf (" %d %d", &v, &w) != EOF) {
                if (v >= 0 && w >= 0) {
                    UGRAPHinsertArc (G, v, w);
                    break;
                }
            }
            break;

        case 13:
            printf ("void GRAPHremoveArc (Graph G, vertex v, vertex w)\n");
            while (scanf (" %d %d", &v, &w) != EOF) {
                if (v >= 0 && w >= 0) {
                    GRAPHremoveArc (G, v, w);
                    break;
                }
            }
            break;

        case 14:
            printf ("void GRAPHdfs (Graph G)\n");
            GRAPHdfs (G);
            printf ("v     ");
            for (v = 0; v < G->V; ++v) printf ("%2d%c", v, (v == G->V - 1) ? '\n' : ' ');
            printf ("pre   ");
            for (v = 0; v < G->V; ++v) printf ("%2d%c", G->pre[v], (v == G->V - 1) ? '\n' : ' ');
            printf ("post  ");
            for (v = 0; v < G->V; ++v) printf ("%2d%c", G->post[v], (v == G->V - 1) ? '\n' : ' ');
            printf ("pred  ");
            for (v = 0; v < G->V; ++v) printf ("%2d%c", G->pred[v], (v == G->V - 1) ? '\n' : ' ');
            break;

        case 15:
            printf ("void GRAPHbfs (Graph G, vertex s)\n");
            GRAPHbfs (G);
            printf ("v     ");
            for (v = 0; v < G->V; ++v) printf ("%2d%c", v, (v == G->V - 1) ? '\n' : ' ');
            printf ("num   ");
            for (v = 0; v < G->V; ++v) printf ("%2d%c", G->num[v], (v == G->V - 1) ? '\n' : ' ');
            break;

        case 16:
            printf ("void GRAPHtopoOrder (Graph G, int *vv)\n");
            arr = malloc (G->V * sizeof (int));
            GRAPHtopoOrder (G, arr);
            for (v = 0; v < G->V; ++v)
                printf ("%2d%c", arr[v], ((v == G->V - 1)) ? '\n' : ' ');
            free (arr);
            break;

        case 17:
            printf ("void GRAPHpath (Graph G, vertex s, vertex t)\n");
            while (scanf (" %d %d", &v, &w) != EOF) {
                if (v >= 0 && w >= 0) {
                    GRAPHpath (G, v, w);
                    break;
                }
            }
            break;

        case 18:
            printf ("void UGRAPHbridges (UGraph G)\n");
            UGRAPHbridges (G);
            break;
            

        case 19:
            printf ("int GRAPHindeg (Graph G, vertex v)\n");
            while (scanf (" %d", &v) != EOF) {
                if (v >= 0) {
                    printf (" %d\n", GRAPHindeg (G, v));
                    break;
                }
            }
            break;

        case 20:
            printf ("int GRAPHoutdeg (Graph G, vertex v)\n");
            while (scanf (" %d", &v) != EOF) {
                if (v >= 0) {
                    printf (" %d\n", GRAPHoutdeg (G, v));
                    break;
                }
            }
            break;

        case 21:
            printf ("int GRAPHrootedForestHeight (Graph G, vertex *p)\n");
            arr = malloc (G->V * sizeof (int));
            for (i = 0; i < G->V; ++i) error |= scanf (" %d", &arr[i]);
            printf (" %d\n", GRAPHrootedForestHeight (G, arr));
            free (arr);
            break;

        case 22:
            printf ("int GRAPHdfsForestHeight (Graph G)\n");
            printf (" %d\n", GRAPHdfsForestHeight (G));
            break;

        case 23:
            printf ("int UGRAPHcc (UGraph G, int *cc)\n");
            arr = malloc (G->V * sizeof (int));
            printf ("components: %2d\n", UGRAPHcc (G, arr));
            printf ("v           ");
            for (i = 0; i < G->V; ++i) printf ("%2d%c", i, (i == G->V - 1) ? '\n' : ' ');
            printf ("cc          ");
            for (i = 0; i < G->V; ++i) printf ("%2d%c", arr[i], (i == G->V - 1) ? '\n' : ' ');
            free (arr);
            break;

        case 24:
            printf ("int UGRAPHccAdd (UGraph G, int *cc, vertex v, vertex w)\n");
            while (scanf (" %d %d", &v, &w) != EOF && v < 0 && w < 0) {}
            arr = malloc (G->V * sizeof (int));
            printf ("components: %2d\n", UGRAPHcc (G, arr));
            printf ("v           ");
            for (i = 0; i < G->V; ++i) printf ("%2d%c", i, (i == G->V - 1) ? '\n' : ' ');
            printf ("cc          ");
            for (i = 0; i < G->V; ++i) printf ("%2d%c", arr[i], (i == G->V - 1) ? '\n' : ' ');
            printf ("components: %2d", UGRAPHccAdd (G, arr, v, w));
            printf ("v           ");
            for (i = 0; i < G->V; ++i) printf ("%2d%c", i, (i == G->V - 1) ? '\n' : ' ');
            printf ("cc          ");
            for (i = 0; i < G->V; ++i) printf ("%2d%c", arr[i], (i == G->V - 1) ? '\n' : ' ');
            free (arr);
            break;

        case 25:
            printf ("int GRAPHscT (Graph G, int *sc)\n");
            arr = malloc (G->V * sizeof (int));
            printf ("components: %2d", GRAPHscT (G, arr));
            printf ("v           ");
            for (i = 0; i < G->V; ++i) printf ("%2d%c", i, (i == G->V - 1) ? '\n' : ' ');
            printf ("sc          ");
            for (i = 0; i < G->V; ++i) printf ("%2d%c", arr[i], (i == G->V - 1) ? '\n' : ' ');
            free (arr);
            break;

        case 26:
            printf ("int GRAPHscK (Graph G, int *sc)\n");
            arr = malloc (G->V * sizeof (int));
            printf ("components: %2d", GRAPHscK (G, arr));
            printf ("v           ");
            for (i = 0; i < G->V; ++i) printf ("%2d%c", i, (i == G->V - 1) ? '\n' : ' ');
            printf ("sc          ");
            for (i = 0; i < G->V; ++i) printf ("%2d%c", arr[i], (i == G->V - 1) ? '\n' : ' ');
            free (arr);
            break;

        case 27:
            printf ("bool GRAPHisUndirected (Graph G)\n");
            printf (GRAPHisUndirected (G) ? "Yes\n" : "No\n");
            break;

        case 28:
            printf ("bool GRAPHisolated (Graph G, vertex v)\n");
            error |= scanf (" %d", &v);
            printf (GRAPHisolated (G, v) ? "Yes\n" : "No\n");
            break;

        case 29:
            printf ("bool GRAPHadj (Graph G, vertex v, vertex w)\n");
            error |= scanf (" %d %d", &v, &w);
            printf (GRAPHadj (G, v, w) ? "Yes\n" : "No\n");
            break;

        case 30:
            printf ("bool GRAPHisTopoNumbering (Graph G, int *topo)\n");
            arr = malloc (G->V * sizeof (int));
            for (i = 0; i < G->V; ++i) error |= scanf (" %d", &arr[i]);
            printf (GRAPHisTopoNumbering (G, arr) ? "Yes\n" : "No\n");
            free (arr);
            break;

        case 31:
            printf ("bool GRAPHisTopoOrder (Graph G, vertex *vv)\n");
            arr = malloc (G->V * sizeof (int));
            for (i = 0; i < G->V; ++i) error |= scanf (" %d", &arr[i]);
            printf (GRAPHisTopoOrder (G, arr) ? "Yes\n" : "No\n");
            free (arr);
            break;

        case 32:
            printf ("bool GRAPHreach (Graph G, vertex s, vertex t)\n");
            error |= scanf (" %d %d", &v, &w);
            printf (GRAPHreach (G, v, w) ? "Yes\n" : "No\n");
            break;

        case 33:
            printf ("bool GRAPHhasCycle (Graph G)\n");
            printf (GRAPHhasCycle (G) ? "Yes\n" : "No\n");
            break;

        case 34:
            printf ("bool UGRAPHisConnected (UGraph G)\n");
            printf (UGRAPHisConnected (G) ? "Yes\n" : "No\n");
            break;

        case 35:
            printf ("void GRAPHshow (Graph G)\n");
            GRAPHshow (G);
            break;

        case 36:
            printf ("void UGRAPHshowKnight (Graph G, int i, int j)\n");
            error |= scanf (" %d %d", &v, &w);
            UGRAPHshowKnight (G, v, w);
            break;

        case 37:
            jump = true;
        }
    }

    GRAPHfree (G);
    if (file) free (file);
    if (command) free (command);
    return 0;
}
