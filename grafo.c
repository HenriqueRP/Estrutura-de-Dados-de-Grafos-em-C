#include "grafo.h"
#include "vertice.h"
#include "aresta.h"

#include "strc_vertice.h"
#include "strc_aresta.h"

#include <stdlib.h>

// Mantém a posição atual durante a iteração de arestas.
struct edge_iter{
    EDGE *atual;
    VERTEX *vertice;
};

// Mantém a posição atual durante a iteração de vértices.
struct vertex_iter{
    VERTEX *atual;
};

// Representação interna do grafo: lista de vértices e contadores.
struct grafo_{
    VERTEX *vertices;
    int n_vertex, n_edge;
};

// Cria um grafo vazio.
GRAFO *grafo_criar(void){
    GRAFO *novo = (GRAFO *)malloc(sizeof(GRAFO));

    if(novo != NULL){
        novo->vertices = NULL;
        novo->n_vertex = 0;
        novo->n_edge = 0;
    }
    return novo;
}

// Retorna a quantidade de vértices, ou -1 se o grafo for NULL.
int vertex_count(GRAFO *g){
    if(g != NULL){
        return g->n_vertex;
    }
    return -1;
}

// Retorna a quantidade de arestas, ou -1 se o grafo for NULL.
int edge_count(GRAFO *g){
    if(g != NULL){
        return g->n_edge;
    }
    return -1;
}

// Busca a aresta entre u e v percorrendo a lista de menor grau.
EDGE *grafo_get_edge(GRAFO *g, VERTEX *u, VERTEX *v){
    if(g != NULL && u != NULL && v != NULL){
        if(grafo_degree(g, u) <= grafo_degree(g, v)){
            EDGE *atual = u->incidentes;

            while(atual != NULL && edge_opposite(atual, u) != v){
                if(atual->u == u){
                    atual = atual->u_prox;
                }
                else{
                    atual = atual->v_prox;
                }
            }
            return atual;
        }
        else{
            EDGE *atual = v->incidentes;

            while(atual != NULL && edge_opposite(atual, v) != u){
                if(atual->u == v){
                    atual = atual->u_prox;
                }
                else{
                    atual = atual->v_prox;
                }
            }
            return atual;
        }
    }
    return NULL;
}

// Retorna o grau do vértice, armazenado no próprio vértice.
int grafo_degree(GRAFO *g, VERTEX *v){
    if(g != NULL && v != NULL){
        return v->n_incidentes;
    }
    return -1;
}

// Cria um vértice e o insere no início da lista do grafo.
VERTEX *grafo_insert_vertex(GRAFO *g, int e){
    if(g == NULL){
        return NULL;
    }

    VERTEX *v = vertex_create(e);

    if(v != NULL){
        if(g->vertices == NULL){
            g->vertices = v;
        }
        else{
            v->prox = g->vertices;
            g->vertices = v;
            v->prox->ant = v;
        }
        g->n_vertex++;
    }
    return v;
}

// Cria uma aresta e a insere nas listas de adjacência dos dois extremos.
EDGE *grafo_insert_edge(GRAFO *g, VERTEX *u, VERTEX *v, int e){
    if(g == NULL || u == NULL || v == NULL || u == v){
        return NULL;
    }

    EDGE *a = edge_create(e, u, v);

    if(a == NULL){
        return NULL;
    }

    // Insere a aresta no início da lista de u.
    if(u->incidentes == NULL){
        u->incidentes = a;
    }
    else{
        EDGE *inicio = u->incidentes;

        a->u_prox = inicio;
        u->incidentes = a;

        // Atualiza o predecessor usando o encadeamento de u.
        if(inicio->u == u){
            inicio->u_ant = a;
        }
        else{
            inicio->v_ant = a;
        }
    }

    // Insere a mesma aresta no início da lista de v.
    if(v->incidentes == NULL){
        v->incidentes = a;
    }
    else{
        EDGE *inicio = v->incidentes;

        a->v_prox = inicio;
        v->incidentes = a;

        // Atualiza o predecessor usando o encadeamento de v.
        if(inicio->u == v){
            inicio->u_ant = a;
        }
        else{
            inicio->v_ant = a;
        }
    }

    g->n_edge++;
    u->n_incidentes++;
    v->n_incidentes++;

    return a;
}

// Remove a aresta das duas listas de adjacência e libera sua memória.
void grafo_remove_edge(GRAFO *g, EDGE **a){
    if(g == NULL || a == NULL || *a == NULL){
        return;
    }

    EDGE *atual = *a;
    VERTEX *u = atual->u;
    VERTEX *v = atual->v;

    // Guarda os vizinhos da aresta na lista de u.
    EDGE *u_ant = atual->u_ant;
    EDGE *u_prox = atual->u_prox;

    // Remove a aresta da lista de u.
    if(u_ant == NULL){
        u->incidentes = u_prox;
    }
    else{
        if(u_ant->u == u){
            u_ant->u_prox = u_prox;
        }
        else{
            u_ant->v_prox = u_prox;
        }
    }

    // Atualiza o predecessor do sucessor na lista de u.
    if(u_prox != NULL){
        if(u_prox->u == u){
            u_prox->u_ant = u_ant;
        }
        else{
            u_prox->v_ant = u_ant;
        }
    }

    // Guarda os vizinhos da aresta na lista de v.
    EDGE *v_ant = atual->v_ant;
    EDGE *v_prox = atual->v_prox;

    // Remove a aresta da lista de v.
    if(v_ant == NULL){
        v->incidentes = v_prox;
    }
    else{
        if(v_ant->u == v){
            v_ant->u_prox = v_prox;
        }
        else{
            v_ant->v_prox = v_prox;
        }
    }

    // Atualiza o predecessor do sucessor na lista de v.
    if(v_prox != NULL){
        if(v_prox->u == v){
            v_prox->u_ant = v_ant;
        }
        else{
            v_prox->v_ant = v_ant;
        }
    }

    // Atualiza os contadores do grafo e dos vértices.
    g->n_edge--;
    u->n_incidentes--;
    v->n_incidentes--;

    // Libera a aresta somente depois de atualizar as duas listas.
    edge_erase(a);
}

