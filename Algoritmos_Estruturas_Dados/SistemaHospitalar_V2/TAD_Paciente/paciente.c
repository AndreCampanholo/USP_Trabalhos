#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "paciente.h"
#include "../Pilha_Encadeada/pilha.h"

struct paciente
{
   int id;
   char nome[100];
   int prioridade;        // 1 = Emergência ... 5 = Consulta (menor número = maior prioridade)
   PILHA *historico;      // histórico de procedimentos (LIFO, máximo 10)
};

// cria um paciente e retorna-o (usado ao registrar um novo paciente)
PACIENTE *paciente_criar(int id, const char *nome)
{
   PACIENTE *paciente = (PACIENTE *)malloc(sizeof(PACIENTE));
   if (paciente != NULL)
   {
      paciente->id = id;
      snprintf(paciente->nome, sizeof(paciente->nome), "%s", nome ? nome : "");
      paciente->prioridade = 3;            // define como 3 por padrão
      paciente->historico = pilha_criar(); // cria a pilha do histórico médico do paciente
      if (!paciente->historico)
      {
         // se não for possível criar o histórico médico, apaga o paciente criado
         free(paciente);
         return NULL;
      }
      return paciente;
   }
   return NULL;
}

// apaga um paciente (usado ao registrar óbito)
bool paciente_apagar(PACIENTE **paciente)
{
   if (paciente != NULL && *paciente != NULL)
   {
      if ((*paciente)->historico)
      {
         pilha_apagar(&((*paciente)->historico));
      }
      free(*paciente);
      *paciente = NULL;
      return true;
   }
   return false;
}

// imprime o nome e o id de um paciente
void paciente_imprimir(PACIENTE *paciente)
{
   if (paciente != NULL)
   {
      printf("Nome: %s - ID: %d\n", paciente->nome, paciente->id);
   }
}

// retorna o id de um paciente
int paciente_get_id(PACIENTE *paciente)
{
   if (paciente != NULL)
      return (paciente->id);
   return -1; // Retorna -1 em caso de erro, sem encerrar o programa
}

// retorna o nome de um paciente
char *paciente_get_nome(PACIENTE *paciente)
{
   if (paciente != NULL)
      return (paciente->nome);
   return NULL;
}

// altera a prioridade de um paciente
bool paciente_set_prioridade(PACIENTE *paciente, int prioridade)
{
   if (paciente != NULL && prioridade >= 1 && prioridade <= 5)
   {
      paciente->prioridade = prioridade;
      return true;
   }
   return false;
}

// retorna a prioridade de um paciente
int paciente_get_prioridade(PACIENTE *paciente)
{
   if (paciente != NULL)
      return paciente->prioridade;
   return -1;
}

// retorna a pilha do histórico de um paciente
PILHA *paciente_get_historico(PACIENTE *paciente)
{
   if (paciente != NULL)
      return paciente->historico;
   return NULL;
}
