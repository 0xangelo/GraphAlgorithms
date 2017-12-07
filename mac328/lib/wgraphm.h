#ifndef _GRAPHMATRIX_H
#define _GRAPHMATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include <limits.h>
#include "priority_queue.h"

/* Vértices de grafos são representados por objetos do tipo vertex. */
#define vertex int
/* O tipo UGraph é apenas um sinônimo de Graph, mas deixa claro para o leitor 
   humano que o grafo é não-dirigido. */
#define UGraph Graph
#define INFINITY INT_MAX

/* Um Graph é um ponteiro para um graph. */
typedef struct graph *Graph;

typedef struct { 
    vertex v, w; 
    int cst; 
} arc;

Graph GRAPHinit (int V); 
Graph GRAPHinputArcs (void);
Graph GRAPHinputArcsFile (FILE *in);
Graph GRAPHrand1 (int V, int A, int cmin, int cmax);
Graph GRAPHrand2 (int V, int A, int cmin, int cmax);
Graph GRAPHreverse (Graph G);
UGraph UGRAPHrandU (int V, int E, int cmin, int cmax);
UGraph UGRAPHrandGrid (int N, int cmin, int cmax);

void GRAPHinsertArc (Graph G, vertex v, vertex w, int cst); 
void UGRAPHinsertEdge (Graph G, vertex v, vertex w, int cst);
void GRAPHremoveArc (Graph G, vertex v, vertex w);

int GRAPHvertices (Graph G);
int GRAPHarcs (Graph G);

void GRAPHspt1 (Graph G, vertex s, vertex *parent, int *dist);
void GRAPHspt2 (Graph G, vertex s, vertex *parent, int *dist);
int GRAPHdistSet (Graph G, bool *S, bool *T);
arc GRAPHcriticalArc (Graph G, vertex s, vertex t);

void GRAPHshow (Graph G); 
void GRAPHsave (Graph G, FILE * out);
    
void GRAPHfree (Graph G);

#endif
