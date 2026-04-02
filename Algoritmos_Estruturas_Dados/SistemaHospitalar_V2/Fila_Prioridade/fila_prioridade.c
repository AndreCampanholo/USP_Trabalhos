#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "fila_prioridade.h"

//struct criada para facilitar tratamento da fila de prioridade (max-heap por urgência)
//Inclui timestamp (hora de chegada dos pacientes) para desempate FIFO quando prioridades são iguais
//Nota: Max-heap em relação à urgência/gravidade: número menor (1) = máxima urgência
typedef struct elemento_fila_
{
    PACIENTE *paciente;
    time_t timestamp; // Hora de chegada; usado para desempate (FIFO) quando prioridade é igual
} ELEMENTO_FILA;

// Implementação do tipo de elementos armazenados na fila: inclui paciente e seu timestamp
struct fila_item_
{
    PACIENTE *paciente;
    time_t timestamp;
};

struct fila_prioridade_
{
    ELEMENTO_FILA *heap;
    int tamanho;
    int capacidade;
};


// Funcoes auxiliares privadas
int pai(int i)
{
    return (i - 1) / 2;
}

int filho_esquerdo(int i)
{
    return 2 * i + 1;
}

int filho_direito(int i)
{
    return 2 * i + 2;
}

//comparação entre prioridade de dois pacientes
// Retorna true se e1 tem MAIOR prioridade que e2
// Prioridade maior = número MENOR (1 é max, 5 é min)
// Em caso de prioridade igual, compara timestamp (FIFO)
bool comparar_prioridade(ELEMENTO_FILA e1, ELEMENTO_FILA e2)
{
    int prio1 = paciente_get_prioridade(e1.paciente);
    int prio2 = paciente_get_prioridade(e2.paciente);

    if (prio1 != prio2)
        return prio1 < prio2; // Prioridade maior = número menor
    else
        return e1.timestamp < e2.timestamp; // Desempate FIFO: quem chegou primeiro
}

void heap_swap(ELEMENTO_FILA *a, ELEMENTO_FILA *b)
{
    ELEMENTO_FILA temp = *a;
    *a = *b;
    *b = temp;
}

// Sobe o elemento para manter propriedade do max-heap (números menores = maior urgência)
void fix_up(FILA_PRIORIDADE *fila, int indice)
{
    while (indice > 0 && comparar_prioridade(fila->heap[indice], fila->heap[pai(indice)]))
    {
        heap_swap(&fila->heap[indice], &fila->heap[pai(indice)]);
        indice = pai(indice);
    }
}

// Desce o elemento para manter propriedade do max-heap (números menores = maior urgência)
void fix_down(FILA_PRIORIDADE *fila, int indice)
{
    int maior = indice;
    int esq = filho_esquerdo(indice);
    int dir = filho_direito(indice);

    if (esq < fila->tamanho && comparar_prioridade(fila->heap[esq], fila->heap[maior]))
        maior = esq;

    if (dir < fila->tamanho && comparar_prioridade(fila->heap[dir], fila->heap[maior]))
        maior = dir;

    if (maior != indice)
    {
        heap_swap(&fila->heap[indice], &fila->heap[maior]);
        fix_down(fila, maior);
    }
}
//merge_sort implementado como função auxiliar para impressão ordenada da fila
//Recebe um vetor auxiliar de ELEMENTO_FILA e o ordena por prioridade (número menor = maior urgência)
//Em caso de prioridade igual, ordena por timestamp (FIFO - quem chegou primeiro é atendido)


void merge(ELEMENTO_FILA *arr, int esq, int meio, int dir)
{
    int i = esq, j = meio + 1, k = 0;
    ELEMENTO_FILA *temp = (ELEMENTO_FILA *)malloc(sizeof(ELEMENTO_FILA) * (dir - esq + 1));

    if (temp == NULL)
        return;

    while (i <= meio && j <= dir)
    {
        if (comparar_prioridade(arr[i], arr[j]))
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }

    while (i <= meio)
        temp[k++] = arr[i++];

    while (j <= dir)
        temp[k++] = arr[j++];

    for (i = esq, k = 0; i <= dir; i++, k++)
        arr[i] = temp[k];

    free(temp);
}

