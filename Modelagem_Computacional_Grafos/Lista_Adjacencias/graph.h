#ifndef FILA_H
#define FILA_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

typedef struct graph GRAPH;

GRAPH *criar_grafo(int ordem);
bool grafo_apagar(GRAPH **g);
bool grafo_inserir_aresta(GRAPH *graph, int node1, int node2, int weight);
int grafo_buscar_aresta(GRAPH *graph, int node1, int node2); // Retorna o peso da aresta, caso exista
int *grafo_vizinhos_no(GRAPH *graph, int node); // Retorna vetor de vizinhos de um nó
bool grafo_remover_aresta(GRAPH *graph, int node1, int node2);
int grafo_no_mais_vizinhos(GRAPH *graph);
void grafo_print_info(GRAPH *graph);
//int **adjacency_list(GRAPH *graph);

void dfs_pre_ordem(GRAPH *g, int no, bool *visitados);
void dfs_pos_ordem(GRAPH *g, int no, bool *visitados);

#endif