#ifndef FILA_H
#define FILA_H
#define FILA_H
#include "../TAD_Paciente/paciente.h"

typedef struct fila_ FILA;

FILA *fila_criar(void);
void fila_apagar(FILA **fila);
bool fila_inserir_paciente(FILA *fila, PACIENTE *paciente);
PACIENTE *fila_remover_paciente(FILA *fila);
PACIENTE *fila_frente(FILA *fila);
PACIENTE *fila_atras(FILA *fila);
PACIENTE *fila_busca(FILA *fila, int chave);
int fila_tamanho(FILA *fila);
bool fila_cheia(FILA *fila);
bool fila_vazia(FILA *fila);
void fila_imprimir(FILA *fila);
void fila_esvaziar(FILA *fila);
void *fila_primeiro_no(FILA *fila);
void *fila_proximo_no(void *no);
PACIENTE *fila_no_paciente(void *no);

#endif
