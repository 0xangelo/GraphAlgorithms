#ifndef _QUEUE_H
#define _QUEUE_H

#include <stdlib.h>
#include <stdbool.h>

#define vertex int

typedef struct queue *Queue;

Queue QUEUEinit (int size);
void QUEUEput (Queue Q, vertex v);
vertex QUEUEget (Queue Q);
bool QUEUEempty (Queue Q);
void QUEUEfree (Queue Q);

#endif
