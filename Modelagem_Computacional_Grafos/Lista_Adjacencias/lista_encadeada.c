#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lista.h"

#define TAM 100

typedef struct no {
    int id_no;
    int peso;
    struct no *proximo;
} NO;

struct lista{
    NO *inicio;
    NO *fim;
    int tamanho;
};

//FUNÇÕES AUXILIARES

bool lista_inserir_ordenada(LISTA *l, int id_no, int peso) {
    NO *novo = (NO *)malloc(sizeof(NO));
    if (novo == NULL) {
        return false;
    }

    novo->id_no = id_no;
    novo->peso = peso;
    novo->proximo = NULL;

    if (lista_vazia(l)) {
        l->inicio = novo;
        l->fim = novo;
        l->tamanho++;
        return true;
    }

    NO *anterior = NULL;
    NO *atual = l->inicio;

    while(atual != NULL && atual->id_no < id_no) {
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

int lista_busca_ordenada(LISTA *l, int b)
{
    if (l != NULL)
    {
        NO *p = l->inicio;
        while (p != NULL && p->id_no < b)
        {
            p = p->proximo;
        }
        if (p == NULL || p->id_no > b)
            return -1;
        else
        {
            return (p->peso);
        }
    }
    return -1;
}

//FUNÇÕES PRINCIPAIS
LISTA *lista_criar() {
    LISTA *l = (LISTA *)malloc(sizeof(LISTA));

    if(l != NULL) {
        l->inicio = NULL;
        l->fim = NULL;
        l->tamanho = 0;
    }

    return l;
}

bool lista_inserir(LISTA *l, int id_no, int peso) {
    if(l != NULL && !lista_cheia(l)) {
        return lista_inserir_ordenada(l, id_no, peso);
    }

    return false;
}

bool lista_remover(LISTA *l, int chave) {
    if(l == NULL || lista_vazia(l)) {
        return false;
    }

    NO *tras = NULL;
    NO *frente = l->inicio;

    while(frente != NULL && frente->id_no != chave) {
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
        free(frente);
        l->tamanho--;
        return true;
    }
    return false;
}

int lista_busca(LISTA *l, int chave) {
    if(l != NULL) 
        return lista_busca_ordenada(l, chave);
    return -1;
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

int lista_tamanho(LISTA *l) {
    if(l == NULL) {
        return 0;
    }
    return l->tamanho;
}

int *lista_extrair_no_ids(LISTA *l) {
    if(l != NULL) {
        NO *aux = l->inicio;
        int *vizinhos = (int *)malloc(l->tamanho * sizeof(int));
        int i = 0;
        while(aux != NULL) {
            vizinhos[i] = aux->id_no;
            aux = aux->proximo;
            i++;
        }
        return vizinhos;
    }
    return NULL;
}

int **lista_percorrer_arestas(LISTA *l) {
    if(l != NULL && l->inicio != NULL && l->tamanho > 0) {
        NO* aux = l->inicio;
        int **no_b_peso = (int **)malloc(l->tamanho * sizeof(int *));
        if(no_b_peso == NULL) {
            return NULL;
        }

        for(int i = 0; i < l->tamanho; i++) {
            no_b_peso[i] = (int *)malloc(2 * sizeof(int));
            if(no_b_peso[i] == NULL) {
                for(int j = 0; j < i; j++) {
                    free(no_b_peso[j]);
                }
                free(no_b_peso);
                return NULL;
            }
        }

        int i = 0;
        while(aux != NULL && i < l->tamanho) {
            no_b_peso[i][0] = aux->id_no;
            no_b_peso[i][1] = aux->peso;
            aux = aux->proximo;
            i++;
        }
        return no_b_peso;
    }
    return NULL;
}