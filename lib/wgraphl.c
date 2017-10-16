#include "wgraphl.h"

/* A lista de adjacência de um vértice v é composta por nós do tipo node.
   Cada nó da lista corresponde a um arco e contém um vizinho w de v e o
   endereço do nó seguinte da lista. Um link é um ponteiro para um node. */
typedef struct node *link;
struct node { 
    vertex w;
    int cst;
    link next; 
};

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIA: A estrutura graph representa um grafo.
   O campo adj é um ponteiro para o vetor de listas de adjacência, o campo V 
   contém o número de vértices e o campo A contém o número de arcos do grafo. */
struct graph {
    int V; 
    int A; 
    link *adj;
    int cnt1;
    int cnt2;
    int *pre;
    int *post;
    int *pred;
    int *low;
};


/* A função NEWnode() recebe um vértice w e o endereço next de um nó e devolve o
   endereço a de um novo nó tal que a->w == w e a->next == next. */
static link NEWnode (vertex w, int cst, link next) {
    link a = malloc (sizeof (struct node));
    a->w = w;
    a->cst = cst;
    a->next = next;    
    return a;                        
}

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIA: A função GRAPHinit() constrói um
   grafo com vértices 0 1 .. V-1 e nenhum arco. */
Graph GRAPHinit (int V) {
    vertex v;
    Graph G = malloc (sizeof *G);
    G->V = V;
    G->A = 0;
    G->adj = malloc (V * sizeof (link));
    for (v = 0; v < V; ++v)
        G->adj[v] = NULL;
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
    link a;
    for (a = G->adj[v]; a != NULL; a = a->next)
        if (a->w == w) return;
    G->adj[v] = NEWnode (w, cst, G->adj[v]);
    G->A++;
}

void UGRAPHinsertEdge( Graph G, vertex v, vertex w, int cst) { 
   link a;
   for (a = G->adj[v]; a != NULL; a = a->next) 
      if (a->w == w) return;
   G->adj[v] = NEWnode( w, cst, G->adj[v]);
   G->adj[w] = NEWnode( v, cst, G->adj[w]);
   G->A += 2;
}

void GRAPHremoveArc (Graph G, vertex v, vertex w) {
    link a, *ant;
    for (ant = &G->adj[v], a = G->adj[v]; a != NULL; ant = &a, a = a->next)
        if (a->w == w) {
            *ant = a->next;
            free (a);
            G->A--;
            return;
        }
}

int GRAPHvertices (Graph G) {
    return G->V;
}

int GRAPHarcs (Graph G) {
    return G->A;
}

/* Recebe um grafo G com custos positivos nos arcos e um vértice s. Armazena no 
   vetor de pais parent[] uma SPT de G com raiz s. Se um vértice v não está ao 
   alcance de s, parent[v] valerá -1. As distâncias a partir de s 
   são armazenadas no vetor dist[]. Os vetores parent[] e dist[] devem ser 
   alocados pelo usuário. (Código inspirado no Programa 20.3 de Sedgewick.) */
void GRAPHspt1 (Graph G, vertex s, vertex *parent, int *dist) {
    vertex *hook = malloc (G->V * sizeof (vertex));
    vertex v, y, z, w; link a;
    int mindist, cst;

    /* inicialização: */
    for (v = 0; v < G->V; ++v)
        parent[v] = -1, dist[v] = INFINITY;
    parent[s] = s, dist[s] = 0;
    for (a = G->adj[s]; a != NULL; a = a->next) {
        dist[a->w] = a->cst;
        hook[a->w] = s;
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
        for (a = G->adj[y]; a != NULL; a = a->next) {
            w = a->w;
            cst = a->cst;
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
    vertex v, y, w; int cst; link a;
    PriorityQueue Q;
    
    /* inicialização: */
    for (v = 0; v < G->V; ++v)
        parent[v] = -1, dist[v] = INFINITY;
    parent[s] = s, dist[s] = 0;
    Q = PQinit (G->V);
    for (a = G->adj[s]; a != NULL; a = a->next) {
        dist[a->w] = a->cst;
        PQinsert (Q, a->w, dist);
        hook[a->w] = s;
    }

    while (!PQempty (Q)) {
        y = PQdelMin (Q, dist);
        parent[y] = hook[y];
        /* atualização de dist[]: */
        for (a = G->adj[y]; a != NULL; a = a->next) {
            w = a->w;
            cst = a->cst;
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

void GRAPHshow (Graph G) {
    vertex v;
    link a;
    for (v = 0; v < G->V; ++v) 
        for (a = G->adj[v]; a != NULL; a = a->next)
            printf  ("%d %d %d\n", v, a->w, a->cst);
}

void GRAPHsave (Graph G, FILE * out) {
    vertex v; link a;

    fprintf (out, "%d %d\n", G->V, G->A);
    for (v = 0; v < G->V; ++v)
        for (a = G->adj[v]; a != NULL; a = a->next)
            fprintf (out, "%d %d %d\n", v, a->w, a->cst);
}

void GRAPHfree (Graph G) {
    vertex v;
    link a, b;
    for (v = 0; v < G->V; ++v) {
        a = G->adj[v];
        while (a != NULL) {
            b = a->next;
            free (a);
            a = b;
        }
    }
    free (G->adj);
    free (G);
}
