#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b, long long *num_swaps)
{
    int temp = *a;
    *a = *b;
    *b = temp;
    (*num_swaps)++;
}

void bubblesort(int v[], int n, long long *num_comps, long long *num_swaps)
{
    for (int i = 0; i < n - 1; i++)
    {
        int swapou = 0;
        for (int j = 0; j < n - i - 1; j++)
        {
            (*num_comps)++;
            if (v[j] > v[j + 1])
            {
                swap(&v[j], &v[j + 1], num_swaps);
                swapou = 1;
            }
        }
        if (!swapou)
            return;
    }
    return;
}

void selectionsort(int v[], int n, long long *num_comps, long long *num_swaps)
{
    for (int i = 0; i < n - 1; i++)
    {
        int menor = i;
        for (int j = i + 1; j < n; j++)
        {
            (*num_comps)++;
            if (v[menor] > v[j])
            {
                menor = j;
            }
        }
        if (menor != i)
        {
            swap(&v[i], &v[menor], num_swaps);
        }
    }
}

void insertionsort(int v[], int n, long long *num_comps, long long *num_swaps)
{
    int i, j;
    for (i = 1; i < n; i++)
    {
        int elem = v[i];
        for (j = i - 1; j >= 0; j--)
        {
            (*num_comps)++;
            if (elem < v[j])
            {
                v[j + 1] = v[j];
                (*num_swaps)++;
            }
            else
            {
                break;
            }
        }
        v[j + 1] = elem;
        (*num_swaps)++;
    }
}

void shellsort(int v[], int n, long long *num_comps, long long *num_swaps, int incrementos[], int qtd_incrementos)
{
    int i, j, k;
    for (k = 0; k < qtd_incrementos; k++)
    {
        int h = incrementos[k];
        for (i = h; i < n; i++)
        {
            int elem = v[i];
            for (j = i - h; j >= 0; j -= h)
            {
                (*num_comps)++;
                if (elem < v[j])
                {
                    v[j + h] = v[j];
                    (*num_swaps)++;
                }
                else
                {
                    break;
                }
            }
            v[j + h] = elem;
            (*num_swaps)++;
        }
    }
}

void quicksort(int v[], long long *num_comps, long long *num_swaps, int ini, int fim)
{
    if (ini >= fim)
        return;

    int i = ini, j = fim, meio = (ini + fim) / 2, pivo;

    int aux[] = {v[ini], v[meio], v[fim]};
    insertionsort(aux, 3, num_comps, num_swaps);
    pivo = aux[1];

    while (i <= j)
    {
        while (v[i] < pivo)
        {
            (*num_comps)++;
            i++;
        }
        (*num_comps)++;

        while (v[j] > pivo)
        {
            (*num_comps)++;
            j--;
        }
        (*num_comps)++;

        if (i <= j)
        {
            if (i < j)
            {
                swap(&v[i], &v[j], num_swaps);
            }
            i++;
            j--;
        }
    }

    if (ini < j)
        quicksort(v, num_comps, num_swaps, ini, j);
    if (i < fim)
        quicksort(v, num_comps, num_swaps, i, fim);
}

void heapify(int v[], int n, int index, long long *num_comps, long long *num_swaps)
{
    int maior = index, esq = 2 * index + 1, dir = 2 * index + 2;

    if (esq < n) {
        (*num_comps)++;
        if (v[esq] > v[maior])
            maior = esq;
    }

    if (dir < n) {
        (*num_comps)++;
        if (v[dir] > v[maior])
            maior = dir;
    }

    if (maior != index)
    {
        swap(&v[maior], &v[index], num_swaps);
        heapify(v, n, maior, num_comps, num_swaps);
    }
}

void heapsort(int v[], int n, long long *num_comps, long long *num_swaps)
{
    if (n <= 1)
        return;

    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(v, n, i, num_comps, num_swaps);
    }

    for (int i = n - 1; i > 0; i--)
    {
        swap(&v[0], &v[i], num_swaps);
        heapify(v, i, 0, num_comps, num_swaps);
    }
}

