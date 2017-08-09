#include "GRAPHlists.h"
/* A função NEWnode() recebe um vértice w e o endereço next de um nó e devolve o endereço a de um novo nó tal que a->w == w e a->next == next. */

static link NEWnode( vertex w, link next) { 
    link a = malloc( sizeof (struct node));
    a->w = w; 
    a->next = next;     
    return a;                         
}
/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIA: A função GRAPHinit() constrói um grafo com vértices 0 1 .. V-1 e nenhum arco. */

Graph GRAPHinit( int V) { 
    vertex v;
    Graph G = malloc( sizeof *G);
    G->V = V; 
    G->A = 0;
    G->adj = malloc( V * sizeof (link));
    for (v = 0; v < V; ++v) 
        G->adj[v] = NULL;
    return G;
}
/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIA: A função GRAPHinsertArc() insere um arco v-w no grafo G. A função supõe que v e w são distintos, positivos e menores que G->V. Se o grafo já tem um arco v-w, a função não faz nada. */

void GRAPHinsertArc( Graph G, vertex v, vertex w) { 
    link a;
    for (a = G->adj[v]; a != NULL; a = a->next) 
        if (a->w == w) return;
    G->adj[v] = NEWnode( w, G->adj[v]);
    G->A++;
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

Graph GRAPHinputArcs( FILE *in) {
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

Graph GRAPHinputLists( FILE *in) {
    int V, i, v, error;
    char c;
    Graph G;
    error = fscanf (in, " %d", &V);
    G = GRAPHinit (V);
    for (i = 0; i < V; ++i) {
        error |= fscanf (in, " %d", &v);
        error |= fscanf (in, "%c", &c);
        while (c != '\n') {
            GRAPHinsertArc (G, v, c - '0');
            error |= fscanf (in, "%c", &c);
        }
    }
    if (error == 1) fprintf (stderr, "error\n");
    return G;
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

/* Essa função constrói um grafo aleatório com vértices 0..V-1 e exatamente A arcos. A função supõe que A <= V*(V-1). Se A for próximo de V*(V-1), a função pode consumir muito tempo. (Código inspirado no Programa 17.7 de Sedgewick.) */

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

/* Constrói um grafo aleatório com vértices 0..V-1 e número esperado de arcos igual a A. A função supõe que V >= 2 e A <= V*(V-1). (Código inspirado no Program 17.8 de Sedgewick.) */

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
