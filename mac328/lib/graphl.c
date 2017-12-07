#include "graphl.h"

/* A lista de adjacência de um vértice v é composta por nós do tipo node.
   Cada nó da lista corresponde a um arco e contém um vizinho w de v e o
   endereço do nó seguinte da lista. Um link é um ponteiro para um node. */
typedef struct node *link;
struct node { 
    vertex w; 
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
static link NEWnode (vertex w, link next) {
    link a = malloc (sizeof (struct node));
    a->w = w;
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

Graph GRAPHinputLists (void) {
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

Graph GRAPHinputArcsFile (FILE *in) {
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

Graph GRAPHinputListsFile (FILE *in) {
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

Graph GRAPHbuildComplete (int V) {
    Graph G;
    vertex v, w;
    G = GRAPHinit (V);
    for (v = 0; v < G->V; ++v)
        for (w = v + 1; w < G->V; ++w) {
            GRAPHinsertArc (G, v, w);
            GRAPHinsertArc (G, w, v);
        }
    return G;
}

/* A função randV() devolve um vértice aleatório do grafo G. */
static vertex randV (Graph G) {
    double r;
    r = rand () / (RAND_MAX + 1.0);
    return r * G->V;
}

/* Essa função constrói um grafo aleatório com vértices 0..V-1 e exatamente A
   arcos. A função supõe que A <= V*(V-1). Se A for próximo de V*(V-1), a função
   pode consumir muito tempo. (Código inspirado no Programa 17.7 de Sedgewick.) */
Graph GRAPHrand1 (int V, int A) {
    Graph G = GRAPHinit (V);
    vertex v, w;
    srand (time (NULL));
    while (G->A < A) {
        v = randV (G);
        w = randV (G);
        if (v != w)
            GRAPHinsertArc (G, v, w);
    }
    return G;
}

/* Constrói um grafo aleatório com vértices 0..V-1 e número esperado de arcos
   igual a A. A função supõe que V >= 2 e A <= V*(V-1). (Código inspirado no
   Program 17.8 de Sedgewick.) */
Graph GRAPHrand2 (int V, int A) {
    double prob = (double) A / V / (V-1);
    Graph G = GRAPHinit (V);
    vertex v, w;
    srand (time (NULL));
    for (v = 0; v < V; ++v)
        for (w = 0; w < V; ++w)
            if (v != w)
                if (rand () < prob*(RAND_MAX+1.0))
                    GRAPHinsertArc (G, v, w);
    return G;
}

Graph GRAPHbuildRandRootedTree (int V) {
    Graph G;
    G = GRAPHinit (V);
    return G;
}

/* Constrói o inverso do grafo G. */
Graph GRAPHreverse (Graph G) {
    vertex v, w; link a;
    Graph GR = GRAPHinit (G->V);
    for (v = 0; v < G->V; ++v)
        for (a = G->adj[v]; a != NULL; a = a->next) {
            w = a->w;
            GRAPHinsertArc (GR, w, v);
        }
    return GR;
}

UGraph UGRAPHrandU (int V, int E) {
    double prob = (double) E / V / (V-1);
    UGraph G = GRAPHinit (V);
    vertex v, w;
    for (v = 0; v < V; ++v)
        for (w = 0; w < V; ++w)
            if (v != w)
                if (rand () < prob*(RAND_MAX+1.0))
                    UGRAPHinsertArc (G, v, w);
    return G;
}

UGraph UGRAPHgrid (int N) {
    vertex v, V = N * N;
    UGraph G = GRAPHinit (V);
    for (v = 0; v < V; ++v) {
        if (v > N)
            GRAPHinsertArc (G, v, v - N);
        if (v < V - N)
            GRAPHinsertArc (G, v, v + N);
        if (v % N > 0)
            GRAPHinsertArc (G, v, v - 1);
        if (v % N < N - 1)
            GRAPHinsertArc (G, v, v + 1);
    }
    return G;
}

UGraph UGRAPHgridDiagonals (int N) {
    vertex v, V = N * N;
    UGraph G = UGRAPHgrid (N);
    for (v = 0; v < V; ++v) {
        if (v > N && v % N > 0)
            GRAPHinsertArc (G, v, v - N - 1);
        if (v > N && v % N < N - 1)
            GRAPHinsertArc (G, v, v - N + 1);
        if (v < V - N && v % N > 0)
            GRAPHinsertArc (G, v, v + N - 1);
        if (v < V - N && v % N < N - 1)
            GRAPHinsertArc (G, v, v + N + 1);
    }
    return G;
}

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIA: A função GRAPHinsertArc() insere um
   arco v-w no grafo G. A função supõe que v e w são distintos, positivos e
   menores que G->V. Se o grafo já tem um arco v-w, a função não faz nada. */
void GRAPHinsertArc (Graph G, vertex v, vertex w) {
    link a;
    for (a = G->adj[v]; a != NULL; a = a->next)
        if (a->w == w) return;
    G->adj[v] = NEWnode (w, G->adj[v]);
    G->A++;
}

void UGRAPHinsertArc (Graph G, vertex v, vertex w) {
    GRAPHinsertArc (G, v, w);
    GRAPHinsertArc (G, w, v);
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

/* Seja X o conjunto dos vértices x que estão ao alcance de v e têm pre[x] == -1.
   Para cada vértice x em X, a função dfsR() atribui um valor positivo a pre[x]
   de modo que o k-ésimo vértice descoberto receba valor cnt+k.  O código supõe
   que G é representado por uma matriz de adjacências. (Código inspirado no
   programa 18.1 de Sedgewick.) */
static void dfsR (Graph G, vertex v) {
    link a;
    G->pre[v] = G->cnt1++;
    for (a = G->adj[v]; a != NULL; a = a->next)
        if (G->pre[a->w] == -1) {
            G->pred[a->w] = v;
            dfsR (G, a->w);
        }
    G->post[v] = G->cnt2++;
}

static void initDfs (Graph G) {
    vertex v;
    G->pre = malloc (G->V * sizeof v);
    G->post = malloc (G->V * sizeof v);
    G->pred = malloc (G->V * sizeof v);
    G->cnt1 = G->cnt2 = 0;
    for (v = 0; v < G->V; ++v)
        G->pre[v] = G->post[v] = -1;
}

static void freeDfs (Graph G) {
    if (G->pre) free (G->pre);
    if (G->post) free (G->post);
    if (G->pred) free (G->pred);
}

/* A função GRAPHdfs() visita todos os vértices e todos os arcos do grafo G.
   A função atribui um número de ordem pre[x] a cada vértice x: o k-ésimo
   vértice descoberto recebe número de ordem k.  (Código inspirado no
   programa 18.3 de Sedgewick.) */
void GRAPHdfs (Graph G) {
    vertex v;
    initDfs (G);
    
    for (v = 0; v < G->V; ++v)
        if (G->pre[v] == -1) {
            G->pred[v] = v;
            dfsR (G, v);
        }

    for (printf ("v     "), v = 0; v < G->V; ++v)
        printf ("%2d%c", v, (v == G->V - 1) ? '\n' : ' ');
    
    for (printf ("pre   "), v = 0; v < G->V; ++v)
        printf ("%2d%c", G->pre[v], (v == G->V - 1) ? '\n' : ' ');
    
    for (printf ("post  "), v = 0; v < G->V; ++v)
        printf ("%2d%c", G->post[v], (v == G->V - 1) ? '\n' : ' ');
    
    for (printf ("pred  "), v = 0; v < G->V; ++v)
        printf ("%2d%c", G->pred[v], (v == G->V - 1) ? '\n' : ' ');

    freeDfs (G);
}

/* A função GRAPHbfs() implementa o algoritmo de busca em largura. Ela visita
   todos os vértices do grafo G que estão ao alcance do vértice s.  A ordem em
   que os vértices são descobertos é registrada no vetor num[]. Esta versão da
   função supõe que o grafo G é representado por listas de adjacência.  (Código
   inspirado no programa 18.9 de Sedgewick.) */
void GRAPHbfs (Graph G, vertex s) {
    vertex v; link a; Queue Q;
    int cnt = 0;
    int *num = malloc (G->V * sizeof v);
    for (v = 0; v < G->V; ++v) num[v] = -1;
    Q = QUEUEinit (G->V);
    num[s] = cnt++;
    QUEUEput(Q, s);

    while (!QUEUEempty (Q)) {
        v = QUEUEget (Q);
        for (a = G->adj[v]; a != NULL; a = a->next)
            if (num[a->w] == -1) {
                num[a->w] = cnt++;
                QUEUEput (Q, a->w);
            }
    }

    for (printf ("v     "), v = 0; v < G->V; ++v)
        printf ("%2d%c", v, (v == G->V - 1) ? '\n' : ' ');
    
    for (printf ("num   "), v = 0; v < G->V; ++v)
        printf ("%2d%c", num[v], (v == G->V - 1) ? '\n' : ' ');

    free (num);
    QUEUEfree (Q);
}

/* Para cada vértice v do grafo G, esta função armazena em dist[v] a distância
   de s a v.  Também armazena em parent[] o vetor de pais da árvore de caminhos
   mínimos. Esta versão da função supõe que o grafo G é representado por listas
   de adjacência.  (Código inspirado no programa 18.9 de Sedgewick.) */
void GRAPHminPaths (Graph G, vertex s, int *pred, int *dist) {
    const int INFINITY = G->V;
    vertex v, w; link a; Queue Q;
    for (v = 0; v < G->V; ++v)
        pred[v] = -1, dist[v] = INFINITY;
    Q = QUEUEinit (G->V);
    dist[s] = 0;
    pred[s] = s;
    QUEUEput (Q, s);

    while (!QUEUEempty (Q)) {
        v = QUEUEget (Q);
        for (a = G->adj[v]; a != NULL; a = a->next) {
            w = a->w;
            if (pred[w] == -1) {
                pred[w] = v;
                dist[w] = dist[v] + 1;
                QUEUEput (Q, w);
            }
        }
    }

    QUEUEfree (Q);
}

void GRAPHtopoOrder (Graph G, int *vv) {
    vertex v;
    initDfs (G);

    for (v = 0; v < G->V; ++v)
        if (G->pre[v] == -1) {
            G->pred[v] = v;
            dfsR (G, v);
        }

    for (v = 0; v < G->V; ++v)
        vv[G->V - 1 - G->post[v]] = v;

    freeDfs (G);
}

void GRAPHpath (Graph G, vertex s, vertex t) {
    vertex v; Stack S = STACKinit (G->V);
    initDfs (G);
    G->pred[s] = s;
    dfsR (G, s);

    if (G->pre[t] == -1) {
        for (v = 0; v < G->V; ++v)
            if (G->pre[v] != -1)
                printf (" %2d", v);
        printf ("\n");
    }
    else {
        for (v = t; v != G->pred[v]; STACKput (S, v), v = G->pred[v]);
        for (printf ("%2d", s); !STACKempty (S); printf (" %2d", STACKget (S)));
        printf ("\n");
    }

    STACKfree (S);
    freeDfs (G);
}

static void bridgesR (Graph G, vertex v) {
    vertex w; link a; int min;
    G->pre[v] = G->cnt1++;
    min = G->pre[v];
    for (a = G->adj[v]; a != NULL; a = a->next) {
        w = a->w;
        if (w == G->pred[v]) continue;
        if (G->pre[w] == -1) {
            G->pred[w] = v;
            bridgesR (G, w);
            if (G->low[w] < min) min = G->low[w];
        }
        else if (G->pre[w] < G->pre[v]) {
            if (G->pre[w] < min) min = G->pre[w];
        }
    }
    G->low[v] = min;
    if (G->pred[v] != v && G->low[v] > G->pre[G->pred[v]])
        printf ("%d-%d\n", G->pred[v], v);
}

void UGRAPHbridges (UGraph G) {
    vertex v;
    G->low = malloc (G->V * sizeof v);
    initDfs (G);
    
    for (v = 0; v < G->V; ++v)
        if (G->pre[v] == -1) {
            G->pred[v] = v;
            bridgesR (G, v);
        }
    
    freeDfs (G);
    free (G->low);
}

int GRAPHvertices (Graph G) {
    return G->V;
}

int GRAPHarcs (Graph G) {
    return G->A;
}

int GRAPHindeg (Graph G, vertex v) {
    int i, ans = 0;
    link a;
    for (i = 0; i < G->V; i++)
        for (a = G->adj[i]; a != NULL; a = a->next)
            if (a->w == v) ans++;
    return ans;
}

int GRAPHoutdeg (Graph G, vertex v) {
    int ans = 0;
    link a;
    for (a = G->adj[v]; a != NULL; a = a->next)
        ans++;
    return ans;
}

int GRAPHrootedForestHeight (Graph G, vertex *p) {
    int *h, i, max = 0;
    Stack S = STACKinit (G->V);
    h = malloc (G->V * sizeof (int));

    for (i = 0; i < G->V; ++i) h[i] = (i == p[i] ? 0:-1);
    for (i = 0; i < G->V; ++i) {
        while (h[i] == -1) {
            STACKput (S, i);
            i = p[i];
        }
        while (!STACKempty (S)) {
            i = STACKget (S);
            h[i] = h[p[i]] + 1;
        }
        max = (h[i] > max ? h[i] : max);
    }

    free (h); STACKfree (S);
    return max;
}

int GRAPHdfsForestHeight (Graph G) {
    vertex v; int ans;
    initDfs (G);

    for (v = 0; v < G->V; ++v)
        if (G->pre[v] == -1) {
            G->pred[v] = v;
            dfsR (G, v);
        }
    ans = GRAPHrootedForestHeight (G, G->pred);

    freeDfs (G);
    return ans;
}

/* A função dfsRcc() atribui o número id a todos os vértices que estão na mesma
   componente conexa que v. A função supõe que o grafo é representado por listas
   de adjacência. */
static void dfsRcc (UGraph G, int *cc, vertex v, int id) {
    link a;
    cc[v] = id;
    for (a = G->adj[v]; a != NULL; a = a->next)
        if (cc[a->w] == -1)
            dfsRcc (G, cc, a->w, id);
}

/* A função UGRAPHcc() devolve o número de componentes conexas do grafo
   não-dirigido G. Além disso, armazena no vetor cc[] uma numeração dos
   vértices tal que dois vértices v e w pertencem à mesma componente se
   e somente se cc[v] == cc[w]. (O código foi copiado do programa 18.4
   de Sedgewick.) */
int UGRAPHcc (UGraph G, int *cc) {
    vertex v; int id = 0;
    for (v = 0; v < G->V; ++v)
        cc[v] = -1;
    for (v = 0; v < G->V; ++v)
        if (cc[v] == -1)
            dfsRcc (G, cc, v, id++);
    return id;
}

int UGRAPHccBfs (UGraph G, int *cc) {
    vertex v, y; int id = -1;
    link a; Queue Q;
    for (v = 0; v < G->V; ++v)
        cc[v] = -1;
    Q = QUEUEinit (G->V);

    for (v = 0; v < G->V; ++v)
        if (cc[v] == -1)
            for (QUEUEput (Q, v), cc[v] = ++id; !QUEUEempty (Q); ) {
                y = QUEUEget (Q);
                for (a = G->adj[y]; a != NULL; a = a->next)
                    if (cc[a->w] == -1) {
                        cc[a->w] = id;
                        QUEUEput (Q, a->w);
                    }
            }

    QUEUEfree (Q);
    return id + 1;
}

int UGRAPHccAdd (UGraph G, int *cc, vertex v, vertex w) {
    vertex s; int id = 0, idv = cc[v], idw = cc[w];
    for (s = 0; s < G->V; ++s)
        id = id < cc[s] ? cc[s] : id;
    if (cc[v] != cc[w]) {
        for (s = 0; s < G->V; ++s)
            if (cc[s] == idv || cc[s] == idw)
                cc[s] = cc[v] < cc[w] ? cc[v] : cc[w];
        return id;
    }
    return id + 1;
}

/* O código de strongR() foi adaptado da figura 5.15 do livro de Aho,
   Hopcroft e Ullman. */
static void strongR (Graph G, vertex v, int *sc, Stack S, int *k) {
    vertex w, u; link a; int min;
    G->pre[v] = G->cnt1++;
    min = G->pre[v];
    STACKput (S, v);
    
    for (a = G->adj[v]; a != NULL; a = a->next) {
        w = a->w;
        if (G->pre[w] == -1) {
            strongR (G, w, sc, S, k);
            if (G->low[w] < min) min = G->low[w]; /*A*/
        }
        else if (G->pre[w] < G->pre[v] && sc[w] == -1) {
            if (G->pre[w] < min) min = G->pre[w]; /*B*/
        }
    }
    G->low[v] = min;
    if (G->low[v] == G->pre[v]) {               /*C*/
        do {
            u = STACKget (S);
            sc[u] = *k;
        } while (u != v);
        *k = *k + 1;
    }
}

/* A função GRAPHscT() devolve o número de componentes fortes do grafo G e
   armazena no vetor sc[], indexado pelo vértices de G, os nomes das componentes
   fortes de G: para cada vértice u, sc[u] será o nome da componente forte que
   contém u. Os nomes das componentes fortes são 0, 1, 2, etc. (A função
   implementa o algoritmo de Tarjan.) */
int GRAPHscT (Graph G, int *sc) {
    vertex v; int *k = malloc (sizeof (int));
    Stack S = STACKinit (G->V);
    G->low = malloc (G->V * sizeof v);
    for (v = 0; v < G->V; ++v) sc[v] = -1;
    initDfs (G);
    
    *k = 0;
    for (v = 0; v < G->V; ++v)
        if (G->pre[v] == -1)
            strongR (G, v, sc, S, k);
    v = *k;

    free (k);
    STACKfree (S);
    free (G->low);
    freeDfs (G);
    return v;
}

/* Atribui o rótulo k a todo vértice w ao alcance de v que ainda não foi
   rotulado. Os rótulos são armazenados no vetor sc[]. */
static void dfsRsc (Graph G, vertex v, int *sc, int k) {
    link a;
    sc[v] = k;
    for (a = G->adj[v]; a != NULL; a = a->next)
        if (sc[a->w] == -1)
            dfsRsc (G, a->w, sc, k);
}

/* Esta função atribui um rótulo sc[v] (os rótulos são 0,1,2,...) a cada vértice
   v do grafo G de modo que dois vértices tenham o mesmo rótulo se e somente se
   os dois pertencem à mesma componente forte. A função devolve o número
   (quantidade) de componentes fortes de G. (A função implementa o algoritmo de
   Kosaraju. O código é adaptado do Programa 19.10 de Sedgewick.) */
int GRAPHscK (Graph G, int *sc) {
    int k, i, *vv;
    vertex v;
   
    /* fase 1 */
    Graph GR = GRAPHreverse (G);
    vv = malloc (G->V * sizeof (int));
    initDfs (GR);
    
    for (v = 0; v < GR->V; ++v)
        if (GR->pre[v] == -1)
            dfsR (GR, v);
    for (v = 0; v < GR->V; ++v)
        vv[GR->post[v]] = v;

    /* fase 2 */
    for (v = 0; v < G->V; ++v)
        sc[v] = -1;
    for (k = 0, i = G->V-1; i >= 0; --i) {
        v = vv[i];
        if (sc[v] == -1) { /* nova etapa */
            dfsRsc (G, v, sc, k);
            k++;
        }
    }

    freeDfs (GR);
    GRAPHfree (GR);
    free (vv);
    return k;
}

int UGRAPHsequentialColoring (UGraph G, int *color) { 
    vertex v;
    link a;
    int i, k = 0;
    int *disponivel = malloc (sizeof color);
    for (v = 0; v < G->V; ++v) color[v] = -1;
    for (v = 0; v < G->V; ++v) {
        for (i = 0; i < k; ++i) disponivel[i] = 1;
        for (a = G->adj[v]; a != NULL; a = a->next) {
            i = color[a->w];
            if (i != -1) disponivel[i] = 0;
        }
        for (i = 0; i < k; ++i) 
            if (disponivel[i] == 1) break;
        if (i < k) color[v] = i;
        else color[v] = k++;
    }
    return k;
}

/* A função newMatching() executa a operação M⊕P sobre um emparelhamento M e um
   caminho aumentador P. O emparelhamento M é representado pelo vetor 
   match[0..V-1]. O caminho P termina no vértice t e é representado por 
   parent[]. A origem s de P é caracterizada pela propriedade parent[s] == s. */
static void newMatching (Graph G, vertex *match, vertex t) { 
    vertex x;
    do {
        x = G->pred[t];
        match[t] = x;
        match[x] = t;
        t = G->pred[x]; 
    } while (t != x);
}

/* Esta função recebe um grafo não-dirigido bipartido G, com bicoloração 
   color[0..V-1], e um emparelhamento M representado por match[0..V-1]. A função
   procura calcular um emparelhamento maior que M. Se tiver sucesso, devolve 
   TRUE e modifica match[] de acordo. Se fracassar, devolve false sem alterar 
   match[]. (A função usa a estratégia de busca em largura. Esse código não está
   no livro de Sedgewick.) */
static bool augmentMatchingBfs (UGraph G, int *color, vertex *match) { 
    vertex v, s;
    Queue Q = QUEUEinit (G->V);
    initDfs (G);
    for (v = 0; v < G->V; ++v) G->pre[v] = 0;
    for (s = 0; s < G->V; ++s) {
        if (color[s] == 0 && match[s] == -1) {
            G->pre[s] = 1; 
            G->pred[s] = s;
            QUEUEput (Q, s); 
        }
    } 
    /* a fila contém todos os vértices solteiros de cor 0 */

    while (!QUEUEempty (Q)) { 
        /* todos os vértices da fila têm cor 0 */
        vertex w, x;
        link a;
        v = QUEUEget (Q);
        for (a = G->adj[v]; a != NULL; a = a->next) {
            w = a->w; /* cor[w] == 1 */
            if (G->pre[w] == 0) { 
                G->pre[w] = 1; 
                G->pred[w] = v; 
                if (match[w] == -1) {
                    newMatching (G, match, w);
                    QUEUEfree (Q); freeDfs (G);
                    return true;
                }
                x = match[w]; /* cor[x] == 0 e visit[x] == 0 */
                G->pre[x] = 1;
                G->pred[x] = w; /* caminho ganhou segmento v-w-x */
                QUEUEput (Q, x); 
            }
        }
    }

    QUEUEfree (Q); freeDfs (G);
    return false;
}

static bool dfsRaugment (Graph G, vertex v, vertex *match) {
    vertex w, ww;
    link a;
    G->pre[v] = 1;
    for (a = G->adj[v]; a != NULL; a = a->next) {
        w = a->w; /* color[w] = 1 */
        if (G->pre[w] == 0) {
            G->pre[w] = 1;
            if (match[w] == -1) { /* w solteiro */
                match[w] = v;
                match[v] = w;
                return true; 
            }
            ww = match[w]; /* color[ww] = 0 */
            if (dfsRaugment (G, ww, match)) {
                match[w] = v;
                match[v] = w;
                return true;
            }
        }
    }
    return false;
}

/* Esta função recebe um grafo não-dirigido bipartido G, com bicoloração 
   color[], e um emparelhamento M representado por match[]. A função procura 
   calcular um emparelhamento maior que M. Se tiver sucesso, devolve true e 
   modifica match[] de acordo. Se fracassar, devolve false sem alterar match[].
   (A função usa a estratégia de busca em profundidade. Esse código não está no 
   livro de Sedgewick.) */
static bool augmentMatchingDfs (UGraph G, int *color, vertex *match) { 
    vertex v, s;
    initDfs (G);
    for (s = 0; s < G->V; ++s) G->pre[s] = 0;
    for (v = 0; v < G->V; ++v) 
        if (color[v] == 0 && match[v] == -1 && G->pre[v] == 0)
            if (dfsRaugment (G, v, match)) {
                freeDfs (G);
                return true;
            }
    freeDfs (G);
    return false;
}

/* A função UGRAPHbipartiteMatching() calcula um emparelhamento máximo M no 
   grafo não-dirigido bipartido G. A bipartição de G é dada pelo vetor 
   color[0..V-1], que tem valores 0 e 1. A função devolve o tamanho de M e 
   armazena uma representação de M no vetor match[0..V-1], alocado pelo usuário:
   para cada vértice v, match[v] é o vértice que M casa com v (ou -1 se v é 
   solteiro). (Esse código não está no livro de Sedgewick.) */
int UGRAPHbipartiteMatching (UGraph G, int *color, vertex *match, bool bfs) { 
    vertex v;
    int size;
    for (v = 0; v < G->V; ++v) match[v] = -1;
    size = 0;
    while ((bfs && augmentMatchingBfs (G, color, match)) ||
           (!bfs && augmentMatchingDfs (G, color, match)))
        size++;
    return size;
}

int UGRAPHgeneralMatching (UGraph G, vertex *match) {
    vertex v;
    int *phi = malloc (G->V * sizeof int);
    int *rho = malloc (G->V * sizeof int);
    /* Inicializacao */
    for (v = 0; v < G->V; ++v)
        if (match[v] != 1)
            phi[v] = rho[v] = -1;
        else {
            phi[v] = rho[v] = v;
            /* inclui as arestas que saem de v numa fila */
        }
    /* Inicializa A = empty */
    
    return 0;
}

bool GRAPHisUndirected (Graph G) {
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

bool GRAPHisolated (Graph G, vertex v) {
    if (GRAPHindeg (G, v) > 0) return false;
    if (GRAPHoutdeg (G, v) > 0) return false;
    return true;
}

bool GRAPHadj (Graph G, vertex v, vertex w) {
    link a;
    for (a = G->adj[v]; a != NULL; a = a->next)
        if (a->w == w) return true;
    for (a = G->adj[w]; a != NULL; a = a->next)
        if (a->w == v) return true;
    return false;
}

bool GRAPHisTopoNumbering (Graph G, int *topo) {
    vertex v;
    link a;
    for (v = 0; v < G->V; ++v)
        for (a = G->adj[v]; a != NULL; a = a->next)
            if (topo[v] >= topo[a->w])
                return false;
    return true;
}

bool GRAPHisTopoOrder (Graph G, vertex *vv) {
    int *topo, i;
    topo = malloc (G->V * sizeof (int));
    for (i = 0; i < G->V; ++i)
        topo[vv[i]] = i;
    i = GRAPHisTopoNumbering (G, topo);
    free (topo);
    return i;
}

bool GRAPHreach (Graph G, vertex s, vertex t) {
    vertex v, N;
    link a, *next;
    bool *visit;
    Stack S = STACKinit (G->V);
    visit = malloc (G->V * sizeof (bool));
    next = malloc (G->V * sizeof a);

    N = 0;
    for (v = 0; v < G->V; ++v) visit[v] = false;
    STACKput (S, s);
    next[N++] = G->adj[s];

    while (!STACKempty (S)) {
        v = STACKget (S);
        a = next[--N];
        visit[v] = true;
        if (v == t) break;

        while (a != NULL) {
            if (!visit[a->w]) {
                STACKput (S, v);
                STACKput (S, a->w);
                next[N++] = a;
                next[N++] = G->adj[a->w];
                break;
            }
            a = a->next;
        }
    }

    free (visit);
    STACKfree (S);
    free (next);
    return v == t;
}

/* A função cycleR() devolve true se encontra um ciclo ao percorrer G a partir
   do vértice v e devolve false em caso contrário. */
static bool cycleR (Graph G, vertex v) {
    vertex w; link a;
    G->pre[v] = G->cnt1++;
    for (a = G->adj[v]; a != NULL; a = a->next) {
        w = a->w;
        if (G->pre[w] == -1) {
            if (cycleR (G, w))
                return true;
        } else {
            if (G->post[w] == -1) /* A */
                return true;   /* v-w é de retorno */
            /* B */
        }
    }
    G->post[v] = G->cnt2++;
    return false;
}

bool GRAPHhasCycle (Graph G) {
    vertex v; bool ans = false;
    initDfs (G);

    for (v = 0; v < G->V; ++v)
        if (G->pre[v] == -1)
            if (cycleR (G, v))
                ans = true;
    
    freeDfs (G);
    return ans;
}

bool UGRAPHisConnected (UGraph G) {
    vertex v; bool ans = true;
    initDfs (G);
    
    dfsR (G, 0);
    for (v = 0; v < G->V; ++v)
        if (G->pre[v] == -1) ans = false;

    freeDfs (G);
    return ans;
}

static bool dfsRcolor (UGraph G, vertex v, int *color, int c) { 
    link a; 
    color[v] = c;
    for (a = G->adj[v]; a != NULL; a = a->next) {
        vertex w = a->w; 
        if (color[w] == -1) {
            if (dfsRcolor (G, w, color, 1-c) == false) 
                return false; 
        }
        else { /* v-w é arco de retorno */
            if (color[w] == c) /* base da recursão */
                return false;
        }
    }
    return true;
}

/* Esta função decide se o grafo não-dirigido G admite bipartição. Em caso 
   afirmativo, a função atribui uma cor, 0 ou 1, a cada vértice de G de tal 
   forma que toda aresta tenha pontas de cores diferentes. As cores dos vértices
   são armazenadas no vetor color[] indexado pelos vértices. (Esta função supõe 
   que G é representado por listas de adjacência. 
   Código inspirado no programa 18.6 de Sedgewick.) */
bool UGRAPHtwoColor (UGraph G, int *color) { 
    vertex v;
    for (v = 0; v < G->V; ++v) 
        color[v] = -1; /* incolor */
    for (v = 0; v < G->V; ++v)
        if (color[v] == -1) /* começa nova etapa */
            if (dfsRcolor (G, v, color, 0) == false) 
                return false;
    return true;
}

bool UGRAPHisMatching (UGraph G, vertex *match) {
    vertex v;
    for (v = 0; v < G->V; ++v)
        if (match[v] != -1 && match[match[v]] != v)
            return false;
    return true;
}

void GRAPHshow (Graph G) {
    vertex v;
    link a;
    for (v = 0; v < G->V; ++v) {
        printf  ("%2d:", v);
        for (a = G->adj[v]; a != NULL; a = a->next) {
            printf  (" %2d", a->w);
        }
        printf  ("\n");
    }
}

void UGRAPHshowKnight (Graph G, int i, int j) {
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

void GRAPHsave (Graph G, FILE * out) {
    vertex v; link a;

    fprintf (out, "%d\n", G->V);
    for (v = 0; v < G->V; ++v) {
        fprintf (out, "%d:", v);
        for (a = G->adj[v]; a != NULL; a = a->next)
            fprintf (out, " %d", a->w);
        fprintf (out, "\n");
    }
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
