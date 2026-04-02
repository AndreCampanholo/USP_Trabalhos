#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "../Arvore_Binaria/arvore.h"
#include "../Fila_Prioridade/fila_prioridade.h"

void imprimir_escolha_operacao(void);
void registrar_paciente(ARVORE *arvore, FILA_PRIORIDADE *fila);
void registrar_obito(ARVORE *arvore, FILA_PRIORIDADE *fila);
void adicionar_procedimento(ARVORE *arvore);
void desfazer_procedimento(ARVORE *arvore);
void chamar_paciente(FILA_PRIORIDADE *fila);
void mostrar_fila(FILA_PRIORIDADE *fila);
void mostrar_historico(ARVORE *arvore);
void salvar_pacientes(ARVORE *arvore, FILA_PRIORIDADE *fila);

#endif
