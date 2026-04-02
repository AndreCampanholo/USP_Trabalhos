#include <stdio.h>
#include <stdlib.h>

//struct item que guarda o valor e peso de cada item
typedef struct item {
    int valor;
    int peso;
} ITEM;

//passa como parametros o vetor de itens, um vetor dos itens selecionados a cada recursão, o número de itens, a capacidade, o contador i,
//um vetor que retorna os itens da melhor solução e um ponteiro para o melhor valor que é atualizado a cada caso base e passado por referência na próxima recursão 
int brute_force(ITEM *itens, ITEM *selecionados, int n, int W, int i, int *melhor_selecao, int *melhor_valor) {
    //a cada chamada recursiva i é incrementado em 1, logo o caso base é quando i atinge o valor n que já não é um índice válido do vetor de itens ou selecionados
    if(i >= n) {
        int peso = 0, valor = 0;

        //soma o peso e o valor dos itens selecionados para esta recursão
        for(int j = 0; j < n; j++) {
            peso += selecionados[j].peso;
            valor += selecionados[j].valor;
        }

        //atualiza o maior global - verifica se o peso é menor que a capacidade e se a soma dos valores é maior que o maior valor, substituindo-o caso sim
        if(peso <= W && valor > *melhor_valor) {
            *melhor_valor = valor;

            //como esta é a melhor solução até o momento, insere os itens selecionados para esta recursão no vetor melhor solução
            for(int j = 0; j < n; j++) {
                //verifica se o valor dos itens selecionados são zero pois a cada recursão os itens não selecionados tem seu peso e valor zerados
                if(selecionados[j].valor > 0) {
                    //vetor da melhor solução recebe 1 para indicar que o item j foi selecionado
                    melhor_selecao[j] = 1;
                } else {
                    //caso o elemento não tenha sido selecionado o item não é adicionado ao vetor
                    melhor_selecao[j] = 0;
                }
            }
        }

        //atualiza o maior local - verifica se o peso é menor que a capacidade e retorna
        if(peso <= W) {
            return valor;
        }
        return 0;
    } 
    
    //chamada da função para o caso em que o item do indice i não é selecionado
    int n_seleciona = brute_force(itens, selecionados, n, W, i + 1, melhor_selecao, melhor_valor);
    
    //seleciona o item da posição i e chama a função para este caso
    selecionados[i] = itens[i];
    int seleciona = brute_force(itens, selecionados, n, W, i + 1, melhor_selecao, melhor_valor);
    
    //após um ciclo de recursão zera o vetor de selecionados para não influenciar futuras recursões
    selecionados[i].peso = 0;
    selecionados[i].valor = 0;

    //verifica qual a melhor solução para cada recursão (a que inclui ou não o elemento i) e retorna-o, retornando, ao final, a melhor solução
    if(seleciona > n_seleciona)
        return seleciona;

    return n_seleciona;
}

int main() {
    //leitura dos dados de entrada
    int n, W, i = 0;
    scanf("%d", &n);

    //alocação de memória para o vetor de itens e o vetor de itens selecionados que será usado na função recursiva para o número de itens informado na entrada
    ITEM *item = (ITEM *)malloc(n * sizeof(ITEM));
    ITEM *selecionados = (ITEM *)malloc(n * sizeof(ITEM));

    //alocação do vetor dos itens selecionados na melhor solução como um vetor de inteiros (se a posição x == 0 o item não está na melhor solução, caso contrário, está)
    int *melhor_selecao = (int *)calloc(n, sizeof(int));
    //inicializa o melhor valor com zero
    int melhor_valor = 0;
    
    //zera todos os pesos e valores do vetor de selecionados (receberão seus valores reais caso selecionados dentro da função recursiva)
    for(int i = 0; i < n; i++) {
        selecionados[i].peso = 0;
        selecionados[i].valor = 0;
    }

    //leitura dos dados de entrada  
    while(i < n) {
        scanf("%d %d", &item[i].valor, &item[i].peso);
        i++;
    }

    scanf("%d", &W);

    //chamada da função recursiva
    brute_force(item, selecionados, n, W, 0, melhor_selecao, &melhor_valor);

    //impressão do melhor valor e dos itens como índices (item[0] = 0, item[1] = 1...)
    printf("Valor: %d\n", melhor_valor);
    printf("Itens: ");
    for(int i = 0; i < n; i++) {
        if(melhor_selecao[i]) {
            printf("%d ", i); //imprime o índice dos itens escolhidos
        }
    }
    printf("\n");

    //desalocação de memória
    free(item);
    free(selecionados);
    free(melhor_selecao);

    return 0;
}