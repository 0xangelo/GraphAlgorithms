#include "wgraphm.h"

static arc ARC( vertex v, vertex w, int cst) {
   arc a;
   a.v = v, a.w = w;
   a.cst = cst;
   return a;
}

typedef struct { 
    vertex v, w; 
    int cst; 
} edge;

/* static edge EDGE( vertex v, vertex w, int cst) { */
/*    edge e; */
/*    e.v = v, e.w = w; */
/*    e.cst = cst; */
/*    return e; */
/* } */

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A estrutura graph representa
   um grafo. O campo adj é um ponteiro para a matriz de adjacências do 
   grafo. O campo V contém o número de vértices e o campo A contém o 
   número de arcos do grafo. */
struct graph {
    int V; 
    int A; 
    int **adj;
};

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função MATRIXint() aloca uma matriz
   com linhas 0..r-1 e colunas 0..c-1. Cada elemento da matriz recebe valor val. */
static int **MATRIXint (int r, int c, int val) {
    vertex i, j;
    int **m = malloc (r * sizeof (int *));
    for (i = 0; i < r; ++i)
        m[i] = malloc (c * sizeof (int));
    for (i = 0; i < r; ++i)
        for (j = 0; j < c; ++j)
            m[i][j] = val;
    return m;
}

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função GRAPHinit() constrói um
   grafo com vértices 0 1 .. V-1 e nenhum arco. */
Graph GRAPHinit (int V) {
    Graph G = malloc (sizeof *G);
    G->V = V;
    G->A = 0;
    G->adj = MATRIXint (V, V, INFINITY);
    return G;
}

Graph GRAPHinputArcs (void) {
    int V, A, i, v, w, cst, error;
    Graph G;
    error = scanf (" %d %d", &V, &A);
    G = GRAPHinit(V);
    for (i = 0; i < A; ++i) {
        error |= scanf (" %d %d %d", &v, &w, &cst);
        GRAPHinsertArc(G, v, w, cst);
    }
    if (error == 1) fprintf (stderr, "error\n");
    return G;
}

Graph GRAPHinputArcsFile (FILE *in) {
    int V, A, i, v, w, cst, error;
    Graph G;
    error = fscanf (in, " %d %d", &V, &A);
    G = GRAPHinit(V);
    for (i = 0; i < A; ++i) {
        error |= fscanf (in, " %d %d %d", &v, &w, &cst);
        GRAPHinsertArc(G, v, w, cst);
    }
    if (error == 1) fprintf (stderr, "error\n");
    return G;
}

/* A função randV() devolve um vértice aleatório do grafo G. */
static vertex randV (Graph G) {
    double r;
    r = rand () / (RAND_MAX + 1.0);
    return r * G->V;
}

static vertex randC (int cmin, int cmax) {
    double r;
    r = rand () / (RAND_MAX + 1.0);
    return cmin + r * (cmax - cmin);
}

/* Essa função constrói um grafo aleatório com vértices 0..V-1 e exatamente A
   arcos. A função supõe que A <= V*(V-1). Se A for próximo de V*(V-1), a função
   pode consumir muito tempo. (Código inspirado no Programa 17.7 de Sedgewick.) */
Graph GRAPHrand1 (int V, int A, int cmin, int cmax) {
    Graph G = GRAPHinit (V);
    vertex v, w; int cst;
    srand (time (NULL));
    while (G->A < A) {
        v = randV (G);
        w = randV (G);
        cst = randC (cmin, cmax);
        if (v != w)
            GRAPHinsertArc (G, v, w, cst);
    }
    return G;
}

/* Constrói um grafo aleatório com vértices 0..V-1 e número esperado de arcos
   igual a A. A função supõe que V >= 2 e A <= V*(V-1). (Código inspirado no
   Program 17.8 de Sedgewick.) */
Graph GRAPHrand2 (int V, int A, int cmin, int cmax) {
    double prob = (double) A / V / (V-1);
    Graph G = GRAPHinit (V);
    vertex v, w;
    srand (time (NULL));
    for (v = 0; v < V; ++v)
        for (w = 0; w < V; ++w)
            if (v != w)
                if (rand () < prob*(RAND_MAX+1.0))
                    GRAPHinsertArc (G, v, w, randC (cmin, cmax));
    return G;
}

/* Constrói o inverso do grafo G. */
Graph GRAPHreverse (Graph G) {
    vertex v, w;
    Graph GR = GRAPHinit (G->V);
    for (v = 0; v < G->V; ++v)
        for (w = 0; w < G->V; ++w) {
            if (G->adj[v][w] != INFINITY) GRAPHinsertArc (GR, w, v, G->adj[v][w]);
        }
    return GR;
}

