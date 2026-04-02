#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pilha.h"

//cada elemento da pilha possui um procedimento (string) e um ponteiro para o elemento anterior
//Implementação de pilha encadeada (LIFO) com máximo de 10 procedimentos por paciente
typedef struct no NO;
struct no
{
    char procedimento[100];
    NO *anterior;
};

struct pilha
{
    NO *topo;
    int tamanho;
};

PILHA *pilha_criar()
{
    PILHA *pilha = (PILHA *)malloc(sizeof(PILHA));
    if (pilha != NULL)
    {
        pilha->topo = NULL;
        pilha->tamanho = 0;
    }
    return pilha;
}

//libera todos os nós (procedimentos) e depois a pilha em si
bool pilha_apagar(PILHA **pilha)
{
    if (pilha && *pilha)
    {
        NO *paux;
        while ((*pilha)->topo != NULL)
        {
            paux = (*pilha)->topo;
            (*pilha)->topo = (*pilha)->topo->anterior;
            free(paux);
        }
        free(*pilha);
        *pilha = NULL;
        return true;
    }
    return false;
}

bool pilha_vazia(PILHA *pilha)
{
    if (pilha != NULL)
        return (pilha->tamanho == 0);
    return false;
}

bool pilha_cheia(PILHA *pilha)
{
    if (pilha != NULL && pilha->tamanho >= 10)
    {
        return true;
    }
    return false;
}

int pilha_tamanho(PILHA *pilha)
{
    return (pilha != NULL) ? pilha->tamanho : -1;
}

//adiciona novo procedimento no topo da pilha (LIFO)
bool pilha_empilhar(PILHA *pilha, const char *procedimento)
{
    if (!pilha_cheia(pilha))
    {
        NO *pnovo = (NO *)malloc(sizeof(NO));
        if (pnovo != NULL)
        {
            snprintf(pnovo->procedimento, sizeof(pnovo->procedimento), "%s", procedimento);
            pnovo->anterior = pilha->topo;
            pilha->topo = pnovo;
            pilha->tamanho++;
            return true;
        }
    }
    return false;
}

//retira procedimento do topo da pilha (LIFO)
//Copia o procedimento removido em 'procedimento' se não for NULL
bool pilha_desempilhar(PILHA *pilha, char *procedimento)
{
    if (pilha != NULL && !pilha_vazia(pilha))
    {
        NO *pno = pilha->topo;
        if (procedimento != NULL)
        {
            snprintf(procedimento, 100, "%s", pno->procedimento);
        }
        pilha->topo = pilha->topo->anterior;
        free(pno);
        pilha->tamanho--;
        return true;
    }
    return false;
}

void pilha_imprimir(PILHA *pilha)
{
    if (pilha != NULL && !pilha_vazia(pilha))
    {
        NO *aux = pilha->topo;
        while (aux != NULL)
        {
            printf("- %s\n", aux->procedimento);
            aux = aux->anterior;
        }
    }
    else
    {
        printf("Histórico vazio!\n");
    }
    if (pilha_cheia(pilha))
    {
        printf("Histórico cheio!\n");
    }
}

bool pilha_obter_elemento(PILHA *pilha, int indice, char *procedimento)
{
    if (!pilha || indice < 0 || indice >= pilha->tamanho)
        return false;
    int tam = pilha->tamanho;
    // Alocar dinamicamente em vez de usar VLA (Variable Length Array)
    char **temp = (char **)malloc(sizeof(char *) * tam);
    if (temp == NULL)
        return false;
    for (int j = 0; j < tam; j++)
    {
        temp[j] = (char *)malloc(100 * sizeof(char));
        if (temp[j] == NULL)
        {
            for (int k = 0; k < j; k++)
                free(temp[k]);
            free(temp);
            return false;
        }
    }
    NO *no = pilha->topo;
    int i = tam - 1;
    while (no && i >= 0)
    {
        snprintf(temp[i], 100, "%s", no->procedimento);
        no = no->anterior;
        i--;
    }
    snprintf(procedimento, 100, "%s", temp[indice]);
    // Liberar memoria alocada
    for (int j = 0; j < tam; j++)
        free(temp[j]);
    free(temp);
    return true;
}