void merge_sort_rec(ELEMENTO_FILA *arr, int esq, int dir)
{
    if (esq < dir)
    {
        int meio = esq + (dir - esq) / 2;
        merge_sort_rec(arr, esq, meio);
        merge_sort_rec(arr, meio + 1, dir);
        merge(arr, esq, meio, dir);
    }
}
void merge_sort(ELEMENTO_FILA *arr, int tamanho)
{
    if (tamanho > 1)
        merge_sort_rec(arr, 0, tamanho - 1);
}
// Funções públicas

FILA_PRIORIDADE *fila_prioridade_criar(int capacidade_maxima)
{
    if (capacidade_maxima <= 0)
        capacidade_maxima = 100; // limita capacidade da fila a 100 pessoas. Pode ser adaptado de acordo com a necessidade de uso

    FILA_PRIORIDADE *fila = (FILA_PRIORIDADE *)malloc(sizeof(FILA_PRIORIDADE));
    if (fila != NULL)
    {
        fila->heap = (ELEMENTO_FILA *)malloc(sizeof(ELEMENTO_FILA) * capacidade_maxima);
        if (fila->heap != NULL)
        {
            fila->tamanho = 0;
            fila->capacidade = capacidade_maxima;
            return fila;
        }
        free(fila);
    }
    return NULL;
}

bool fila_prioridade_apagar(FILA_PRIORIDADE **fila)
{
    if (fila != NULL && *fila != NULL)
    {
        // Não liberamos os pacientes aqui, pois eles são gerenciados pela árvore
        if ((*fila)->heap != NULL)
        {
            free((*fila)->heap);
            (*fila)->heap = NULL;
        }
        free(*fila);
        *fila = NULL;
        return true;
    }
    return false;
}

// Insere paciente de acordo com sua prioridade e seu horário de chegada, mantendo a propriedade de FIFO(para mesma prioridade)
bool fila_prioridade_inserir(FILA_PRIORIDADE *fila, PACIENTE *paciente)
{
    return fila_prioridade_inserir_aux(fila, paciente, time(NULL)); // time(NULL) retorna o horário da inserçao
}

bool fila_prioridade_inserir_aux(FILA_PRIORIDADE *fila, PACIENTE *paciente, time_t timestamp)
{
    if (fila == NULL || paciente == NULL)
        return false;

    if (fila_prioridade_cheia(fila))
    {
        printf("Fila de prioridade cheia!\n");
        return false;
    }

    ELEMENTO_FILA novo;
    novo.paciente = paciente;
    novo.timestamp = timestamp;

    fila->heap[fila->tamanho] = novo;
    fix_up(fila, fila->tamanho);
    fila->tamanho++;

    return true;
}

// remove paciente da fila de prioridade e arruma propriedade de heap max
PACIENTE *fila_prioridade_remover(FILA_PRIORIDADE *fila)
{
    if (fila == NULL || fila_prioridade_vazia(fila))
        return NULL;

    PACIENTE *paciente = fila->heap[0].paciente;

    fila->heap[0] = fila->heap[fila->tamanho - 1];
    fila->tamanho--;

    if (fila->tamanho > 0)
        fix_down(fila, 0);

    return paciente;
}

// retorna tamanho da fila
int fila_prioridade_tamanho(FILA_PRIORIDADE *fila)
{
    if (fila != NULL)
        return fila->tamanho;
    return -1;
}

bool fila_prioridade_vazia(FILA_PRIORIDADE *fila)
{
    if (fila != NULL)
        return fila->tamanho == 0;
    return true;
}