UGraph UGRAPHrandU (int V, int E, int cmin, int cmax) {
    double prob = (double) E / V / (V-1);
    UGraph G = GRAPHinit (V);
    vertex v, w;
    for (v = 0; v < V; ++v)
        for (w = 0; w < V; ++w)
            if (v != w)
                if (rand () < prob*(RAND_MAX+1.0))
                    UGRAPHinsertEdge (G, v, w, randC (cmin, cmax));
    return G;
}

UGraph UGRAPHrandGrid (int N, int cmin, int cmax) {
    UGraph G = GRAPHinit (N * N);
    vertex v, V = N * N;
    srand (time (NULL));
    for (v = 0; v < V; ++v) {
        if (v > N)
            GRAPHinsertArc (G, v, v - N, randC (cmin, cmax));
        if (v < V - N)
            GRAPHinsertArc (G, v, v + N, randC (cmin, cmax));
        if (v % N > 0)
            GRAPHinsertArc (G, v, v - 1, randC (cmin, cmax));
        if (v % N < N - 1)
            GRAPHinsertArc (G, v, v + 1, randC (cmin, cmax));
    }
    return G;
}

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIA: A função GRAPHinsertArc() insere um
   arco v-w no grafo G. A função supõe que v e w são distintos, positivos e
   menores que G->V. Se o grafo já tem um arco v-w, a função não faz nada. */
void GRAPHinsertArc (Graph G, vertex v, vertex w, int cst) {
    if (G->adj[v][w] != INFINITY) return;
    G->adj[v][w] = cst;
    G->A++;
}

void UGRAPHinsertEdge( Graph G, vertex v, vertex w, int cst) { 
    if (G->adj[v][w] != INFINITY) return;
    G->adj[v][w] = cst;
    G->adj[w][v] = cst;
    G->A += 2;
}

void GRAPHremoveArc (Graph G, vertex v, vertex w) {
    if (G->adj[v][w] == INFINITY) return;
    G->adj[v][w] = INFINITY;
    G->A--;
}

int GRAPHvertices (Graph G) {
    return G->V;
}

int GRAPHarcs (Graph G) {
    return G->A;
}

arc *GRAPHallArcs (Graph G) {
    vertex v, w; int n = 0;
    arc *list = malloc (G->A * sizeof (arc));
    for (v = 0; v < G->V; ++v) 
        for (w = 0; w < G->V; ++w)
            if (G->adj[v][w] != INFINITY) list[n++] = ARC (v, w, G->adj[v][w]);
    return list;
}

/* Recebe um grafo G com custos positivos nos arcos e um vértice s. Armazena no 
   vetor de pais parent[] uma SPT de G com raiz s. Se um vértice v não está ao 
   alcance de s, parent[v] valerá -1. As distâncias a partir de s 
   são armazenadas no vetor dist[]. Os vetores parent[] e dist[] devem ser 
   alocados pelo usuário. (Código inspirado no Programa 20.3 de Sedgewick.) */
void GRAPHspt1 (Graph G, vertex s, vertex *parent, int *dist) {
    vertex *hook = malloc (G->V * sizeof (vertex));
    vertex v, y, z, w;
    int mindist, cst;

    /* inicialização: */
    for (v = 0; v < G->V; ++v)
        parent[v] = -1, dist[v] = INFINITY;
    parent[s] = s, dist[s] = 0;
    for (w = 0; w < G->V; ++w) 
        if (G->adj[s][w] != INFINITY) {
            dist[w] = G->adj[s][w];
            hook[w] = s;
        }

    while (true) {
        /* cálculo de y: */
        mindist = INFINITY;
        for (z = 0; z < G->V; ++z)
            if (parent[z] == -1 && dist[z] < mindist)
                mindist = dist[z], y = z;
        if (mindist == INFINITY) break;
        parent[y] = hook[y];
        /* atualização de dist[]: */
        for (w = 0; w < G->V; ++w) 
            if (G->adj[y][w] != INFINITY) {
                cst = G->adj[y][w];
                if (!(dist[y] + cst >= dist[w])) {
                    dist[w] = dist[y] + cst; /* relaxa y-w */
                    hook[w] = y;
                }
            }
    }
    free (hook);
}

/* Recebe um grafo G com custos positivos nos arcos e um vértice s e armazena no
   vetor de pais parent[] uma SPT de G com raiz s. Se um vértice v não está ao 
   alcance de s, parent[v] valerá -1. As distâncias a partir de s são armazenadas
   no vetor dist[]. Os vetores parent[] e dist[] devem ser alocados pelo usuário.
   (Código inspirado nos Programas 20.4 e 21.1 de Sedgewick.) */
