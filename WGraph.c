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
    "spt1",
    "spt2",
    "distSet",
    "quit",
    NULL
};

int main () {
    Graph G = GRAPHinit (1);
    FILE * in, * out;
    vertex *parent, *dist;
    vertex v, w;
    int V, A, E;
    int func, i;
    int cmin, cmax;
    int insert, error = 0;
    char *file = NULL, *command = NULL;
    char c;
    bool jump = false;
    bool *S, *T;
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
            printf ("void GRAPHspt1 (Graph G, vertex s, vertex *parent, int *dist)\n");
            parent = malloc (V * sizeof (vertex));
            dist = malloc (V * sizeof (vertex));
            scanf (" %d", &v);
            GRAPHspt1 (G, v, parent, dist);
            for (printf ("v     "), v = 0; v < V; ++v)
                printf ("%2d%c", v, (v == V - 1) ? '\n' : ' ');
    
            for (printf ("dist  "), v = 0; v < V; ++v)
                printf ("%2d%c", dist[v], (v == V - 1) ? '\n' : ' ');
    
            for (printf ("parent"), v = 0; v < V; ++v)
                printf ("%2d%c", parent[v], (v == V - 1) ? '\n' : ' ');
            
            free (parent);
            free (dist);
            break;

        case 16:
            printf ("void GRAPHspt2 (Graph G, vertex s, vertex *parent, int *dist)\n");
            parent = malloc (V * sizeof (vertex));
            dist = malloc (V * sizeof (vertex));
            scanf (" %d", &v);
            GRAPHspt2 (G, v, parent, dist);
            for (printf ("v     "), v = 0; v < V; ++v)
                printf ("%2d%c", v, (v == V - 1) ? '\n' : ' ');
    
            for (printf ("dist  "), v = 0; v < V; ++v)
                printf ("%2d%c", dist[v], (v == V - 1) ? '\n' : ' ');
    
            for (printf ("parent"), v = 0; v < V; ++v)
                printf ("%2d%c", parent[v], (v == V - 1) ? '\n' : ' ');
            
            free (parent);
            free (dist);
            break;

        case 17:
            printf ("int GRAPHdistSet (Graph G, bool *S, bool *T)\n");
            S = malloc (V * sizeof (bool));
            T = malloc (V * sizeof (bool));
            for (v = 0; v < V; ++v) S[v] = T[v] = false;

            printf ("Vertices in S: ");
            w = c = insert = 0;
            while (c != '\n') {
                error |= scanf ("%c", &c);
                while (isdigit(c)) {
                    insert = 1;
                    w *= 10;
                    w += c - '0';
                    error |= scanf ("%c", &c);
                }
                if (insert) S[w] = true;
                w = insert = 0;
            }
            
            printf ("Vertices in T: ");
            w = c = insert = 0;
            while (c != '\n') {
                error |= scanf ("%c", &c);
                while (isdigit(c)) {
                    insert = 1;
                    w *= 10;
                    w += c - '0';
                    error |= scanf ("%c", &c);
                }
                if (insert) T[w] = true;
                w = insert = 0;
            }

            printf (" %d\n", GRAPHdistSet (G, S, T));
            free (S);
            free (T);
            break;

        case 18:
            jump = true;
        }
    }

    GRAPHfree (G);
    if (file) free (file);
    if (command) free (command);
    return 0;
}
