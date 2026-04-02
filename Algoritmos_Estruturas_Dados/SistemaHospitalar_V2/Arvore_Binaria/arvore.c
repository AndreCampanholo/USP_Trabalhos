#include <stdlib.h>
#include <stdio.h>
#include "arvore.h"

// Cada nó da árvore AVL tem um ponteiro para paciente, dois ponteiros para os filhos 
// esquerdo e direito, além da altura do nó (para calcular balanceamento)
typedef struct no
{
    PACIENTE *paciente;
    struct no *esq;
    struct no *dir;
    int altura;
} NO;

// A árvore AVL possui uma raiz (ponteiro para nó raiz) e o tamanho total de elementos
// Altura de cada nó é mantida para garantir O(log n) em todas operações
struct arvore
{
    NO *raiz;
    int tamanho;
};

// Obtém a altura de um nó
int avl_altura_no(NO *raiz)
{
    if (raiz != NULL)
    {
        return raiz->altura;
    }
    return -1;
}

// Retorna o maior entre dois inteiros
int max(int a, int b)
{
    return (a > b) ? a : b;
}

// Rotação simples à direita
NO *rotacao_direita(NO *a)
{
    NO *b = a->esq;

    a->esq = b->dir;
    b->dir = a;

    a->altura = 1 + max(avl_altura_no(a->esq), avl_altura_no(a->dir));
    b->altura = 1 + max(avl_altura_no(b->esq), avl_altura_no(b->dir));

    return b;
}

// Rotação simples à esquerda
NO *rotacao_esquerda(NO *a)
{
    NO *b = a->dir;

    a->dir = b->esq;
    b->esq = a;

    a->altura = 1 + max(avl_altura_no(a->esq), avl_altura_no(a->dir));
    b->altura = 1 + max(avl_altura_no(b->esq), avl_altura_no(b->dir));

    return b;
}

// Rotação dupla: esquerda-direita
NO *rotacao_esquerda_direita(NO *a)
{
    if (a != NULL)
    {
        a->esq = rotacao_esquerda(a->esq);
        return rotacao_direita(a);
    }
    return NULL;
}

// Rotação dupla: direita-esquerda
NO *rotacao_direita_esquerda(NO *a)
{
    if (a != NULL)
    {
        a->dir = rotacao_direita(a->dir);
        return rotacao_esquerda(a);
    }
    return NULL;
}

// Cria um novo nó com o paciente fornecido
NO *avl_cria_no(PACIENTE *paciente)
{
    NO *novo = (NO *)malloc(sizeof(NO));
    if (novo != NULL)
    {
        novo->altura = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        novo->paciente = paciente;
    }
    return novo;
}

// Busca recursiva de um paciente pela ID na subárvore
PACIENTE *avl_buscar(NO *no, int id)
{
    if (no == NULL)
        return NULL;

    int id_atual = paciente_get_id(no->paciente);

    if (id < id_atual)
        return avl_buscar(no->esq, id);
    else if (id > id_atual)
        return avl_buscar(no->dir, id);
    else
        return no->paciente;
}

// Inserção recursiva com balanceamento automático
NO *avl_inserir_no(NO *raiz, PACIENTE *it)
{
    if (raiz == NULL)
    {
        // Encontrou o local certo para inserir novo elemento
        raiz = avl_cria_no(it);
    }
    else if (paciente_get_id(it) < paciente_get_id(raiz->paciente))
    {
        // Chave é menor do que do nó atual, buscar à esquerda
        raiz->esq = avl_inserir_no(raiz->esq, it);
    }
    else if (paciente_get_id(it) > paciente_get_id(raiz->paciente))
    {
        // Chave é maior do que do nó atual, buscar à direita
        raiz->dir = avl_inserir_no(raiz->dir, it);
    }
    else
    {
        // Chave já existe, retorna nó raiz da árvore
        return raiz;
    }

    int altura_esq = avl_altura_no(raiz->esq), altura_dir = avl_altura_no(raiz->dir);
    raiz->altura = max(altura_esq, altura_dir) + 1;

    int fator_balanceamento = altura_esq - altura_dir;

    // Aplica rotações se necessário, para manter estrutura de AVL
    if (fator_balanceamento == -2)
    {
        if (avl_altura_no(raiz->dir->esq) - avl_altura_no(raiz->dir->dir) <= 0)
        {
            raiz = rotacao_esquerda(raiz);
        }
        else
        {
            raiz = rotacao_direita_esquerda(raiz);
        }
    }
    else if (fator_balanceamento == 2)
    {
        if (avl_altura_no(raiz->esq->esq) - avl_altura_no(raiz->esq->dir) >= 0)
        {
            raiz = rotacao_direita(raiz);
        }
        else
        {
            raiz = rotacao_esquerda_direita(raiz);
        }
    }

    return raiz;
}