void GRAPHspt2 (Graph G, vertex s, vertex *parent, int *dist) {
    vertex *hook = malloc (G->V * sizeof (vertex));
    vertex v, y, w; int cst;
    PriorityQueue Q;
    
    /* inicialização: */
    for (v = 0; v < G->V; ++v)
        parent[v] = -1, dist[v] = INFINITY;
    parent[s] = s, dist[s] = 0;
    Q = PQinit (G->V);
    for (w = 0; w < G->V; ++w) 
        if (G->adj[s][w] != INFINITY) {
            dist[w] = G->adj[s][w];
            PQinsert (Q, w, dist);
            hook[w] = s;
        }

    while (!PQempty (Q)) {
        y = PQdelMin (Q, dist);
        parent[y] = hook[y];
        /* atualização de dist[]: */
        for (w = 0; w < G->V; ++w) 
            if (G->adj[y][w] != INFINITY) {
                cst = G->adj[y][w];
                if (dist[w] == INFINITY) {
                    dist[w] = dist[y] + cst; /* relaxa y-w */
                    PQinsert (Q, w, dist);
                    hook[w] = y;
                }
                else if (!(dist[y] + cst >= dist[w])) {
                    dist[w] = dist[y] + cst; /* relaxa y-w */
                    PQdec (Q, w, dist);
                    hook[w] = y;
                }
            }
    }
    PQfree (Q);
    free (hook);
}

int GRAPHdistSet (Graph G, bool *S, bool *T) {
    vertex *hook = malloc (G->V * sizeof (vertex));
    vertex v, y, w; int cst;
    PriorityQueue Q;
    
    /* inicialização: */
    int *parent = malloc (G->V * sizeof (vertex));
    int *dist = malloc (G->V * sizeof (vertex));
    Q = PQinit (G->V);
    for (v = 0; v < G->V; ++v)
        if (S[v]) hook[v] = v, dist[v] = 0, PQinsert (Q, v, dist);
        else parent[v] = -1, dist[v] = INFINITY;

    while (!PQempty (Q)) {
        y = PQdelMin (Q, dist);
        parent[y] = hook[y];
        /* atualização de dist[]: */
        for (w = 0; w < G->V; ++w) 
            if (G->adj[y][w] != INFINITY) {
                cst = G->adj[y][w];
                if (dist[w] == INFINITY) {
                    dist[w] = dist[y] + cst; /* relaxa y-w */
                    PQinsert (Q, w, dist);
                    hook[w] = y;
                }
                else if (!(dist[y] + cst >= dist[w])) {
                    dist[w] = dist[y] + cst; /* relaxa y-w */
                    PQdec (Q, w, dist);
                    hook[w] = y;
                }
            }
    }
    for (y = INFINITY, v = 0; v < G->V; ++v)
        if (T[v] && (y == INFINITY || dist[v] < y)) y = dist[v];

    PQfree (Q);
    free (hook);
    free (parent);
    free (dist);
    return y;
}

arc GRAPHcriticalArc (Graph G, vertex s, vertex t) {
    Graph GR = GRAPHreverse (G);
    vertex v, w, x, y;
    int *parent = malloc (G->V * sizeof (vertex));
    int *dist = malloc (G->V * sizeof (vertex));
    int cst, red_cst, min_cst, max_cst = -INFINITY;

    GRAPHspt2 (G, s, parent, dist);

    for (w = t; w != parent[w]; w = parent[w]) {
        min_cst = INFINITY;
        for (v = 0; v < GR->V; ++v) 
            if (GR->adj[w][v] != INFINITY) {
                cst = GR->adj[w][v];
                if (v == parent[w]) continue;
                red_cst = (dist[v] == INFINITY) ? INFINITY : dist[v] + cst - dist[w];
                if (red_cst < min_cst) min_cst = red_cst;
            }
        if (min_cst > max_cst) max_cst = min_cst, x = parent[w], y = w;
    }

    GRAPHfree (GR);
    free (parent);
    free (dist);
    return ARC (x, y, dist[y] - dist[x]);
}

void GRAPHshow (Graph G) {
    vertex v, w;
    for (v = 0; v < G->V; ++v) 
        for (w = 0; w < G->V; ++w)
            if (G->adj[v][w] != INFINITY) printf  ("%d %d %d\n", v, w, G->adj[v][w]);
}

void GRAPHsave (Graph G, FILE * out) {
    vertex v, w;

    fprintf (out, "%d %d\n", G->V, G->A);
    for (v = 0; v < G->V; ++v)
        for (w = 0; w < G->V; ++w)
            if (G->adj[v][w] != INFINITY)
                fprintf (out, "%d %d %d\n", v, w, G->adj[v][w]);
}

void GRAPHfree (Graph G) {
    vertex i;
    for (i = 0; i < G->V; i++)
        free (G->adj[i]);
    free (G->adj);
    free (G);
}
