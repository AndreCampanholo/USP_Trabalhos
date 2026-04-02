#ifndef ARVORE_H
#define ARVORE_H

#include "../TAD_Paciente/paciente.h"
#include <stdbool.h>

//Define o nome do tipo abstrato de dado
typedef struct arvore ARVORE;

ARVORE *arvore_criar(void);
bool arvore_apagar(ARVORE **arvore);
bool arvore_inserir(ARVORE *arvore, PACIENTE *paciente);
PACIENTE *arvore_remover(ARVORE *arvore, int id);
PACIENTE *arvore_buscar(ARVORE *arvore, int id);
int arvore_tamanho(ARVORE *arvore);
bool arvore_vazia(ARVORE *arvore);
void arvore_imprimir_em_ordem(ARVORE *arvore);
PACIENTE **arvore_listar_em_ordem(ARVORE *arvore, int *outCount);
bool arvore_liberar_lista(PACIENTE **lista);

#endif
