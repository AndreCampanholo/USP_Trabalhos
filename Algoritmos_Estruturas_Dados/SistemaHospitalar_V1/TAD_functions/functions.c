#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "../TAD_Paciente/paciente.h"
#include "../Pilha_Encadeada/pilha.h"
#include "../Fila_Encadeada/fila.h"
#include "../TAD_IO/IO.h"

//função que exibe o menu principal de operações disponíveis ao usuário.
void imprimir_escolha_operacao(void)
{
    printf("\nOperação desejada:\n");
    printf("1 - Registrar paciente.\n");
    printf("2 - Registar óbito de paciente.\n");
    printf("3 - Adicionar procedimento ao histórico médico.\n");
    printf("4 - Desfazer procedimento do histórico médico.\n");
    printf("5 - Chamar paciente para atendimento.\n");
    printf("6 - Mostrar fila de espera.\n");
    printf("7 - Mostrar histórico do paciente.\n");
    printf("8 - Mostrar lista de pacientes.\n");
    printf("9 - Sair.\n");
    return;
}

//registra um novo paciente
void registrar_paciente(LISTA *lista, FILA *fila)
{
    if (fila_cheia(fila))
    {
        //imprime mensagem de erro caso a fila de espera já esteja cheia
        printf("Não é possível registrar paciente, pois a fila de espera está cheia.\n");
        return;
    }

    int id;
    printf("Digite o ID do paciente: ");
    scanf("%d", &id);
    getchar();
    
    //verifica pelo id informado se o paciente já existe
    if(lista_busca(lista, id) != NULL)
    {
        //caso já exista um paciente com este id e ele já está na fila de espera, imprime mensagem de erro
        if(fila_busca(fila, id) != NULL) {
            printf("Já existe um paciente com esse ID e este já está na fila.\n\n");
            return;
        }
        //caso já exista paciente com este id porém ele não está na fila de espera, reinsere-o na fila
        printf("Já existe um paciente com esse ID... reinserindo-o na fila de espera.\n\n");
        fila_inserir_paciente(fila, lista_busca(lista, id));
        return;
    }

    char nome[100];
    printf("Digite o nome do paciente: ");
    fgets(nome, 99, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    PACIENTE *paciente = paciente_criar(id, nome);
    if (paciente != NULL)
    {
        //caso não exista paciente com este id insere-o na lista de pacientes e na fila de espera
        lista_inserir(lista, paciente);
        fila_inserir_paciente(fila, paciente);
        printf("Paciente registrado com sucesso!\n\n");
    }
    else
    {
        printf("Erro ao registrar paciente.\n\n");
    }
}

//registra o obito do paciente, ou seja, retira-o do banco de dados do sistema
void registrar_obito(LISTA *lista, FILA *fila)
{
    int id;
    printf("Digite o ID do paciente: ");
    scanf("%d", &id);
    PACIENTE *paciente = lista_busca(lista, id);
    if (paciente != NULL)
    {
        if ((fila_busca(fila, id)) == NULL)
        {
            //se o paciente for encontrado na lista de pacientes e não for encontrado na fila de espera, remove-o da lista e apaga-o
            printf("Óbito de %s registrado com sucesso, paciente removido da base de dados.\n\n", paciente_get_nome(paciente));
            paciente = lista_remover(lista, id);
            if (paciente != NULL) {
                paciente_apagar(&paciente);
            }
            return;
        }
        //se o paciente existir porém ainda estiver na fila de espera, não permite seu óbito
        printf("Registro de óbito inválido, paciente está na fila de espera.\n\n");
        return;
    }
    //se o paciente não for encontrado imprime mensagem de erro
    printf("Paciente inexistente!\n\n");
}

//desfaz o último procedimento do histórico do paciente
void desfazer_procedimento(LISTA *lista)
{
    int id;
    char procedimento[100];
    printf("Digite o ID do paciente: ");
    scanf("%d", &id);
    PACIENTE *paciente = lista_busca(lista, id);
    if(paciente == NULL)
    {
        //imprime mensagem de erro caso o paciente não seja encontrado
        printf("Paciente não encontrado!\n\n");
        return;
    }
    //caso contrário, desempilha o útlimo procedimento do paciente
    if(pilha_desempilhar(paciente_get_historico(paciente), procedimento))
    {
        printf("Procedimento '%s' desfeito para paciente %d.\n\n", procedimento, id);
    }
    else
    {
        //caso a pilha de procedimentos do paciente estja vazia imprime mensagem de erro
        printf("Histórico vazio, nada a desfazer.\n\n");
    }
}

//adiciona procedimento ao histórico médico do paciente
void adicionar_procedimento(LISTA *lista)
{
    int id;
    char procedimento[100];
    printf("Digite o ID do paciente: ");
    scanf("%d", &id);
    getchar();
    printf("Digite o procedimento: ");
    fgets(procedimento, 99, stdin);
    procedimento[strcspn(procedimento, "\n")] = '\0';
    PACIENTE *paciente = lista_busca(lista, id);
    
    if (paciente == NULL)
    {
        //se o paciente não for encontrado na busca imprime mensagem de erro
        printf("Paciente não encontrado!\n\n");
        return;
    }
    if (pilha_cheia(paciente_get_historico(paciente)))
    {
        //caso o paciente tenha atingido o máximo de procedimentos no histórico imprime mensagem de aviso
        printf("Não é possível adicionar procedimento ao histórico do paciente %d pois este já atingiu a quantidade máxima de procedimentos.\n", id);
        return;
    }
    //caso contrário, adiciona procedimento ao histórico do paciente
    pilha_empilhar(paciente_get_historico(paciente), procedimento);
    printf("Procedimento '%s' adicionado ao histórico do paciente %d.\n\n", procedimento, id);
}

//chama o paciente para atendimento, retirand-o da fila de espera
void chamar_paciente(FILA *fila)
{
    PACIENTE *paciente = fila_remover_paciente(fila);
    if (paciente != NULL)
    {
        //se o paciente for encontrado, retira-o da fila de espera
        printf("Chamando paciente %d para atendimento.\n\n", paciente_get_id(paciente));
    }
    else
    {
        //caso contrário, exibe mensagem de erro
        printf("Nenhum paciente na fila de espera.\n\n");
    }
}

//imprime todos os pacientes na fila de espera
void mostrar_fila(FILA *fila)
{
    if (fila_vazia(fila))
    {
        //avisa que a fila está vazia caso esteja
        printf("A fila está vazia!\n");
        return;
    }

    //caso contrário, imprime todos os pacientes da fila
    printf("Fila de espera:\n");
    fila_imprimir(fila);
}

//imprime o histórico médico do paciente
void mostrar_historico(LISTA *lista)
{
    int id;
    printf("Digite o ID do paciente: ");
    scanf("%d", &id);
    PACIENTE *paciente = lista_busca(lista, id);
    if (paciente == NULL)
    {
        //se o paciente não existir imprime mensagem de erro
        printf("Paciente não encontrado!\n\n");
        return;
    }

    //caso contrário, imprime o histórico
    printf("Histórico Médico de %s:\n", paciente_get_nome(paciente));
    pilha_imprimir(paciente_get_historico(paciente));
}

//chama a função que salva a lista dos pacientes e a fila de espera, garantindo a persistência dos dados
void salvar_pacientes(LISTA *lista, FILA *fila)
{
    if(SAVE(lista, fila))
        printf("Dados salvos com sucesso!\n\n");
    else
        printf("Erro ao salvar os dados!\n\n");
}