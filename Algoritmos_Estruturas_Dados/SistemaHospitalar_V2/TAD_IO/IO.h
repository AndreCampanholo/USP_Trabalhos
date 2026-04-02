#ifndef IO_H
#define IO_H

#include "../TAD_Paciente/paciente.h"
#include "../Fila_Prioridade/fila_prioridade.h"
#include "../Arvore_Binaria/arvore.h"
#include <stdbool.h>

// Funções de persistência - Salvar e carregar dados
bool SAVE(ARVORE *arvore, FILA_PRIORIDADE *fila);
bool LOAD(ARVORE **arvore, FILA_PRIORIDADE **fila);

#endif
