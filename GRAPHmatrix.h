#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

/* Vértices de grafos são representados por objetos do tipo vertex. */
#define vertex int
/* O tipo UGraph é apenas um sinônimo de Graph, mas deixa claro para o leitor 
   humano que o grafo é não-dirigido. */
#define UGraph Graph

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A estrutura graph representa
   um grafo. O campo adj é um ponteiro para a matriz de adjacências do 
   grafo. O campo V contém o número de vértices e o campo A contém o 
   número de arcos do grafo. */
struct graph {
    int V; 
    int A; 
    int **adj;
    int *pre;
    int *post;
    int *parent;
};

/* Um Graph é um ponteiro para um graph, ou seja, um Graph contém o
   endereço de um graph. */
typedef struct graph *Graph;

Graph GRAPHinit (int V); 
Graph GRAPHinputArcs (void);
Graph GRAPHinputLists (void);
Graph GRAPHinputArcsFile (FILE *in);
Graph GRAPHinputListsFile (FILE *in);
Graph UGRAPHknight();
Graph GRAPHbuildComplete (int V);
Graph GRAPHrand1 (int V, int A);
Graph GRAPHrand2 (int V, int A);

void GRAPHinsertArc (Graph G, vertex v, vertex w); 
void UGRAPHinsertArc (Graph G, vertex v, vertex w);
void GRAPHremoveArc (Graph G, vertex v, vertex w); 
void GRAPHdfs (Graph G);

int GRAPHindeg (Graph G, vertex v);
int GRAPHoutdeg (Graph G, vertex v);
int GRAPHrootedForestHeight (Graph G, vertex *p);
int UGRAPHcc (UGraph G, int *cc);
bool GRAPHisUndirected (Graph G);
bool GRAPHisolated (Graph G, vertex v);
bool GRAPHadj (Graph G, vertex v, vertex w);
bool GRAPHisTopoNumbering (Graph G, int *topo);
bool GRAPHisTopoOrder (Graph G, vertex *vv);
bool GRAPHreach (Graph G, vertex s, vertex t);
bool GRAPHhasCycle (Graph G);

void GRAPHshow (Graph G); 
void UGRAPHshowKnight (Graph G, int i, int j);

void GRAPHfree (Graph G);