void merge(int v[], int ini, int meio, int fim, long long *num_comps, long long *num_swaps)
{
    int n1 = meio - ini + 1, n2 = fim - meio;
    int esq[n1], dir[n2];

    for (int i = 0; i < n1; i++)
    {
        esq[i] = v[ini + i];
    }

    for (int i = 0; i < n2; i++)
    {
        dir[i] = v[meio + 1 + i];
    }

    int i = 0, j = 0, k = ini;
    while (i < n1 && j < n2)
    {
        (*num_comps)++;
        if (esq[i] <= dir[j])
        {
            v[k++] = esq[i++];
        }
        else
        {
            v[k++] = dir[j++];
        }
        (*num_swaps)++;
    }

    while (i < n1)
    {
        v[k++] = esq[i++];
        (*num_swaps)++;
    }
    while (j < n2)
    {
        v[k++] = dir[j++];
        (*num_swaps)++;
    }
}

void mergesort(int v[], int ini, int fim, long long *num_comps, long long *num_swaps)
{
    if (ini < fim)
    {
        int meio = (ini + fim) / 2;
        mergesort(v, ini, meio, num_comps, num_swaps);
        mergesort(v, meio + 1, fim, num_comps, num_swaps);
        merge(v, ini, meio, fim, num_comps, num_swaps);
    }
}

