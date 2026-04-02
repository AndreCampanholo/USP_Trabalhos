#ifndef ITEM_H
#define ITEM_H

#include <stdbool.h>
#include "../Pilha_Encadeada/pilha.h"

typedef struct paciente PACIENTE;

PACIENTE *paciente_criar(int id, const char *nome);
bool paciente_apagar(PACIENTE **paciente);
void paciente_imprimir(PACIENTE *paciente);
int paciente_get_id(PACIENTE *paciente);
char *paciente_get_nome(PACIENTE *paciente);
bool paciente_set_id(PACIENTE *paciente, int id);
bool paciente_set_nome(PACIENTE *paciente, const char *nome);
PILHA *paciente_get_historico(PACIENTE *paciente);

#endif
