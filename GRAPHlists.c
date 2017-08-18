#include "GRAPHlists.h"

static int cnt;

/* A função NEWnode() recebe um vértice w e o endereço next de um nó e devolve o
   endereço a de um novo nó tal que a->w == w e a->next == next. */
static link NEWnode( vertex w, link next) { 
    link a = malloc( sizeof (struct node));
    a->w = w; 
    a->next = next;     
    return a;                         
}

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIA: A função GRAPHinit() constrói um 
   grafo com vértices 0 1 .. V-1 e nenhum arco. */
Graph GRAPHinit( int V) { 
    vertex v;
    Graph G = malloc( sizeof *G);
    G->V = V; 
    G->A = 0;
    G->adj = malloc( V * sizeof (link));
    for (v = 0; v < V; ++v) 
        G->adj[v] = NULL;
    G->pre = malloc( V * sizeof v);
    return G;
}

Graph GRAPHinputArcs( void) {
    int V, A, i, v, w, error;
    Graph G;
    error = scanf (" %d %d", &V, &A);
    G = GRAPHinit(V);
    for (i = 0; i < A; ++i) {
        error |= scanf (" %d %d", &v, &w);
        GRAPHinsertArc(G, v, w);
    }
    if (error == 1) fprintf (stderr, "error\n");
    return G;
}

Graph GRAPHinputLists( void) {
    int V, i, v, w, error = 0, insert;
    char c;
    Graph G;
    error |= scanf (" %d", &V);
    G = GRAPHinit (V);
    for (i = 0; i < V; ++i) {
        error |= scanf (" %d", &v);
        w = c = insert = 0;
        while (c != '\n') {
            error |= scanf ("%c", &c);
            while (isdigit(c)) {
                insert = 1;
                w *= 10;
                w += c - '0';
                error |= scanf ("%c", &c);
            }
            if (insert) GRAPHinsertArc (G, v, w);
            w = insert = 0;
        }
    }
    return G;
}

Graph GRAPHinputArcsFile( FILE *in) {
    int V, A, i, v, w, error;
    Graph G;
    error = fscanf (in, " %d %d", &V, &A);
    G = GRAPHinit(V);
    for (i = 0; i < A; ++i) {
        error |= fscanf (in, " %d %d", &v, &w);
        GRAPHinsertArc(G, v, w);
    }
    if (error == 1) fprintf (stderr, "error\n");
    return G;
}

Graph GRAPHinputListsFile( FILE *in) {
    int V, i, v, w, error = 0, insert;
    char c;
    Graph G;
    error |= fscanf (in, " %d", &V);
    G = GRAPHinit (V);
    for (i = 0; i < V; ++i) {
        error |= fscanf (in, " %d", &v);
        w = c = insert = 0;
        while (c != '\n') {
            error |= fscanf (in, "%c", &c);
            while (isdigit(c)) {
                insert = 1;
                w *= 10;
                w += c - '0';
                error |= fscanf (in, "%c", &c);
            }
            if (insert) GRAPHinsertArc (G, v, w);
            w = insert = 0;
        }
    }
    return G;
}

Graph UGRAPHknight() {
    int i, j;
    Graph G = GRAPHinit (64);
    for (i = 0; i < 64; ++i) {
        j = i - 16 + 1;
        if (j > 0 && j % 8 > i % 8) {
            GRAPHinsertArc (G, i, j);
            GRAPHinsertArc (G, j, i);
        }
        j = i - 8 + 2;
        if (j > 0 && j % 8 > i % 8) {
            GRAPHinsertArc (G, i, j);
            GRAPHinsertArc (G, j, i);
        }
        j = i + 8 + 2;
        if (j < 64 && j % 8 > i % 8) {
            GRAPHinsertArc (G, i, j);
            GRAPHinsertArc (G, j, i);            
        }
        j = i + 16 + 1;
        if (j < 64 && j % 8 > i % 8) {
            GRAPHinsertArc (G, i, j);
            GRAPHinsertArc (G, j, i);            
        }
        j = i + 16 - 1;
        if (j < 64 && j % 8 < i % 8) {
            GRAPHinsertArc (G, i, j);
            GRAPHinsertArc (G, j, i);            
        }
        j = i + 8 - 2;
        if (j < 64 && j % 8 < i % 8) {
            GRAPHinsertArc (G, i, j);
            GRAPHinsertArc (G, j, i);            
        }
        j = i - 8 - 2;
        if (j > 0 && j % 8 < i % 8) {
            GRAPHinsertArc (G, i, j);
            GRAPHinsertArc (G, j, i);
        }
        j = i - 16 - 1;
        if (j > 0 && j % 8 < i % 8) {
            GRAPHinsertArc (G, i, j);
            GRAPHinsertArc (G, j, i);
        }
    }
    return G;
}

