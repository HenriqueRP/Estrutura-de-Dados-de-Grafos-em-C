#ifndef ARES_H
#define ARES_H

#include <stdbool.h>

typedef struct vertice_ VERTEX;
typedef struct aresta_ EDGE;

typedef struct{
    VERTEX *u;
    VERTEX *v;
}ENDPOINT;

EDGE *edge_create(int e, VERTEX *u_, VERTEX *v_);
int edge_element(EDGE *a);
ENDPOINT *edge_endpoint(EDGE *a);
VERTEX *edge_opposite(EDGE *a, VERTEX *v);
void edge_erase(EDGE **a);

#endif