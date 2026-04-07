#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lista.h"

#define TAM 100

typedef struct no {
    int conteudo;
    struct no *proximo;
} NO;

struct lista{
    NO *inicio;
    NO *fim;
    int tamanho;
    bool ordenada;
};

//FUNÇÕES AUXILIARES
bool lista_inserir_fim(LISTA *l, int *conteudo) {
    NO *novo = (NO *)malloc(sizeof(NO));

    if(novo != NULL) {
        novo->conteudo = conteudo;
        novo->proximo = NULL;

        if(lista_vazia(l)) {
            l->inicio = novo;
        } else {
            l->fim->proximo = novo;
        }
        l->fim = novo;
        l->tamanho++;

        return true;
    }
    return false;
}

bool lista_inserir_ordenada(LISTA *l, int *conteudo) {
    NO *novo = (NO *)malloc(sizeof(NO));
    if (novo == NULL) {
        return false;
    }

    novo->conteudo = conteudo;
    novo->proximo = NULL;

    if (lista_vazia(l)) {
        l->inicio = novo;
        l->fim = novo;
        l->tamanho++;
        return true;
    }

    NO *anterior = NULL;
    NO *atual = l->inicio;

    while(atual != NULL && atual->conteudo < conteudo) {
        anterior = atual;
        atual = atual->proximo;
    }

    if(anterior == NULL) {
        novo->proximo = l->inicio; //existia um primeiro elemento e o novo vai ser inserido antes dele
        l->inicio = novo;
    } else {
        novo->proximo = atual;
        anterior->proximo = novo;
        if(atual == NULL) {
            l->fim = novo;
        }
    }
    l->tamanho++;
    return true;
}

int *lista_buscar_recursiva(NO *n, int chave) {
    if(n == NULL) {
        return NULL;
    }
    if(n->conteudo == chave) {
        return n->conteudo;
    }
    return lista_buscar_recursiva(n->proximo, chave);
}

int *lista_busca_ordenada(LISTA *l, int chave)
{
    NO *p = NULL;
    if (l != NULL)
    {
        p = l->inicio;
        while (p != NULL && p->conteudo < chave)
        {
            p = p->proximo;
        }
        if (p == NULL || p->conteudo > chave)
            return (NULL);
        else
        {
            return (p->conteudo);
        }
    }
    return (p);
}

//FUNÇÕES PRINCIPAIS
LISTA *lista_criar(bool ordenada) {
    LISTA *l = (LISTA *)malloc(sizeof(LISTA));

    if(l != NULL) {
        l->inicio = NULL;
        l->fim = NULL;
        l->tamanho = 0;
        l->ordenada = ordenada;
    }

    return l;
}

bool lista_inserir(LISTA *l, int *conteudo) {
    if(l != NULL && conteudo != NULL && !lista_cheia(l)) {
        if(l->ordenada) {
            return lista_inserir_ordenada(l, conteudo);
        } else {
            return lista_inserir_fim(l, conteudo);
        }
    }

    return false;
}

int lista_remover(LISTA *l, int chave) {
    if(l == NULL || lista_vazia(l)) {
        return NULL;
    }

    NO *tras = NULL;
    NO *frente = l->inicio;

    while(frente != NULL && frente->conteudo != chave) {
        tras = frente;
        frente = frente->proximo;
    }

    if(frente != NULL) {
        if(frente == l->inicio) {
            l->inicio = frente->proximo;
            frente->proximo = NULL;
        } else if(frente == l->fim) {
            l->fim = tras;
            l->fim->proximo = NULL;
        } else {
            tras->proximo = frente->proximo;
            frente->proximo = NULL;
        }
        int conteudo = frente->conteudo;
        free(frente);
        l->tamanho--;
        return conteudo;
    }
    return NULL;
}

int lista_busca(LISTA *l, int chave) {
    int *conteudo;

    if(l != NULL) {
        if(!l->ordenada) {
            return lista_buscar_recursiva(l->inicio, chave);
        } else {
            return lista_busca_ordenada(l, chave);
        }
    }
    
}

bool lista_apagar(LISTA **l) {
    if (l == NULL || *l == NULL) {
        return true;
    }

    NO *atual = (*l)->inicio;
    while (atual != NULL) {
        NO *prox = atual->proximo;
        free(atual);
        atual = prox;
    }

    free(*l);
    *l = NULL;
    return true;
}

bool lista_vazia(LISTA *l) {
    if(l == NULL || l->tamanho == 0) {
        return true;
    }
    return false;
}

bool lista_cheia(LISTA *l) {
    if(l != NULL && l->tamanho == TAM) {
        return true;
    }
    return false;
}