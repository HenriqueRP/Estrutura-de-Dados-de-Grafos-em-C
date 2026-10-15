#ifndef STRC_A_H
#define STRC_A_H

#include "aresta.h"
#include "vertice.h"

// Representação interna da aresta.
struct aresta_{
    int elemento; // Valor armazenado na aresta.
    bool visit;   // Marca utilizada para evitar arestas duplicadas em percursos.
    VERTEX *u, *v; // Vértices que formam as extremidades da aresta.

    // Encadeamento da aresta na lista de u.
    EDGE *u_prox, *u_ant;

    // Encadeamento da mesma aresta na lista de v.
    EDGE *v_prox, *v_ant;
};

#endif