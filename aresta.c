#include "aresta.h"
#include "strc_vertice.h"
#include "strc_aresta.h"

#include <stdlib.h>

#include "vertice.h"

// Cria uma aresta entre dois vértices distintos.
EDGE *edge_create(int e, VERTEX *u_, VERTEX *v_){
    if(u_ == NULL || v_ == NULL || u_ == v_){
        return NULL;
    }

    EDGE *nova = (EDGE *)malloc(sizeof(EDGE));

    if(nova != NULL){
        nova->elemento = e;
        nova->visit = false;
        nova->u = u_;
        nova->v = v_;

        // Inicializa os encadeamentos nas listas de ambos os extremos.
        nova->u_prox = NULL;
        nova->u_ant = NULL;
        nova->v_prox = NULL;
        nova->v_ant = NULL;
    }

    return nova;
}

// Retorna o elemento armazenado na aresta, ou -1 se ela for NULL.
int edge_element(EDGE *a){
    if(a != NULL){
        return a->elemento;
    }
    return -1;
}

// Cria e retorna um par com os extremos da aresta.
ENDPOINT *edge_endpoint(EDGE *a){
    if(a != NULL){
        ENDPOINT *end = (ENDPOINT *)malloc(sizeof(ENDPOINT));
        if(end != NULL){
            end->u = a->u;
            end->v = a->v;
            return end;
        }
    }
    return NULL;
}

// Retorna o outro extremo da aresta em relação ao vértice informado.
VERTEX *edge_opposite(EDGE *a, VERTEX *v){
    if(a != NULL && v != NULL){
        if(v == a->u){
            return a->v;
        }
        else{
            if(v == a->v){
                return a->u;
            }
            else{
                return NULL;
            }
        }
    }
    return NULL;
}

// Libera a memória da aresta e define o ponteiro como NULL.
void edge_erase(EDGE **a){
    if(a != NULL && *a != NULL){
        free(*a);
        *a = NULL;
    }
}