// Remove todas as arestas incidentes e depois desvincula o vértice do grafo.
void grafo_remove_vertex(GRAFO *g, VERTEX **v){
    if(g == NULL || v == NULL || *v == NULL){
        return;
    }

    EDGE *atual = (*v)->incidentes;
    int tam = (*v)->n_incidentes;

    for(int i = 0; i < tam; i++){
        EDGE *prox;

        // Guarda a próxima aresta antes de liberar a atual.
        if(atual->u == (*v)){
            prox = atual->u_prox;
        }
        else{
            prox = atual->v_prox;
        }

        grafo_remove_edge(g, &atual);
        atual = prox;
    }

    // Remove o vértice da lista duplamente encadeada.
    if((*v)->ant == NULL){
        g->vertices = (*v)->prox;
        if((*v)->prox != NULL){
            (*v)->prox->ant = NULL;
        }
    }
    else{
        if((*v)->prox != NULL){
            (*v)->prox->ant = (*v)->ant;
            (*v)->ant->prox = (*v)->prox;
        }
        else{
            (*v)->ant->prox = (*v)->prox;
        }
    }

    g->n_vertex--;
    vertex_erase(v);
}

// Cria um iterador posicionado no primeiro vértice.
VERTEX_ITER *vertices(GRAFO *g){
    if(g == NULL){
        return NULL;
    }

    VERTEX_ITER *it = (VERTEX_ITER*)malloc(sizeof(VERTEX_ITER));

    if(it != NULL){
        it->atual = g->vertices;
    }
    return it;
}

// Retorna o vértice atual e avança o iterador.
VERTEX *grafo_iter_vertice(VERTEX_ITER *it){
    if(it == NULL || it->atual == NULL){
        return NULL;
    }

    VERTEX *v = it->atual;
    it->atual = it->atual->prox;

    return v;
}

// Cria um iterador para percorrer todas as arestas do grafo.
EDGE_ITER *edges(GRAFO *g){
    if(g == NULL){
        return NULL;
    }

    EDGE_ITER *it = (EDGE_ITER *)malloc(sizeof(EDGE_ITER));

    if(it != NULL){
        it->vertice = g->vertices;

        if(it->vertice != NULL){
            it->atual = g->vertices->incidentes;
        }
        else{
            it->atual = NULL;
        }
    }
    return it;
}

// Percorre as listas de adjacência, evitando retornar cada aresta duas vezes.
EDGE *grafo_iter_edge(EDGE_ITER *it){
    if(it == NULL || it->vertice == NULL){
        return NULL;
    }

    while(it->vertice != NULL){

        // Avança para o próximo vértice quando a lista atual termina.
        while(it->atual == NULL){
            it->vertice = it->vertice->prox;

            if(it->vertice != NULL)
                it->atual = it->vertice->incidentes;
            else
                return NULL;
        }

        if(it->vertice == NULL){
            return NULL;
        }

        EDGE *a = it->atual;

        // Avança pelo encadeamento correspondente ao extremo atual.
        if(a->u == it->vertice){
            it->atual = a->u_prox;
        }
        else{
            it->atual = a->v_prox;
        }

        // Usa a marca de visita para identificar a segunda ocorrência.
        if(a->visit){
            a->visit = false;
            continue;
        }

        a->visit = true;
        return a;
    }
    return NULL;
}

// Cria um iterador para percorrer as arestas incidentes a um vértice.
EDGE_ITER *edges_in_vertice(VERTEX *v){
    if(v == NULL){
        return NULL;
    }

    EDGE_ITER *it = (EDGE_ITER *)malloc(sizeof(EDGE_ITER));

    if(it != NULL){
        it->vertice = v;
        it->atual = v->incidentes;
    }
    return it;
}

// Retorna a próxima aresta da lista de adjacência do vértice informado.
EDGE *grafo_iter_v_edges(EDGE_ITER *it, VERTEX *v){
    if(it == NULL || it->atual == NULL || v == NULL){
        return NULL;
    }

    EDGE *a = it->atual;

    // Avança pelo encadeamento associado ao vértice percorrido.
    if(v == a->v){
        it->atual = a->v_prox;
    }
    else{
        it->atual = a->u_prox;
    }

    return a;
}

// Libera o iterador de arestas, sem alterar o grafo.
void grafo_iter_edge_apagar(EDGE_ITER **it){
    if(it != NULL && *it != NULL){
        free(*it);
        *it = NULL;
    }
}

// Libera o iterador de vértices, sem alterar o grafo.
void grafo_iter_vertice_apagar(VERTEX_ITER **it){
    if(it != NULL && *it != NULL){
        free(*it);
        *it = NULL;
    }
}

// Destrói o grafo removendo seus vértices e arestas antes de liberar a estrutura.
void grafo_apagar(GRAFO **g){
    if(g == NULL || *g == NULL){
        return;
    }

    while((*g)->vertices != NULL){
        VERTEX *v = (*g)->vertices;
        grafo_remove_vertex(*g, &v);
    }

    free(*g);
    *g = NULL;
}