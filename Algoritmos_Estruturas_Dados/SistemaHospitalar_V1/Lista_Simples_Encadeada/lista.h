#ifndef LISTA_H
#define LISTA_H

#include "../TAD_Paciente/paciente.h"

typedef struct lista_ LISTA;

LISTA *lista_criar(bool ordenada);
bool lista_inserir(LISTA *lista, PACIENTE *paciente);
PACIENTE *lista_remover(LISTA *lista, int chave);
bool lista_apagar(LISTA **lista);
PACIENTE *lista_busca(LISTA *lista, int chave);
PACIENTE *lista_primeiro(LISTA *lista);
int lista_tamanho(LISTA *lista);
bool lista_vazia(LISTA *lista);
bool lista_cheia(LISTA *lista);
void lista_imprimir(LISTA *lista);
void lista_esvaziar(LISTA *lista);
void *lista_primeiro_no(LISTA *lista);
void *lista_proximo_no(void *no);
PACIENTE *lista_no_paciente(void *no);

#endif