Graph GRAPHbuildComplete( int V) {
   Graph G;
   vertex v, w;
   G = GRAPHinit( V);
   for (v = 0; v < G->V; ++v)
       for (w = v + 1; w < G->V; ++w) {
          GRAPHinsertArc( G, v, w);
          GRAPHinsertArc( G, w, v);
       }
   return G;
}

/* A função randV() devolve um vértice aleatório do grafo G. */
vertex randV( Graph G) { 
   double r;
   r = rand( ) / (RAND_MAX + 1.0);
   return r * G->V;
}

/* Essa função constrói um grafo aleatório com vértices 0..V-1 e exatamente A
   arcos. A função supõe que A <= V*(V-1). Se A for próximo de V*(V-1), a função
   pode consumir muito tempo. (Código inspirado no Programa 17.7 de Sedgewick.) */
Graph GRAPHrand1( int V, int A) { 
   Graph G = GRAPHinit( V);
   while (G->A < A) {
      vertex v = randV( G);
      vertex w = randV( G);
      if (v != w) 
         GRAPHinsertArc( G, v, w);
   }
   return G;
}

/* Constrói um grafo aleatório com vértices 0..V-1 e número esperado de arcos
   igual a A. A função supõe que V >= 2 e A <= V*(V-1). (Código inspirado no
   Program 17.8 de Sedgewick.) */
Graph GRAPHrand2( int V, int A) { 
   double prob = (double) A / V / (V-1);
   Graph G = GRAPHinit( V);
   vertex v, w;
   for (v = 0; v < V; ++v)
      for (w = 0; w < V; ++w)
         if (v != w)
            if (rand( ) < prob*(RAND_MAX+1.0))
               GRAPHinsertArc( G, v, w);
   return G;
}

Graph GRAPHbuildRandRootedTree( int V) {
    Graph G;
    G = GRAPHinit (V);
    return G;
}

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIA: A função GRAPHinsertArc() insere um
   arco v-w no grafo G. A função supõe que v e w são distintos, positivos e 
   menores que G->V. Se o grafo já tem um arco v-w, a função não faz nada. */
void GRAPHinsertArc( Graph G, vertex v, vertex w) { 
    link a;
    for (a = G->adj[v]; a != NULL; a = a->next) 
        if (a->w == w) return;
    G->adj[v] = NEWnode( w, G->adj[v]);
    G->A++;
}

void UGRAPHinsertArc( Graph G, vertex v, vertex w) {
    GRAPHinsertArc (G, v, w);
    GRAPHinsertArc (G, w, v);
}

void GRAPHremoveArc( Graph G, vertex v, vertex w) { 
    link a, *ant;
    for (ant = &G->adj[v], a = G->adj[v]; a != NULL; ant = &a, a = a->next)
        if (a->w == w) {
            *ant = a->next;
            free (a);
            G->A--;
            return;
        }
}

/* Seja X o conjunto dos vértices x que estão ao alcance de v e têm pre[x] == -1.
   Para cada vértice x em X, a função dfsR() atribui um valor positivo a pre[x] 
   de modo que o k-ésimo vértice descoberto receba valor cnt+k.  O código supõe 
   que G é representado por uma matriz de adjacências. (Código inspirado no 
   programa 18.1 de Sedgewick.) */
static void dfsR( Graph G, vertex v) { 
   link a;
   G->pre[v] = cnt++; 
   for (a = G->adj[v]; a != NULL; a = a->next)
      if (G->pre[a->w] == -1)
         dfsR( G, a->w); 
}

/* A função GRAPHdfs() visita todos os vértices e todos os arcos do grafo G. 
   A função atribui um número de ordem pre[x] a cada vértice x: o k-ésimo 
   vértice descoberto recebe número de ordem k.  (Código inspirado no 
   programa 18.3 de Sedgewick.) */