bool fila_prioridade_cheia(FILA_PRIORIDADE *fila)
{
    if (fila != NULL)
        return fila->tamanho >= fila->capacidade;
    return true;
}

void fila_prioridade_imprimir(FILA_PRIORIDADE *fila)
{
    if (fila == NULL || fila_prioridade_vazia(fila))
    {
        printf("\nFila de atendimento vazia.\n\n");
        return;
    }

    printf("\n--- FILA DE ATENDIMENTO (Ordenada por Prioridade) ---\n\n");

    // cria vetor temporário para ordenar por prioridade e timestamp
    ELEMENTO_FILA *temp = (ELEMENTO_FILA *)malloc(sizeof(ELEMENTO_FILA) * fila->tamanho);
    if (temp != NULL)
    {
        // copia a heap principal para o vetor auxiliar
        memcpy(temp, fila->heap, sizeof(ELEMENTO_FILA) * fila->tamanho);

        // Ordena por prioridade e timestamp usando merge sort
        merge_sort(temp, fila->tamanho);

        printf("%-12s %-35s %-10s\n", "Prioridade", "Nome Paciente", "ID");
        printf("%-12s %-35s %-10s\n", "-----------", "------------------", "-----");

        // imprime os elementos no vetor auxiliar
        for (int i = 0; i < fila->tamanho; i++)
        {
            int prio = paciente_get_prioridade(temp[i].paciente);
            printf("%-12d %-35s %-10d\n", prio, paciente_get_nome(temp[i].paciente), paciente_get_id(temp[i].paciente));
        }

        printf("\nTotal aguardando: %d paciente(s)\n\n", fila->tamanho);
        free(temp);
    }
}

// busca um paciente, se encontrar retorna ele, se não retorna NULL
PACIENTE *fila_prioridade_buscar_paciente(FILA_PRIORIDADE *fila, int id_paciente)
{
    if (fila == NULL)
        return NULL;

    for (int i = 0; i < fila->tamanho; i++)
    {
        if (paciente_get_id(fila->heap[i].paciente) == id_paciente)
            return fila->heap[i].paciente;
    }
    return NULL;
}

// funçao auxiliar para a persistência de dados
// aloca um vetor de FILA_ITEM e copia os elementos da heap
// retorna o ponteiro para o vetor, que é utilizado no TAD IO para salvar os elementos
FILA_ITEM **fila_prioridade_listar(FILA_PRIORIDADE *fila, int *outCount)
{
    if (outCount)
        *outCount = 0;
    if (fila == NULL || fila->tamanho == 0)
        return NULL;
    FILA_ITEM **items = (FILA_ITEM **)malloc(sizeof(FILA_ITEM *) * fila->tamanho);
    if (items == NULL)
        return NULL;
    for (int i = 0; i < fila->tamanho; i++)
    {
        FILA_ITEM *it = (FILA_ITEM *)malloc(sizeof(struct fila_item_));
        if (it == NULL)
        {
            // free any previously allocated and return NULL
            for (int j = 0; j < i; ++j)
                free(items[j]);
            free(items);
            return NULL;
        }
        it->paciente = fila->heap[i].paciente;
        it->timestamp = fila->heap[i].timestamp;
        items[i] = it;
    }
    if (outCount)
        *outCount = fila->tamanho;
    return items;
}

// Libera o array retornado por fila_prioridade_listar
bool fila_prioridade_liberar_lista(FILA_ITEM **lista, int count)
{
    if (lista != NULL)
    {
        for (int i = 0; i < count; ++i)
        {
            if (lista[i])
                free(lista[i]);
        }
        free(lista);
        return true;
    }
    return false;
}

//acessam dados internos de FILA_ITEM
PACIENTE *fila_item_get_paciente(const FILA_ITEM *item)
{
    if (!item)
        return NULL;
    return item->paciente;
}

time_t fila_item_get_timestamp(const FILA_ITEM *item)
{
    if (!item)
        return (time_t)0;
    return item->timestamp;
}
