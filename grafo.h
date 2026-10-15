#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>

#include "aresta.h"
#include "vertice.h"

typedef struct grafo_ GRAFO;

GRAFO *grafo_criar(void);
int vertex_count(GRAFO *g);
int edge_count(GRAFO *g);
EDGE *grafo_get_edge(GRAFO *g, VERTEX *u, VERTEX *v);
int grafo_degree(GRAFO *g, VERTEX *v);
VERTEX *grafo_insert_vertex(GRAFO *g, int e);
EDGE *grafo_insert_edge(GRAFO *g, VERTEX *u, VERTEX *v, int e);
void grafo_remove_edge(GRAFO *g, EDGE **a);
void grafo_remove_vertex(GRAFO *g, VERTEX **v);
void grafo_apagar(GRAFO **g);

typedef struct vertex_iter VERTEX_ITER;

typedef struct edge_iter EDGE_ITER;

VERTEX_ITER *vertices(GRAFO *g);
VERTEX *grafo_iter_vertice(VERTEX_ITER *it);
EDGE_ITER *edges(GRAFO *g);
EDGE *grafo_iter_edge(EDGE_ITER *it);
EDGE_ITER *edges_in_vertice(VERTEX *v);
EDGE *grafo_iter_v_edges(EDGE_ITER *it, VERTEX *v);
void grafo_iter_edge_apagar(EDGE_ITER **it);
void grafo_iter_vertice_apagar(VERTEX_ITER **it);

#endif