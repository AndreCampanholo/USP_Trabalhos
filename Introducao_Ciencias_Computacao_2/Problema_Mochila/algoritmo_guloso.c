#include <stdio.h>
#include <stdlib.h>

//struct item que guarda o valor e peso de cada item e o seu índice original
typedef struct item {
    int valor;
    int peso;
    //usado para determinação dos itens escolhidos
    int indice_original;
} ITEM;

//passa como parâmetros o vetor de itens, o vetor dos itens selecionados, o numero de itens, a capacidade maxima e um contador
int algoritmo_guloso(ITEM *itens, ITEM *selecionados, int n, int W, int cont) {
    //caso base: quando o número de elementos no vetor de itens zera calcula o valor total dos itens selecionados e retorna
    if(n == 0) {
        int valor_total = 0;
        for(int i = 0; i < cont - 1; i++) {
            valor_total += selecionados[i].valor;
        }
        return valor_total;
    }

    //inicializa a melhor razao como zero pois procura-se o maior entre todas as razoes valor/peso
    float melhor_razao = 0;
    //inicializa o indice do melhor item como -1 pois se trata de um índice inválido, logo, caso não seja encontrado nenhum item selecionável
    //saberemos que indice_melhor = -1, logo nenhum item deve ser selecionado 
    int indice_melhor = -1;

    //laço que calcula a razao de todos os itens e atualiza a melhor razão a cada loop, além de atualizar o índice do melhor
    for(int i = 0; i < n; i++) {
        //verifica se peso é válido
        if(itens[i].peso > 0) {
            //casting do valor para float
            float razao = (float)itens[i].valor / itens[i].peso;
        
            if(razao > melhor_razao) {
                melhor_razao = razao;
                indice_melhor = i;
            }
            //se as razões são iguais, escolhe o item com maior valor
            else if(razao == melhor_razao && indice_melhor != -1) {
                if(itens[i].valor > itens[indice_melhor].valor) {
                    indice_melhor = i;
                }
                //se os valores também são iguais, escolhe o com menor peso
                else if(itens[i].valor == itens[indice_melhor].valor && itens[i].peso < itens[indice_melhor].peso) {
                    indice_melhor = i;
                }
            }
        }
    }

    //cálculo do peso atual da mochila
    int peso_atual = 0;
    for(int i = 0; i < cont - 1; i++) {
        peso_atual += selecionados[i].peso;
    }

    //verifica se algum item foi selecionado e se o peso dos itens selecionados está dentra da capacidade limite
    if(indice_melhor != -1 && peso_atual + itens[indice_melhor].peso <= W) {
        //insere o índice do melhor item no vetor dos itens selecionados, do índice zero para cima (cont incrementa a cada recursão)
        selecionados[cont - 1] = itens[indice_melhor];
        
        //joga o item do melhor índice para o final do vetor e o item do final do vetor para a posição em que o melhor item estava
        ITEM temp = itens[indice_melhor];
        itens[indice_melhor] = itens[n-1];
        itens[n-1] = temp;
        
        //chama a função recursivamente para o vetor de itens excluindo o último item (onde agora está o melhor item) e incrementando cont
        return algoritmo_guloso(itens, selecionados, n - 1, W, cont + 1);

    } else {
        //caso nenhum item tenha sido selecionado nesta recursão (tenham valor zero) 
        //ou o peso do item com a melhor razão somado aos itens selecionados 
        //seja maior que a capacidade, encerra a seleção de itens e calcula o valor total
        int valor_total = 0;
        for(int i = 0; i < cont - 1; i++) {
            valor_total += selecionados[i].valor;
        }
        
        //encerra a recursão e retorna o valor total
        return valor_total;
    }
}

int main() {
    //leitura dos dados de entrada
    int n, W, i = 0;
    scanf("%d", &n);

    //alocação de memória para o vetor de itens e o vetor de itens selecionados que será usado na função recursiva para o número de itens informado na entrada
    ITEM *itens = (ITEM *)malloc(n * sizeof(ITEM));
    ITEM *selecionados = (ITEM *)calloc(n, sizeof(ITEM));

    //leitura dos dados de entrada  
    while(i < n) {
        scanf("%d %d", &itens[i].valor, &itens[i].peso);
        //guarda o índice original de cada item
        itens[i].indice_original = i;
        i++;
    }

    scanf("%d", &W);
    
	//impressão do maior valor e dos itens selecionados por ordem de escolha
    printf("Valor: %d\n", algoritmo_guloso(itens, selecionados, n, W, 1));
    printf("Itens: ");
    for(int i = 0; i < n; i++) {
        if(selecionados[i].valor > 0) {
            //imprime os itens do vetor de selecionados com base nos índices originais, para assim mostrar a ordem pela qual os itens foram selecionados
            printf("%d ", selecionados[i].indice_original);
        }
    }
    printf("\n");

    //desalocação de memória
    free(itens);
    free(selecionados);

    return 0;
}