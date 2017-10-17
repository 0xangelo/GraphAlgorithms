#ifndef _GRAPHMATRIX_H
#define _GRAPHMATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include "queue.h"
#include "stack.h"

/* Vértices de grafos são representados por objetos do tipo vertex. */
#define vertex int
/* O tipo UGraph é apenas um sinônimo de Graph, mas deixa claro para o leitor 
   humano que o grafo é não-dirigido. */
#define UGraph Graph

/* Um Graph é um ponteiro para um graph. */
typedef struct graph *Graph;

Graph GRAPHinit (int V); 
Graph GRAPHinputArcs (void);
Graph GRAPHinputLists (void);
Graph GRAPHinputArcsFile (FILE *in);
Graph GRAPHinputListsFile (FILE *in);
Graph UGRAPHknight (void);
Graph GRAPHbuildComplete (int V);
Graph GRAPHrand1 (int V, int A);
Graph GRAPHrand2 (int V, int A);
Graph GRAPHreverse (Graph G);
UGraph UGRAPHrandU (int V, int E);

void GRAPHinsertArc (Graph G, vertex v, vertex w); 
void UGRAPHinsertArc (Graph G, vertex v, vertex w);
void GRAPHremoveArc (Graph G, vertex v, vertex w); 
void GRAPHdfs (Graph G);
void GRAPHbfs (Graph G, vertex s);
int UGRAPHccBfs (UGraph G, int *cc);
void GRAPHminPaths (Graph G, vertex s, int *pred, int *dist);
void GRAPHtopoOrder (Graph G, int *vv);
void GRAPHpath (Graph G, vertex s, vertex t);
void UGRAPHbridges (UGraph G);

int GRAPHvertices (Graph G);
int GRAPHarcs (Graph G);
int GRAPHindeg (Graph G, vertex v);
int GRAPHoutdeg (Graph G, vertex v);
int GRAPHrootedForestHeight (Graph G, vertex *p);
int GRAPHdfsForestHeight (Graph G);
int UGRAPHcc (UGraph G, int *cc);
int UGRAPHccAdd (UGraph G, int *cc, vertex v, vertex w);
int GRAPHscT (Graph G, int *sc);
int GRAPHscK (Graph G, int *sc);
bool GRAPHisUndirected (Graph G);
bool GRAPHisolated (Graph G, vertex v);
bool GRAPHadj (Graph G, vertex v, vertex w);
bool GRAPHisTopoNumbering (Graph G, int *topo);
bool GRAPHisTopoOrder (Graph G, vertex *vv);
bool GRAPHreach (Graph G, vertex s, vertex t);
bool GRAPHhasCycle (Graph G);
bool UGRAPHisConnected (UGraph G);

void GRAPHshow (Graph G); 
void UGRAPHshowKnight (Graph G, int i, int j);
void GRAPHsave (Graph G, FILE * out);

void GRAPHfree (Graph G);

#endif
