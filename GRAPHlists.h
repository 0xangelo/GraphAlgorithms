#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/* Vértices de grafos são representados por objetos do tipo vertex. */

#define vertex int
/* A lista de adjacência de um vértice v é composta por nós do tipo node. Cada nó da lista corresponde a um arco e contém um vizinho w de v e o endereço do nó seguinte da lista. Um link é um ponteiro para um node. */

typedef struct node *link;
struct node { 
   vertex w; 
   link next; 
};
/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIA: A estrutura graph representa um grafo. O campo adj é um ponteiro para o vetor de listas de adjacência, o campo V contém o número de vértices e o campo A contém o número de arcos do grafo. */

struct graph {
   int V; 
   int A; 
   link *adj; 
};
/* Um Graph é um ponteiro para um graph. */

typedef struct graph *Graph;

Graph GRAPHinit( int V); 
void GRAPHinsertArc( Graph G, vertex v, vertex w); 
void GRAPHremoveArc( Graph G, vertex v, vertex w); 
void GRAPHshow( Graph G); 
Graph GRAPHinputArcs( FILE *in);
Graph GRAPHinputLists( FILE *in);
bool GRAPHisUndirected( Graph G);
int GRAPHindeg( Graph G, vertex v);
int GRAPHoutdeg( Graph G, vertex v);
bool GRAPHisolated( Graph G, vertex v);
bool GRAPHadj( Graph G, vertex v, vertex w);
Graph UGRAPHknight();
void UGRAPHshowKnight( Graph G, int i, int j);
Graph GRAPHbuildComplete( int V);
Graph GRAPHrand1( int V, int A);
Graph GRAPHrand2( int V, int A);
