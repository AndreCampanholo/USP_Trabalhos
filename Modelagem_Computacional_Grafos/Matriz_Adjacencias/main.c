#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(void)
{
  int option;
  int N = 0, x, y, w;
  int res;
  bool print_status = false;

  GRAPH *G = NULL;

  // Loop principal: lê as opções até receber -1 para sair
  scanf("%d", &option);

  while (option != -1)
  {
    print_status = false;
    switch (option)
    {
    case 0:
      // Cria um novo grafo com N vértices
      scanf("%d", &N);
      G = MyGraph(N);
      print_status = true;
      break;
    case 1:
    {
      // Adiciona-se uma aresta com seu respectivo peso
      scanf("%d %d %d", &x, &y, &w);
      add_edge(G, x, y, w);
      print_status = true;
      break;
    }
    case 2:
      // Verifica se existe aresta entre dois nós
      scanf("%d %d", &x, &y);
      if (exist_edge(G, x, y))
        printf("1");
      else
        printf("0");
      break;
    case 3:
      // Imprime todos os vizinhos do nó lido
      scanf("%d", &x);
      int *v_vizinhos = neighbors(G, x);
      if (v_vizinhos != NULL)
      {
        int i = 0;
        while (v_vizinhos[i] != -1)
        {
          printf("%d ", v_vizinhos[i] + 1);
          i++;
        }
        printf("\n");
        free(v_vizinhos);
      }
      break;
    case 4:
      // Remove uma aresta. Caso não exista, retorna -1
      scanf("%d %d", &x, &y);
      res = remove_edge(G, x, y);
      if (res == -1)
        printf("-1");
      else
        print_status = true;
      break;
    case 5:
      // Exibe a matriz de adjacência
      printf("Adjacency Matrix:\n");
      int **adj_matrix = adjacency_matrix(G);
      for (int i = 0; i < N; i++)
      {
        for (int j = 0; j < N; j++)
        {
          int curr_value = adj_matrix[i][j];
          if (curr_value == -1)
            curr_value++; // Caso a aresta não exista, incrementa 1 para, na impressão, apresentar 0 ao invés de -1
          if (j == N - 1)
            printf("%3d\n", curr_value);
          else
            printf("%3d ", curr_value);
        }
      }
      for (int i = 0; i < N; i++)
      {
        free(adj_matrix[i]);
      }
      free(adj_matrix);
      break;
    case 6:
      // Exibe o vértice com o maior número de vizinhos. Em caso de empate, imprime-se o primeiro encontrado (menor índice)
      printf("max vertex: %d\n", max_neighbors(G));
      break;
    default:
      printf("unrecognized option %d!\n", option);
    }
    scanf("%d", &option);
  }

  if (print_status)
    print_info(G);

  delete_graph(&G); // Desaloca toda memória dinâmica
  return 0;
}