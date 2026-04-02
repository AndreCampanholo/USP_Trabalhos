#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lista.h"
#include "../TAD_Paciente/paciente.h"

typedef struct no_
{
    PACIENTE *conteudo;
    struct no_ *proximo;
} NO;

struct lista_
{
    NO *inicio;
    NO *fim;
    int tamanho;
    bool ordenada;
};

LISTA *lista_criar(bool ordenada)
{
    LISTA *l = (LISTA *)malloc(sizeof(LISTA));
    if (l)
    {
        l->inicio = NULL;
        l->fim = NULL;
        l->tamanho = 0;
        l->ordenada = ordenada;
    }
    return (l);
}

bool lista_inserir_fim(LISTA *l, PACIENTE *conteudo)
{
    NO *p = (NO *)malloc(sizeof(NO));
    if (p)
    {
        p->conteudo = conteudo;
        p->proximo = NULL;
        if (l->tamanho == 0)
        {
            l->inicio = p;
        }
        else
        {
            l->fim->proximo = p;
        }
        l->fim = p;
        l->tamanho++;
        return (true);
    }
    return (false);
}

bool lista_inserir_ordenada(LISTA *l, PACIENTE *conteudo)
{
    NO *novo = (NO *)malloc(sizeof(NO));
    if (novo == NULL)
    {
        return false;
    }

    novo->conteudo = conteudo;
    novo->proximo = NULL;

    if (lista_vazia(l))
    {
        l->inicio = novo;
        l->fim = novo;
        l->tamanho++;
        return true;
    }

    NO *anterior = NULL;
    NO *atual = l->inicio;

    while (atual != NULL && paciente_get_id(atual->conteudo) < paciente_get_id(conteudo))
    {
        anterior = atual;
        atual = atual->proximo;
    }

    if (anterior == NULL)
    {
        novo->proximo = l->inicio;
        l->inicio = novo;
        if (l->fim == NULL)
        {
            l->fim = novo;
        }
    }
    else
    {
        novo->proximo = atual;
        anterior->proximo = novo;
        if (atual == NULL)
        {
            l->fim = novo;
        }
    }
    l->tamanho++;
    return true;
}

bool lista_inserir(LISTA *l, PACIENTE *conteudo)
{
    bool x = false;
    if (l != NULL)
    {
        NO *p = l->inicio;
        int novo_id = paciente_get_id(conteudo);
        while (p != NULL)
        {
            if (paciente_get_id(p->conteudo) == novo_id)
            {
                return false;
            }
            p = p->proximo;
        }
        if (l->ordenada)
        {
            x = lista_inserir_ordenada(l, conteudo);
        }
        else
        {
            x = lista_inserir_fim(l, conteudo);
        }
    }
    return x;
}

PACIENTE *lista_busca(LISTA *l, int chave)
{
    if (l != NULL)
    {
        NO *p = l->inicio;
        while (p != NULL)
        {
            if (paciente_get_id(p->conteudo) == chave)
            {
                return (p->conteudo);
            }
            p = p->proximo;
        }
    }
    return (NULL);
}

PACIENTE *lista_remover(LISTA *l, int chave)
{
    if (l == NULL || lista_vazia(l))
        return NULL;

    NO *p = l->inicio;
    NO *anterior = NULL;

    while (p != NULL && paciente_get_id(p->conteudo) != chave)
    {
        anterior = p;
        p = p->proximo;
    }

    if (p == NULL)
        return NULL;

    if (anterior == NULL)
    {
        l->inicio = p->proximo;
        if (l->inicio == NULL)
            l->fim = NULL;
    }
    else
    {
        anterior->proximo = p->proximo;
        if (p == l->fim)
            l->fim = anterior;
    }

    PACIENTE *paciente = p->conteudo;
    p->proximo = NULL;
    free(p);
    p = NULL;
    l->tamanho--;
    return paciente;
}

PACIENTE *lista_primeiro(LISTA *l)
{
    if (l != NULL && l->inicio != NULL)
    {
        return l->inicio->conteudo;
    }
    return NULL;
}

int lista_tamanho(LISTA *l)
{
    if (l != NULL)
        return (l->tamanho);
    return (-1);
}

bool lista_cheia(LISTA *l)
{
    if (l != NULL)
    {
        NO *novo = (NO *)malloc(sizeof(NO));
        if (novo == NULL)
            return true;
        free(novo);
        return false;
    }
    return false;
}

bool lista_vazia(LISTA *l)
{
    if (l != NULL && l->tamanho == 0)
        return true;
    return false;
}

bool lista_apagar(LISTA **l)
{
    if (l != NULL && *l != NULL)
    {
        NO *aux;
        while ((*l)->inicio != NULL)
        {
            aux = (*l)->inicio;
            (*l)->inicio = (*l)->inicio->proximo;
            paciente_apagar(&(aux->conteudo));
            free(aux);
        }
        free(*l);
        *l = NULL;
        return true;
    }
    return false;
}

void lista_imprimir(LISTA *l)
{
    if (l == NULL || l->inicio == NULL)
    {
        printf("Lista de pacientes vazia.\n");
        return;
    }
    NO *p = l->inicio;
    printf("Pacientes registrados:\n");
    while (p != NULL)
    {
        paciente_imprimir(p->conteudo);
        p = p->proximo;
    }
}

void *lista_primeiro_no(LISTA *lista)
{
    if (!lista)
        return NULL;
    return (void *)lista->inicio;
}

void *lista_proximo_no(void *no)
{
    if (!no)
        return NULL;
    return (void *)(((NO *)no)->proximo);
}

PACIENTE *lista_no_paciente(void *no)
{
    if (!no)
        return NULL;
    return ((NO *)no)->conteudo;
}

void lista_esvaziar(LISTA *lista) {
    if(lista == NULL || lista_vazia(lista)) return;

    NO *aux;
    while (lista->inicio != NULL) {
        aux = lista->inicio;
        lista->inicio = lista->inicio->proximo;
        paciente_apagar(&(aux->conteudo));
        free(aux);
    }
    lista->fim = NULL;
    lista->tamanho = 0;
}