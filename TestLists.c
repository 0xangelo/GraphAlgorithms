#include "prompt.h"
#include "GRAPHlists.h"

int main () {
    Graph G = GRAPHinit (1);
    FILE * in;
    vertex v, w;
    int error = 0, V, A, *arr, func, i;
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
            printf ("void GRAPHinsertArc (Graph G, vertex v, vertex w)\n");
            while (scanf (" %d %d", &v, &w) != EOF) {
                if (v >= 0 && w >= 0) {
                    GRAPHinsertArc (G, v, w);
                    break;
                }
            }
            break;

        case 11:
            printf ("void UGRAPHinsertArc (Graph G, vertex v, vertex w)\n");
            while (scanf (" %d %d", &v, &w) != EOF) {
                if (v >= 0 && w >= 0) {
                    UGRAPHinsertArc (G, v, w);
                    break;
                }
            }
            break;

        case 12:
            printf ("void GRAPHremoveArc (Graph G, vertex v, vertex w)\n");
            while (scanf (" %d %d", &v, &w) != EOF) {
                if (v >= 0 && w >= 0) {
                    GRAPHremoveArc (G, v, w);
                    break;
                }
            }
            break;

        case 13:
            printf ("void GRAPHdfs (Graph G)\n");
            GRAPHdfs (G);
            printf ("v       ");
            for (v = 0; v < G->V; ++v) printf ("%2d ", v);
            printf ("\npre     ");
            for (v = 0; v < G->V; ++v) printf ("%2d ", G->pre[v]);
            printf ("\npost    ");
            for (v = 0; v < G->V; ++v) printf ("%2d ", G->post[v]);
            printf ("\nparent  ");
            for (v = 0; v < G->V; ++v) printf ("%2d ", G->parent[v]);
            printf ("\n");
            break;

        case 14:
            printf ("int GRAPHindeg (Graph G, vertex v)\n");
            while (scanf (" %d", &v) != EOF) {
                if (v >= 0) {
                    printf (" %d\n", GRAPHindeg (G, v));
                    break;
                }
            }
            break;

        case 15:
            printf ("int GRAPHoutdeg (Graph G, vertex v)\n");
            while (scanf (" %d", &v) != EOF) {
                if (v >= 0) {
                    printf (" %d\n", GRAPHoutdeg (G, v));
                    break;
                }
            }
            break;

        case 16:
            printf ("int GRAPHrootedForestHeight (Graph G, vertex *p)\n");
            arr = malloc (G->V * sizeof (int));
            for (i = 0; i < G->V; ++i) error |= scanf (" %d", &arr[i]);
            printf (" %d\n", GRAPHrootedForestHeight (G, arr));
            free (arr);
            break;

        case 17:
            printf ("int UGRAPHcc (UGraph G, int *cc)\n");
            arr = malloc (G->V * sizeof (int));
            printf ("components: %2d", UGRAPHcc (G, arr));
            printf ("\nv           ");
            for (i = 0; i < G->V; ++i) printf ("%2d ", i);
            printf ("\ncc          ");
            for (i = 0; i < G->V; ++i) printf ("%2d ", arr[i]);
            printf ("\n");
            free (arr);
            break;

        case 18:
            printf ("int GRAPHscT (Graph G, int *sc)\n");
            arr = malloc (G->V * sizeof (int));
            printf ("components: %2d", GRAPHscT (G, arr));
            printf ("\nv           ");
            for (i = 0; i < G->V; ++i) printf ("%2d ", i);
            printf ("\nsc          ");
            for (i = 0; i < G->V; ++i) printf ("%2d ", arr[i]);
            printf ("\n");
            free (arr);
            break;

        case 19:
            printf ("bool GRAPHisUndirected (Graph G)\n");
            printf (GRAPHisUndirected (G) ? "Yes\n" : "No\n");
            break;

        case 20:
            printf ("bool GRAPHisolated (Graph G, vertex v)\n");
            error |= scanf (" %d", &v);
            printf (GRAPHisolated (G, v) ? "Yes\n" : "No\n");
            break;

        case 21:
            printf ("bool GRAPHadj (Graph G, vertex v, vertex w)\n");
            error |= scanf (" %d %d", &v, &w);
            printf (GRAPHadj (G, v, w) ? "Yes\n" : "No\n");
            break;

        case 22:
            printf ("bool GRAPHisTopoNumbering (Graph G, int *topo)\n");
            arr = malloc (G->V * sizeof (int));
            for (i = 0; i < G->V; ++i) error |= scanf (" %d", &arr[i]);
            printf (GRAPHisTopoNumbering (G, arr) ? "Yes\n" : "No\n");
            free (arr);
            break;

        case 23:
            printf ("bool GRAPHisTopoOrder (Graph G, vertex *vv)\n");
            arr = malloc (G->V * sizeof (int));
            free (arr);
            break;

        case 24:
            printf ("bool GRAPHreach (Graph G, vertex s, vertex t)\n");
            error |= scanf (" %d %d", &v, &w);
            printf (GRAPHreach (G, v, w) ? "Yes\n" : "No\n");
            break;

        case 25:
            printf ("bool GRAPHhasCycle (Graph G)\n");
            printf (GRAPHhasCycle (G) ? "Yes\n" : "No\n");
            break;

        case 26:
            printf ("void GRAPHshow (Graph G)\n");
            GRAPHshow (G);
            break;

        case 27:
            printf ("void UGRAPHshowKnight (Graph G, int i, int j)\n");
            error |= scanf (" %d %d", &v, &w);
            UGRAPHshowKnight (G, v, w);
            break;

        case 28:
            jump = true;
        }
    }

    GRAPHfree (G);
    if (file) free (file);
    if (command) free (command);
    return 0;
}
