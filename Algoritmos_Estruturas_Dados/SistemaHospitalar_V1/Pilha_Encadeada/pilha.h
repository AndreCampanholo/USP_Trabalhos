#ifndef _PILHA_H
#define _PILHA_H

#include <stdbool.h>

typedef struct pilha PILHA;

PILHA *pilha_criar(void);
void pilha_apagar(PILHA **pilha);
bool pilha_vazia(PILHA *pilha);
bool pilha_cheia(PILHA *pilha);
int pilha_tamanho(PILHA *pilha);
char *pilha_topo(PILHA *pilha);
bool pilha_empilhar(PILHA *pilha, const char *procedimento);
bool pilha_desempilhar(PILHA *pilha, char *procedimento);
void pilha_imprimir(PILHA *pilha);
bool pilha_obter_elemento(PILHA *pilha, int indice, char *procedimento);

#endif