#ifndef STRC_V_H
#define STRC_V_H

#include "aresta.h"
#include "vertice.h"

// Representação interna do vértice.
struct vertice_{
    int elemento, n_incidentes; // Valor armazenado e grau do vértice.
    bool visit;                // Marca utilizada em percursos do grafo.
    EDGE *incidentes;          // Início da lista de arestas incidentes.
    VERTEX *prox, *ant;        // Encadeamento na lista global de vértices.
};

#endif