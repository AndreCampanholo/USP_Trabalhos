#ifndef IO_H
#define IO_H
#include "../TAD_Paciente/paciente.h"
#include "../Fila_Encadeada/fila.h"
#include "../Lista_Simples_Encadeada/lista.h"
#include <stdbool.h>

bool SAVE(LISTA *lista, FILA *fila);
bool LOAD(LISTA **lista, FILA **fila);

#endif
