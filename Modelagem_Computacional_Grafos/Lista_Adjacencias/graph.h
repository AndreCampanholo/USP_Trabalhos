#ifndef FILA_H
#define FILA_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct graph GRAPH;

GRAPH *MyGraph(int size);
void delete_graph(GRAPH **graph);
void add_edge(GRAPH *graph, int node1, int node2, int weight);
bool exist_edge(GRAPH *graph, int node1, int node2);
int *neighbors(GRAPH *graph, int node);
int remove_edge(GRAPH *graph, int node1, int node2);
int max_neighbors(GRAPH *graph);
void print_info(GRAPH *graph);
int **adjacency_list(GRAPH *graph);

#endif