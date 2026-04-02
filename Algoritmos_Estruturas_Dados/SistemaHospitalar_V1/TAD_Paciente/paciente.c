#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "paciente.h"
#include "../Pilha_Encadeada/pilha.h"

struct paciente
{
   int id;
   char nome[100];
   PILHA *historico;
};

PACIENTE *paciente_criar(int id, const char *nome)
{
   PACIENTE *paciente = (PACIENTE *)malloc(sizeof(PACIENTE));
   if (paciente != NULL)
   {
      paciente->id = id;
      snprintf(paciente->nome, sizeof(paciente->nome), "%s", nome ? nome : "");
      paciente->historico = pilha_criar();
      return paciente;
   }
   return NULL;
}

bool paciente_apagar(PACIENTE **paciente)
{
   if (paciente != NULL && *paciente != NULL)
   {
      if ((*paciente)->historico != NULL)
      {
         pilha_apagar(&((*paciente)->historico));
      }
      free(*paciente);
      *paciente = NULL;
      return true;
   }
   return false;
}

void paciente_imprimir(PACIENTE *paciente)
{
   if (paciente != NULL)
   {
      printf("%s - %d\n", paciente->nome, paciente->id);
   }
}

PILHA *paciente_get_historico(PACIENTE *paciente)
{
   if (paciente != NULL)
      return paciente->historico;
   return NULL;
}

int paciente_get_id(PACIENTE *paciente)
{
   if (paciente != NULL)
      return (paciente->id);
   exit(1);
}

char *paciente_get_nome(PACIENTE *paciente)
{
   if (paciente != NULL)
      return (paciente->nome);
   return NULL;
}

bool paciente_set_id(PACIENTE *paciente, int id)
{
   if (paciente != NULL)
   {
      paciente->id = id;
      return (true);
   }
   return (false);
}

bool paciente_set_nome(PACIENTE *paciente, const char *nome)
{
   if (paciente != NULL && nome != NULL)
   {
      snprintf(paciente->nome, sizeof(paciente->nome), "%s", nome);
      return true;
   }
   return false;
}