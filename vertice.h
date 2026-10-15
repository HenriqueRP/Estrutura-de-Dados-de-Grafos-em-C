#ifndef VERT_H
#define VERT_H

#include <stdbool.h>

typedef struct vertice_ VERTEX;
typedef struct aresta_ EDGE;

VERTEX *vertex_create(int e);
int vertex_element(VERTEX *v);
void vertex_erase(VERTEX **v);
bool vertex_visited(VERTEX *v);
void vertex_mark(VERTEX *v);

#endif