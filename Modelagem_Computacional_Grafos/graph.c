#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Definição da struct do grafo como uma matriz de adjacências
typedef struct graph
{
  int size;
  int **adj;
} GRAPH;

// Função auxiliar para alocação dinâmica de matriz de adjacências
int **alloc_matrix(int size)
{
  int **matrix = malloc(size * sizeof(int *));

  if (matrix == NULL)
    return NULL;

  for (int i = 0; i < size; i++)
  {
    matrix[i] = malloc(size * sizeof(int));

    // Libera toda a matriz caso haja erro na alocação de alguma linha
    if (matrix[i] == NULL)
    {
      for (int j = 0; j < i; j++)
        free(matrix[j]);

      free(matrix);
      return NULL;
    }
  }

  // Retorna um ponteiro para a matriz de adjacências
  return matrix;
}

// Função auxiliar para liberação de matriz de adjacências
void free_matrix(int **matrix, int size)
{
  if (matrix == NULL)
    return;

  for (int i = 0; i < size; i++)
    free(matrix[i]);

  free(matrix);
}

// Função para criar o grafo dada a quantidade de arrestas
GRAPH *MyGraph(int size)
{
  GRAPH *graph = malloc(sizeof(GRAPH));

  int **adj = alloc_matrix(size);

  // Encerra a função se houver problemas na alocação do grafo ou das colunas da
  // matriz de adjacência
  if (graph == NULL || adj == NULL)
  {
    free(graph);
    free(adj);

    return NULL;
  }

  // Pre-define todas as células da matriz como -1 (inicialmente não existem arestas)
  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++)
      adj[i][j] = -1;

  graph->size = size;
  graph->adj = adj;

  // Retorna um ponteiro para o grafo
  return graph;
}

// Função para deletar o grafo (liberar memória alocada)
void delete_graph(GRAPH **graph)
{
  if (graph != NULL && *graph != NULL)
  {
    free_matrix((*graph)->adj, (*graph)->size);

    free(*graph);

    *graph = NULL;
  }
}

// Função para adicionar uma aresta ao grafo informando os nós vizinhos e seu peso
void add_edge(GRAPH *graph, int node1, int node2, int weight)
{
  if (graph == NULL)
    return;

  graph->adj[node1 - 1][node2 - 1] = weight;
  graph->adj[node2 - 1][node1 - 1] = weight;
}

// Remove uma aresta entre dois nós se existir. Retorna 1 se removeu com sucesso, -1 caso contrário
int remove_edge(GRAPH *graph, int node1, int node2)
{
  if (graph == NULL)
    return -1;

  if (node1 < 1 || node1 > graph->size || node2 < 1 || node2 > graph->size)
    return -1;

  if (graph->adj[node1 - 1][node2 - 1] != -1)
  {
    graph->adj[node1 - 1][node2 - 1] = -1;
    graph->adj[node2 - 1][node1 - 1] = -1;
    return 1;
  }
  return -1;
}

// Verifica se existe uma aresta entre dois nós
bool exist_edge(GRAPH *graph, int node1, int node2)
{
  if (graph == NULL)
    return false;

  return graph->adj[node1 - 1][node2 - 1] != -1;
}

// Retorna array com os índices dos vizinhos de um nó (terminado com -1)
int *neighbors(GRAPH *graph, int node)
{
  if (graph == NULL)
    return NULL;

  int *neighbors_array = malloc((graph->size + 1) * sizeof(int));

  if (neighbors_array == NULL)
    return NULL;

  int neighbors_found = 0;
  for (int i = 0; i < graph->size; i++)
  {
    if (graph->adj[node - 1][i] != -1)
    {
      neighbors_array[neighbors_found] = i;
      neighbors_found++;
    }
  }
  neighbors_array[neighbors_found] = -1;
  return neighbors_array;
}

// Imprime os vértices e arestas do grafo no formato V = [...] E = [...]
void print_info(GRAPH *graph)
{
  if (graph == NULL)
    return;

  printf("V = [");

  for (int i = 0; i < graph->size - 1; i++)
    printf("%d, ", i + 1);

  printf("%d]\n", graph->size);

  printf("E = [");

  bool foundEdge = false;

  for (int j = 1; j < graph->size; j++)
  {
    for (int i = 0; i < j; i++)
    {
      if (graph->adj[i][j] != -1)
      {
        if (foundEdge)
          printf(", ");

        printf("(%d, %d)", i + 1, j + 1);
        foundEdge = true;
      }
    }
  }

  printf("]\n");
}

// Encontra o nó com maior quantidade de vizinhos
int max_neighbors(GRAPH *graph)
{
  if (graph == NULL)
    return -1;

  int max_nbs = -1, max_node = -1, cur;

  for (int i = 0; i < graph->size; i++)
  {
    cur = 0;

    for (int j = 0; j < graph->size; j++)
    {
      cur += graph->adj[i][j] != -1;
    }

    if (cur > max_nbs)
    {
      max_nbs = cur;
      max_node = i;
    }
  }
  return max_node + 1;
}

// Cria uma cópia da matriz de adjacência (para não modificar a original)
int **adjacency_matrix(GRAPH *graph)
{
  if (graph == NULL)
    return NULL;

  int **adj = alloc_matrix(graph->size);

  if (adj == NULL)
    return NULL;

  for (int i = 0; i < graph->size; i++)
    for (int j = 0; j < graph->size; j++)
      adj[i][j] = graph->adj[i][j];

  return adj;
}