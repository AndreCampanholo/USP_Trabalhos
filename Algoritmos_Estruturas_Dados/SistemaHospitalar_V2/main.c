#include <stdio.h>
#include <stdlib.h>
#include "Arvore_Binaria/arvore.h"
#include "Fila_Prioridade/fila_prioridade.h"
#include "TAD_functions/functions.h"
#include "TAD_IO/IO.h"

int main()
{
    ARVORE *arvore = arvore_criar();                    // armazenamento geral de pacientes (AVL)
    FILA_PRIORIDADE *fila = fila_prioridade_criar(100); // fila de atendimento por prioridade
    int operacao;

    // carrega os dados salvos do sistema
    if (!LOAD(&arvore, &fila))
    {
        printf("[Aviso] Não foi possível carregar dados anteriores. Iniciando sistema limpo.\n");
    }

    printf("Serviço de Atendimento Médico\n");
    printf("-------------------------------------------------\n");

    // laço de seleção de operação
    do
    {
        imprimir_escolha_operacao();
        printf("Escolha: ");
        if (scanf("%d", &operacao) != 1)
        {
            printf("Entrada inválida.\n");
            while (getchar() != '\n')
                ; // limpa o buffer
            continue;
        }
        printf("\n");
        switch (operacao)
        {
        case 1:
            registrar_paciente(arvore, fila);
            break;
        case 2:
            registrar_obito(arvore, fila);
            break;
        case 3:
            adicionar_procedimento(arvore);
            break;
        case 4:
            desfazer_procedimento(arvore);
            break;
        case 5:
            chamar_paciente(fila);
            break;
        case 6:
            mostrar_fila(fila);
            break;
        case 7:
            mostrar_historico(arvore);
            break;
        case 8:
            arvore_imprimir_em_ordem(arvore);
            break;
        case 9:
            printf("Encerrando serviço de atendimento médico.\n");
            break;
        // FUNCIONALIDADE ESPECIAL: Reset do banco de dados
        // Entrada: 471728 (código especial)
        // Função: Limpa toda a árvore e fila, resetando o sistema para estado vazio
        // Uso: Digite 471728 no menu de operações para resetar o sistema
        case 471728:
            if (arvore)
            {
                arvore_apagar(&arvore);
            }
            if (fila)
            {
                fila_prioridade_apagar(&fila);
            }

            arvore = arvore_criar();
            fila = fila_prioridade_criar(100);

            salvar_pacientes(arvore, fila);

            printf("Base de Dados Apagada - Sistema Resetado\n");
            printf("Estado vazio salvo com sucesso.\n\n");
            break;
        default:
            printf("Digite uma operação válida.\n");
            break;
        }
    } while (operacao != 9);

    // salvamento dos dados antes da saída do programa
    salvar_pacientes(arvore, fila);

    // apaga a lista e fila para evitar memmory leak
    if (arvore != NULL)
    {
        arvore_apagar(&arvore);
    }
    if (fila != NULL)
    {
        fila_prioridade_apagar(&fila);
    }

    return 0;
}