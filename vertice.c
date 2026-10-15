#include "vertice.h"
#include "strc_vertice.h"

#include "aresta.h"

#include <stdlib.h>

// Cria um vértice com o elemento informado e inicializa seus campos.
VERTEX *vertex_create(int e){
    VERTEX *novo = (VERTEX *)malloc(sizeof(VERTEX));

    if(novo != NULL){
        novo->elemento = e;
        novo->visit = false;
        novo->n_incidentes = 0;
        novo->incidentes = NULL;
        novo->prox = NULL;
        novo->ant = NULL;
    }
    return novo;
}

// Retorna o elemento armazenado no vértice, ou -1 se ele for NULL.
int vertex_element(VERTEX *v){
    if(v != NULL){
        return v->elemento;
    }
    return -1;
}

// Libera a memória do vértice e define o ponteiro como NULL.
void vertex_erase(VERTEX **v){
    if(v != NULL && *v != NULL){
        free(*v);
        *v = NULL;
    }
}

// Informa se o vértice está marcado como visitado.
bool vertex_visited(VERTEX *v){
    return v != NULL && v->visit;
}

// Marca o vértice como visitado.
void vertex_mark(VERTEX *v){
    if(v != NULL)
        v->visit = true;
}