void ranksort(int v[], int n, long long *num_comps, long long *num_swaps)
{
    int aux[n], sorted[n];

    for (int i = 0; i < n; i++)
    {
        aux[i] = 0;
        sorted[i] = 0;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            (*num_comps)++;
            if (v[j] <= v[i] && i != j)
            {
                aux[i]++;
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (sorted[aux[i]] == 0)
        {
            sorted[aux[i]] = v[i];
            (*num_swaps)++;
        }
        else
        {
            int k = aux[i] - 1;
            while (sorted[k] != 0)
                k--;
            sorted[k] = v[i];
            (*num_swaps)++;
        }
    }

    for (int i = 0; i < n; i++)
    {
        v[i] = sorted[i];
        (*num_swaps)++;
    }
}

void countingSortForRadix(int v[], int n, int exp, long long *num_comps, long long *num_swaps)
{
    int output[n];
    int count[10] = {0};

    for (int i = 0; i < n; i++)
    {
        count[(v[i] / exp) % 10]++;
    }

    for (int i = 1; i < 10; i++)
    {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--)
    {
        output[count[(v[i] / exp) % 10] - 1] = v[i];
        count[(v[i] / exp) % 10]--;
        (*num_swaps)++;
    }

    for (int i = 0; i < n; i++)
    {
        v[i] = output[i];
        (*num_swaps)++;
    }
}

void radixsort(int v[], int n, long long *num_comps, long long *num_swaps)
{
    if (n <= 0)
        return;

    int max = v[0];
    for (int i = 1; i < n; i++) {
        (*num_comps)++;
        if (v[i] > max)
        {
            max = v[i];
        }
    }

    for (int exp = 1; max / exp > 0; exp *= 10)
    {
        countingSortForRadix(v, n, exp, num_comps, num_swaps);
    }
}

void imprimir_prompt(int *n, int *metodo, int *config_inicial)
{
    printf("Informe o tamanho do vetor a ser ordenado: ");
    scanf("%d", n);

    printf("\nEscolha o método de ordenação a ser executado:\n");
    printf("1 - Bubble Sort\n");
    printf("2 - Selection Sort\n");
    printf("3 - Insertion Sort\n");
    printf("4 - Shell Sort\n");
    printf("5 - Quick Sort\n");
    printf("6 - Heap Sort\n");
    printf("7 - Merge Sort\n");
    printf("8 - Contagem de Menores\n");
    printf("9 - Radix Sort\n");
    printf("Escolha: ");
    scanf("%d", metodo);

    printf("\nEscolha a configuração inicial do vetor:\n");
    printf("1 - Aleatório\n");
    printf("2 - Inversamente Ordenado\n");
    printf("3 - Ordenado\n");
    printf("Escolha: ");
    scanf("%d", config_inicial);
}

void gerar_aleatorio(int v[], int n)
{
    for (int i = 0; i < n; i++)
    {
        v[i] = rand() % (7 * n);
    }

    return;
}

void gerar_inversamente(int v[], int n)
{
    for (int i = 0; i < n; i++)
    {
        v[i] = n - i;
    }

    return;
}

void gerar_ordenado(int v[], int n)
{
    for (int i = 0; i < n; i++)
    {
        v[i] = i + 1;
    }

    return;
}

void switch_case_metodo(int v[], int n, int metodo, long long *num_comps, long long *num_swaps)
{
    clock_t ini, fim;

    switch (metodo)
    {
    case 1:
        ini = clock();
        bubblesort(v, n, num_comps, num_swaps);
        fim = clock();

        break;

    case 2:
        ini = clock();
        selectionsort(v, n, num_comps, num_swaps);
        fim = clock();

        break;

    case 3:
        ini = clock();
        insertionsort(v, n, num_comps, num_swaps);
        fim = clock();

        break;

    case 4:
    {
        int incrementos[10], shells = 0;

        ini = clock();
        for (int h = 1; h < n && shells < 10; h = 3 * h + 1)
        {
            incrementos[shells++] = h;
        }

        for (int i = 0; i < shells / 2; i++)
        {
            int temp = incrementos[i];
            incrementos[i] = incrementos[shells - 1 - i];
            incrementos[shells - 1 - i] = temp;
        }

        shellsort(v, n, num_comps, num_swaps, incrementos, shells);
        fim = clock();

        break;
    }
    case 5:
        ini = clock();
        quicksort(v, num_comps, num_swaps, 0, n - 1);
        fim = clock();

        break;

    case 6:
        ini = clock();
        heapsort(v, n, num_comps, num_swaps);
        fim = clock();

        break;

    case 7:
        ini = clock();
        mergesort(v, 0, n - 1, num_comps, num_swaps);
        fim = clock();

        break;

    case 8:
        ini = clock();
        ranksort(v, n, num_comps, num_swaps);
        fim = clock();

        break;
    
    case 9:
        ini = clock();
        radixsort(v, n, num_comps, num_swaps);
        fim = clock();

        break;


    default:
        printf("\nMétodo de Ordenação inválido. Encerrando programa.\n");
        return;
        break;
    }

    // printf("\n");
    // for(int i = 0; i < n; i++) {
    //     printf("%d ", v[i]);
    // }
    // printf("\n");

    double tempo = (double)(fim - ini) / (double)(CLOCKS_PER_SEC);

    printf("\nQuantidade de Comparações de Chaves: %lld\n", *num_comps);
    printf("Quantidade de Movimentações de Registros: %lld\n", *num_swaps);
    printf("Tempo de Execução do Algoritmo: %f\n", tempo);

    *num_comps = 0;
    *num_swaps = 0;
}

int main()
{
    int n, metodo, config_inicial;
    imprimir_prompt(&n, &metodo, &config_inicial);

    int *v = (int *)malloc(n * sizeof(int));

    long long comps = 0, swaps = 0;

    if (config_inicial == 1)
    {
        srand((unsigned)time(NULL));

        int **a = (int **)malloc(5 * sizeof(int *));
        for (int i = 0; i < 5; i++)
        {
            a[i] = (int *)malloc(n * sizeof(int));
            gerar_aleatorio(a[i], n);
        }

        for (int i = 0; i < 5; i++)
        {
            switch_case_metodo(a[i], n, metodo, &comps, &swaps);
        }

        for (int i = 0; i < 5; i++)
        {
            free(a[i]);
        }
        free(a);
    }
    else if (config_inicial == 2)
    {
        gerar_inversamente(v, n);

        switch_case_metodo(v, n, metodo, &comps, &swaps);
    }
    else
    {
        gerar_ordenado(v, n);

        switch_case_metodo(v, n, metodo, &comps, &swaps);
    }

    free(v);

    return 0;
}