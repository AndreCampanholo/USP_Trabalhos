#ifndef FILA_PRIORIDADE_H
#define FILA_PRIORIDADE_H

#include "../TAD_Paciente/paciente.h"
#include <stdbool.h>
#include <time.h>

// Define o nome do tipo abstrato de dado
typedef struct fila_prioridade_ FILA_PRIORIDADE;
// Tipo interno para itens na lista(acessado pelo TAD IO durante o salvamento)
typedef struct fila_item_ FILA_ITEM;

FILA_PRIORIDADE *fila_prioridade_criar(int capacidade_maxima);
bool fila_prioridade_apagar(FILA_PRIORIDADE **fila);
bool fila_prioridade_inserir(FILA_PRIORIDADE *fila, PACIENTE *paciente);
// Funcao auxiliar para persistencia de dados - retorna com timestamp preservado
bool fila_prioridade_inserir_aux(FILA_PRIORIDADE *fila, PACIENTE *paciente, time_t timestamp);
PACIENTE *fila_prioridade_remover(FILA_PRIORIDADE *fila);
int fila_prioridade_tamanho(FILA_PRIORIDADE *fila);
bool fila_prioridade_vazia(FILA_PRIORIDADE *fila);
bool fila_prioridade_cheia(FILA_PRIORIDADE *fila);
void fila_prioridade_imprimir(FILA_PRIORIDADE *fila);
// Funcao auxiliar para persistencia - retorna lista de itens com timestamps
FILA_ITEM **fila_prioridade_listar(FILA_PRIORIDADE *fila, int *outCount);
// Libera o array retornado por fila_prioridade_listar
bool fila_prioridade_liberar_lista(FILA_ITEM **lista, int count);
PACIENTE *fila_prioridade_buscar_paciente(FILA_PRIORIDADE *fila, int id_paciente);

//funções para acessar elementos internos dos pacientes, utilizados para salvar os dados
PACIENTE *fila_item_get_paciente(const FILA_ITEM *item);
time_t fila_item_get_timestamp(const FILA_ITEM *item);

#endif
