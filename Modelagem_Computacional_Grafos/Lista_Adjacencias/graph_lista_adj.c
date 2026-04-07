#include "graph.h"
#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct graph {
    int ordem;
    LISTA **lista_adj;
};

GRAPH *criar_grafo(int ordem) {
    if(ordem <= 0) return NULL;

    GRAPH *g = (GRAPH *)malloc(ordem * sizeof(GRAPH));
    if(g != NULL) {
        g->ordem = ordem;
        LISTA **adj_list = (LISTA **)malloc(ordem * sizeof(LISTA *));
        for(int i = 0; i < g->ordem; i++) {
            adj_list[i] = lista_criar(false);
        }
        g->lista_adj = adj_list;
    }

    return g;
}

bool grafo_apagar(GRAPH **g) {
    if(g == NULL || *g == NULL) return true;

    for(int i = 0; i < (*g)->ordem; i++) {
        lista_apagar(&((*g)->lista_adj[i]));
        free((*g)->lista_adj[i]);
    }
    free((*g)->lista_adj);
    (*g)->lista_adj = NULL;
    free(*g);
    *g = NULL;
}