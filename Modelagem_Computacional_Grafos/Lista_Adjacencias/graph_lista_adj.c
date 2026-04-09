#include "graph.h"
#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct graph {
    int ordem;
    LISTA **lista_adj;
};

// O grafo construído pelas funções abaixo possui a estrutura de "Lista de Adjacências", isto é, há um vetor que armazena, para cada nó, uma lista ligada com seus vizinhos e o peso dessas conexões. Tratam-se de listas ordenadas, por escolha de implementação.

//Funções Auxiliares
void grafo_printar_arestas_no(GRAPH *g) {
    if(g == NULL) {
        printf("E = []\n");
        return;
    }

    printf("E = [");
    bool primeira_aresta = true;

    for(int i = 0; i < g->ordem; i++) {
        int total_arestas = lista_tamanho(g->lista_adj[i]);
        if(total_arestas <= 0) {
            continue;
        }

        int **aresta_atual = lista_percorrer_arestas(g->lista_adj[i]);
        if(aresta_atual == NULL) {
            continue;
        }

        for(int j = 0; j < total_arestas; j++) {
            if(!primeira_aresta) {
                printf(", ");
            }
            printf("(%d, %d, %d)", i + 1, aresta_atual[j][0] + 1, aresta_atual[j][1]);
            primeira_aresta = false;
        }

        for(int j = 0; j < total_arestas; j++) {
            free(aresta_atual[j]);
        }
        free(aresta_atual);
    }

    printf("]\n");
}

GRAPH *criar_grafo(int ordem) {
    if(ordem <= 0) return NULL;

    GRAPH *g = (GRAPH *)malloc(sizeof(GRAPH));
    if(g != NULL) {
        g->ordem = ordem;
        g->lista_adj = (LISTA **)malloc(ordem * sizeof(LISTA *));
        if(g->lista_adj == NULL) {
            free(g);
            return NULL;
        }

        for(int i = 0; i < g->ordem; i++) {
            g->lista_adj[i] = lista_criar();
            if(g->lista_adj[i] == NULL) {
                for(int j = 0; j < i; j++) {
                    lista_apagar(&(g->lista_adj[j]));
                }
                free(g->lista_adj);
                free(g);
                return NULL;
            }
        }
    }

    return g;
}

bool grafo_apagar(GRAPH **g) {
    if(g == NULL || *g == NULL) return true;

    for(int i = 0; i < (*g)->ordem; i++) {
        lista_apagar(&((*g)->lista_adj[i]));
    }
    free((*g)->lista_adj);
    (*g)->lista_adj = NULL;
    free(*g);
    *g = NULL;
    return true;
}

bool grafo_inserir_aresta(GRAPH *g, int a, int b, int peso) {
    if(g != NULL && a > 0 && a <= g->ordem && b > 0 && b <= g->ordem) {
        if(lista_inserir(g->lista_adj[a-1], b - 1, peso)) {
            if(lista_inserir(g->lista_adj[b-1], a - 1, peso))
                return true;
            else
                lista_remover(g->lista_adj[a-1], b - 1);
        }        
    }
    return false;
}

int grafo_buscar_aresta(GRAPH *g, int a, int b) {
    if(g == NULL || a <= 0 || a > g->ordem || b <= 0 || b > g->ordem) return -1;
    return lista_busca(g->lista_adj[a-1], b - 1);
}

int *grafo_vizinhos_no(GRAPH *g, int no_id) {
    if(g != NULL && no_id > 0 && no_id <= g->ordem ) {
        return lista_extrair_no_ids(g->lista_adj[no_id-1]);
    }
    return NULL;
}

bool grafo_remover_aresta(GRAPH *g, int a, int b) {
    if(g == NULL || a <= 0 || a > g->ordem || b <= 0 || b > g->ordem) return false;

    lista_remover(g->lista_adj[a-1], b-1);
    lista_remover(g->lista_adj[b-1], a-1);

    return true;
}

int grafo_no_mais_vizinhos(GRAPH *g) {
    if (g != NULL) {
        int max = 0;
        int max_no = 0;
        for(int i = 0; i < g->ordem; i++) {
            int curr = lista_tamanho(g->lista_adj[i]);
            if(curr > max) {
                max = curr; 
                max_no = i;
            } 
        }
        return max_no;
    }
    return -1;
}

void grafo_print_info(GRAPH *g) {
    if(g != NULL) {
        printf("V = [");
        for(int i = 0; i < g->ordem; i++) {
            if(i == g->ordem - 1) 
                printf("%d]\n", i + 1);
            else
                printf("%d, ", i + 1);
        }
        grafo_printar_arestas_no(g);
    }
}

bool no_valido(GRAPH *g, int no) {
    if(g == NULL || no <= 0 || no > g->ordem) return false;
    return true;
}

// Os dois algoritmos abaixo implementam buscas em grafos por profundidade. Pelo fato de que as listas de adjacências são ordenadas, elas sempre retornarão o inverso uma da outra, e os nós sempre estarão em ordem crescente (para dfs em pré-ordem) ou decrescente (para dfs em pós-ordem).

void dfs_pre_ordem(GRAPH *g, int no, bool *visitados) {
    if(g == NULL || !no_valido(g, no)) return;
    
    visitados[no - 1] = true;
    printf("%d ", no);  // processa ANTES dos filhos (pré-ordem)
    
    int *vizinhos = grafo_vizinhos_no(g, no);
    int num_vizinhos = lista_tamanho(g->lista_adj[no - 1]);
    
    for(int i = 0; i < num_vizinhos; i++) {
        int vizinho = vizinhos[i];
        if(!visitados[vizinho]) {
            dfs_pre_ordem(g, vizinho + 1, visitados);
        }
    }
    free(vizinhos);
}

void dfs_pos_ordem(GRAPH *g, int no, bool *visitados) {
    if(g != NULL && no_valido(g, no)) {
        visitados[no-1] = true;
        
        int *vizinhos = grafo_vizinhos_no(g, no);
        int qtd_vizinhos = lista_tamanho(g->lista_adj[no-1]);

        for(int i = 0; i < qtd_vizinhos; i++) {
            if(!visitados[vizinhos[i]]) {
                dfs_pos_ordem(g, vizinhos[i] + 1, visitados); // +1 pois grafo_vizinhos_no retorna o id interno do nó (um a menos do que o visto pelo usuário)
            }
        }

        free(vizinhos);

        printf("%d ", no);
    }
}