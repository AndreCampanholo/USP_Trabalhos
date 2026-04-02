
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "../Lista_Simples_Encadeada/lista.h"
#include "../Fila_Encadeada/fila.h"

void imprimir_escolha_operacao(void);
void registrar_paciente(LISTA *lista, FILA *fila);
void registrar_obito(LISTA *lista, FILA *fila);
void adicionar_procedimento(LISTA *lista);
void desfazer_procedimento(LISTA *lista);
void chamar_paciente(FILA *fila);
void mostrar_fila(FILA *fila);
void mostrar_historico(LISTA *lista);
void salvar_pacientes(LISTA *lista, FILA *fila);

#endif