// Encontra o maior elemento da subárvore à esquerda e o move para substituir o nó removido
// Preserva referências em outras estruturas (fila de prioridade) armazenando o paciente original
// Se removido != NULL, armazena o paciente do nó original (para reutilização em outras estruturas)
void troca_max_esq(NO *troca, NO *raiz, NO *ant, PACIENTE **removido)
{
    if (troca->dir != NULL)
    {
        troca_max_esq(troca->dir, raiz, troca, removido);
    }
    else
    {
        if (raiz == ant)
            ant->esq = troca->esq;
        else
            ant->dir = troca->esq;

        if (removido != NULL)
        {
            *removido = raiz->paciente;
        }
        else
        {
            paciente_apagar(&(raiz->paciente));
        }
        raiz->paciente = troca->paciente;
        free(troca);
        troca = NULL;
    }
}

// Remove um nó da árvore mantendo o paciente em memória para reutilização (não apaga PACIENTE)
// Necessário pois o paciente precisa permanecer na fila de atendimento mesmo após ser removido da árvore
// Evita dangling pointers que ocorreriam se o paciente fosse liberado aqui
NO *avl_remover_paciente(NO *raiz, int chave, PACIENTE **removido)
{
    if (raiz == NULL)
        return NULL;

    if (chave == paciente_get_id(raiz->paciente))
    {
        // Nó encontrado
        if (raiz->esq == NULL || raiz->dir == NULL)
        {
            NO *filho = (raiz->esq) ? raiz->esq : raiz->dir;
            // Retém o paciente para o chamador
            *removido = raiz->paciente;
            free(raiz);
            return filho;
        }
        else
        {
            // Caso tenha dois filhos, usa o troca_max_esq
            // Importante: troca_max_esq modifica a subárvore esquerda
            troca_max_esq(raiz->esq, raiz, raiz, removido);
        }
    }
    else if (chave < paciente_get_id(raiz->paciente))
    {
        raiz->esq = avl_remover_paciente(raiz->esq, chave, removido);
    }
    else
    {
        raiz->dir = avl_remover_paciente(raiz->dir, chave, removido);
    }

    if (raiz != NULL)
    {
        raiz->altura = max(avl_altura_no(raiz->esq), avl_altura_no(raiz->dir)) + 1;
        int fator_balanceamento = avl_altura_no(raiz->esq) - avl_altura_no(raiz->dir);

        if (fator_balanceamento == 2)
        {
            if (avl_altura_no(raiz->esq->esq) - avl_altura_no(raiz->esq->dir) >= 0)
                raiz = rotacao_direita(raiz);
            else
                raiz = rotacao_esquerda_direita(raiz);
        }
        else if (fator_balanceamento == -2)
        {
            if (avl_altura_no(raiz->dir->esq) - avl_altura_no(raiz->dir->dir) <= 0)
                raiz = rotacao_esquerda(raiz);
            else
                raiz = rotacao_direita_esquerda(raiz);
        }
    }
    return raiz;
}

// Libera recursivamente todos os nós da árvore
void avl_apagar_aux(NO *raiz)
{
    if (raiz != NULL)
    {
        avl_apagar_aux(raiz->esq);
        avl_apagar_aux(raiz->dir);
        paciente_apagar(&(raiz->paciente));
        free(raiz);
    }
}

// Imprime recursivamente todos os pacientes em ordem (esquerda -> nó -> direita)
// Resultado: pacientes ordenados por ID (para função de tabela)
void imprimir_em_ordem_tabela(NO *no, int *primeiro)
{
    if (no != NULL)
    {
        imprimir_em_ordem_tabela(no->esq, primeiro);
        
        if (*primeiro)
        {
            printf("%-35s %-10s\n", "Nome Paciente", "ID");
            printf("%-35s %-10s\n", "------------------", "-----");
            *primeiro = 0;
        }
        
        printf("%-35s %-10d\n", paciente_get_nome(no->paciente), paciente_get_id(no->paciente));
        imprimir_em_ordem_tabela(no->dir, primeiro);
    }
}

