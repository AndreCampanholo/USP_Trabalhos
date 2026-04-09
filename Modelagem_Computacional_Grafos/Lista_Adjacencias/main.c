#include "graph.h"

int main() {
    // int operacao;
    //scanf("%d", &operacao);

    GRAPH *g = criar_grafo(5);
    grafo_inserir_aresta(g, 1, 2, 0);
    grafo_inserir_aresta(g, 1, 5, 0);
    grafo_inserir_aresta(g, 2, 5, 0);
    grafo_inserir_aresta(g, 2, 4, 0);
    grafo_inserir_aresta(g, 2, 3, 0);
    grafo_inserir_aresta(g, 4, 3, 0);
    grafo_inserir_aresta(g, 4, 5, 0);
    bool *visitados = (bool *)calloc(5, sizeof(bool));
    dfs_pre_ordem(g, 1, visitados);
    printf("\n");

    for(int i = 0; i < 5; i++) {
        visitados[i] = false;
    }

    dfs_pos_ordem(g, 1, visitados);
    printf("\n");
    //grafo_print_info(g);

    free(visitados);
    grafo_apagar(&g);
    return 0;
}