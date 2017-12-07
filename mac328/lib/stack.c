#include "stack.h"

struct stack {
    int N;
    int top;
    int *cont;
};

Stack STACKinit (int size) {
    Stack S = malloc (sizeof (*S));
    S->N = size;
    S->top = 0;
    S->cont = malloc (size * sizeof (vertex));
    return S;
}

void STACKput (Stack S, vertex v) {
    S->cont[S->top++] = v;
}

vertex STACKget (Stack S) {
    vertex v = S->cont[--S->top];
    return v;
}

bool STACKempty (Stack S) {
    return S->top == 0;
}

void STACKfree (Stack S) {
    free (S->cont);
    free (S);
}
