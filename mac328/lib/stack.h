#ifndef _STACK_H
#define _STACK_H

#include <stdlib.h>
#include <stdbool.h>

#define vertex int

typedef struct stack *Stack;

Stack STACKinit (int size);
void STACKput (Stack S, vertex v);
vertex STACKget (Stack S);
bool STACKempty (Stack S);
void STACKfree (Stack S);

#endif
