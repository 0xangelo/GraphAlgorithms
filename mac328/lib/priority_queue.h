#ifndef _PRIORITY_QUEUE_H
#define _PRIORITY_QUEUE_H

#include <stdlib.h>
#include <stdbool.h>

#define vertex int

typedef struct priority_queue *PriorityQueue;

PriorityQueue PQinit (int size);
bool PQempty (PriorityQueue Q);
int PQsize (PriorityQueue Q);
void PQinsert (PriorityQueue Q, vertex v, int *dist);
vertex PQdelMin (PriorityQueue Q, int *dist);
void PQdec (PriorityQueue Q, vertex v, int *dist);
void PQfree (PriorityQueue Q);

#endif