void GRAPHdfs( Graph G) { 
   vertex v;
   cnt = 0;
   for (v = 0; v < G->V; ++v) 
      G->pre[v] = -1;
   for (v = 0; v < G->V; ++v)
      if (G->pre[v] == -1) 
         dfsR( G, v);
}

int GRAPHindeg( Graph G, vertex v) {
    int i, ans = 0;
    link a;
    for (i = 0; i < G->V; i++)
        for (a = G->adj[i]; a != NULL; a = a->next)
            if (a->w == v) ans++;
    return ans;
}

int GRAPHoutdeg( Graph G, vertex v) {
    int ans = 0;
    link a;
    for (a = G->adj[v]; a != NULL; a = a->next)
        ans++;
    return ans;
}

int GRAPHrootedForestHeight( Graph G, vertex *p) {
    int *h, *stack, top = 0, i, max = 0;
    h = malloc (G->V * sizeof (int));
    stack = malloc (G->V * sizeof (int));
    for (i = 0; i < G->V; ++i) h[i] = (i == p[i] ? 0:-1);
    for (i = 0; i < G->V; ++i) {
        while (h[i] == -1) {
            stack[top++] = i;
            i = p[i];
        }
        while (top > 0) {
            i = stack[--top];
            h[i] = h[p[i]] + 1;
        }
        max = (h[i] > max ? h[i] : max);
    }
    free (h); free (stack);
    return max;
}

bool GRAPHisUndirected( Graph G) {
    int i, w;
    link a, b;
    for (i = 0; i < G->V; ++i)
        for (a = G->adj[i]; a != NULL; a = a->next) {
            w = a->w;
            for (b = G->adj[w]; b != NULL; b = b->next)
                if (b->w == i) break;
            if (b == NULL) return false;
        }
    return true;
}

bool GRAPHisolated( Graph G, vertex v) {
    if (GRAPHindeg (G, v) > 0) return false;
    if (GRAPHoutdeg (G, v) > 0) return false;
    return true;
}

bool GRAPHadj( Graph G, vertex v, vertex w) {
    link a;
    for (a = G->adj[v]; a != NULL; a = a->next)
        if (a->w == w) return true;
    for (a = G->adj[w]; a != NULL; a = a->next)
        if (a->w == v) return true;
    return false;
}

bool GRAPHisTopoNumbering( Graph G, int *topo) {
    vertex v;
    link a;
    for (v = 0; v < G->V; ++v) 
        for (a = G->adj[v]; a != NULL; a = a->next) 
            if (topo[v] >= topo[a->w]) 
                return false;
    return true;
}

bool GRAPHisTopoOrder( Graph G, vertex *vv) {
    int *topo, i;
    topo = malloc (G->V * sizeof (int));
    for (i = 0; i < G->V; ++i)
        topo[vv[i]] = i;
    i = GRAPHisTopoNumbering( G, topo);
    free (topo);
    return i;
}

bool GRAPHreach( Graph G, vertex s, vertex t) {
    vertex v, *stack, top = 0;
    link a, *next;
    bool *visit;
    visit = malloc (G->V * sizeof (bool));
    stack = malloc (G->V * sizeof v);
    next = malloc (G->V * sizeof a);

    for (v = 0; v < G->V; ++v) visit[v] = false;
    stack[top] = s;
    next[top] = G->adj[s];
    while (top >= 0) {
        v = stack[top];
        a = next[top];
        visit[v] = true;
        if (v == t) break;

        while (a != NULL) {
            if (!visit[a->w]) {
                stack[top + 1] = a->w;
                next[top + 1] = G->adj[a->w];
                break;
            }
            a = a->next;
        }
        next[top] = a;
        if (a == NULL) top--;
        else top++;
    }
    free (visit); free (stack); free (next);
    return v == t;
}

void GRAPHshow( Graph G) { 
    vertex v;
    link a;
    for (v = 0; v < G->V; ++v) {
        printf ( "%2d:", v);
        for (a = G->adj[v]; a != NULL; a = a->next) {
            printf ( " %2d", a->w);
        }
        printf ( "\n");
    }
}

void UGRAPHshowKnight( Graph G, int i, int j) {
    vertex v, w;
    for (v = i * 8 + j, w = 0; w < G->V; ++w) {
        if (GRAPHadj (G, v, w))
            printf ("X ");
        else if (w == v)
            printf ("K ");
        else
            printf (". ");
        if (w % 8 == 7)
            printf ("\n");
    }
}