// Preenche um array com os pacientes em ordem (esquerda -> nó -> direita)
// Usado pela função arvore_listar_em_ordem para persistência de dados
int preencher_em_ordem(NO *no, PACIENTE **arr, int i)
{
    if (no == NULL)
        return i;
    i = preencher_em_ordem(no->esq, arr, i);
    arr[i++] = no->paciente;
    i = preencher_em_ordem(no->dir, arr, i);
    return i;
}

// Cria uma nova árvore vazia
ARVORE *arvore_criar(void)
{
    ARVORE *arvore = (ARVORE *)malloc(sizeof(ARVORE));
    if (arvore != NULL)
    {
        arvore->raiz = NULL;
        arvore->tamanho = 0;
    }
    return arvore;
}

// Libera toda a memória alocada pela árvore
bool arvore_apagar(ARVORE **arvore)
{
    if (arvore != NULL && *arvore != NULL)
    {
        avl_apagar_aux((*arvore)->raiz);
        free(*arvore);
        *arvore = NULL;
        return true;
    }
    return false;
}

// Insere um novo paciente na árvore
bool arvore_inserir(ARVORE *arvore, PACIENTE *paciente)
{
    if (arvore == NULL || paciente == NULL)
        return false;

    if (avl_buscar(arvore->raiz, paciente_get_id(paciente)) != NULL)
        return false;

    arvore->raiz = avl_inserir_no(arvore->raiz, paciente);
    arvore->tamanho++;
    return true;
}

// Remove um paciente da árvore sem liberar sua memória
PACIENTE *arvore_remover(ARVORE *arvore, int id)
{
    if (arvore == NULL)
        return NULL;

    PACIENTE *removido = NULL;
    arvore->raiz = avl_remover_paciente(arvore->raiz, id, &removido);
    if (removido != NULL)
        arvore->tamanho--;
    return removido;
}

// Busca um paciente pela ID
PACIENTE *arvore_buscar(ARVORE *arvore, int id)
{
    if (arvore == NULL)
        return NULL;
    return avl_buscar(arvore->raiz, id);
}

// Retorna o número de pacientes na árvore
int arvore_tamanho(ARVORE *arvore)
{
    if (arvore != NULL)
        return arvore->tamanho;
    return -1;
}

// Verifica se a árvore está vazia
bool arvore_vazia(ARVORE *arvore)
{
    if (arvore != NULL)
        return arvore->tamanho == 0;
    return true;
}

// Imprime todos os pacientes em ordem (formato tabela, sem prioridade)
void arvore_imprimir_em_ordem(ARVORE *arvore)
{
    if (arvore != NULL)
    {
        if (arvore_vazia(arvore))
        {
            printf("Banco de Dados de pacientes vazio.\n");
            return;
        }
        
        printf("\n--- LISTA DE PACIENTES (Ordenada por ID) ---\n\n");
        int primeiro = 1;
        imprimir_em_ordem_tabela(arvore->raiz, &primeiro);
        printf("\nTotal de pacientes: %d\n\n", arvore->tamanho);
    }
}

// Retorna um array com todos os pacientes em ordem (por ID)
// Alocado dinamicamente - deve ser liberado através de arvore_liberar_lista()
// Usado pela função SAVE() no TAD IO para persistência de dados
PACIENTE **arvore_listar_em_ordem(ARVORE *arvore, int *outCount)
{
    if (outCount)
        *outCount = 0;
    if (arvore == NULL || arvore->tamanho == 0)
        return NULL;

    PACIENTE **arr = (PACIENTE **)malloc(arvore->tamanho * sizeof(PACIENTE *));
    if (arr != NULL)
    {
        preencher_em_ordem(arvore->raiz, arr, 0);
        if (outCount)
            *outCount = arvore->tamanho;
    }
    return arr;
}

// Libera o array retornado por arvore_listar_em_ordem
bool arvore_liberar_lista(PACIENTE **lista)
{
    if (lista != NULL)
    {
        free(lista);
        return true;
    }
    return false;
}
