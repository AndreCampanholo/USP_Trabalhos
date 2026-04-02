#ifndef PACIENTE_H
#define PACIENTE_H

#include <stdbool.h>
#include "../Pilha_Encadeada/pilha.h"

// Define o nome do tipo abstrato de dado
typedef struct paciente PACIENTE;

PACIENTE *paciente_criar(int id, const char *nome);
bool paciente_apagar(PACIENTE **paciente);
void paciente_imprimir(PACIENTE *paciente);
int paciente_get_id(PACIENTE *paciente);
char *paciente_get_nome(PACIENTE *paciente);
bool paciente_set_prioridade(PACIENTE *paciente, int prioridade);
int paciente_get_prioridade(PACIENTE *paciente);
PILHA *paciente_get_historico(PACIENTE *paciente);

#endif
