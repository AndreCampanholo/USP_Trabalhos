#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "../TAD_IO/IO.h"

// função que exibe o menu principal de operações disponíveis ao usuário.
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

// registra um novo paciente
void registrar_paciente(ARVORE *arvore, FILA_PRIORIDADE *fila)
{
   if (fila_prioridade_cheia(fila))
   {
      // imprime mensagem de erro caso a fila de espera já esteja cheia
      printf("Não é possível registrar paciente, pois a fila de espera está cheia.\n");
      return;
   }

   int id;
   printf("Digite o ID do paciente: ");
   scanf("%d", &id);
   getchar();

   // verifica pelo id informado se o paciente já existe
   if (arvore_buscar(arvore, id) != NULL)
   {
      // caso já exista um paciente com este id e ele já está na fila de espera, imprime mensagem de erro
      if (fila_prioridade_buscar_paciente(fila, id) != NULL)
      {
         printf("Já existe um paciente com esse ID e este já está na fila.\n\n");
         return;
      }
      // caso já exista paciente com este id porém ele não está na fila de espera,
      // reinsere-o na fila solicitando a prioridade novamente
      PACIENTE *paciente_existente = arvore_buscar(arvore, id);
      int prioridade;
      printf("Paciente já cadastrado. Selecione a prioridade novamente.\n");
      printf("\nNível de Prioridade de Atendimento:\n");
      printf("  1. Emergência - Risco imediato de vida\n");
      printf("  2. Muito Urgente - Risco potencial de morte\n");
      printf("  3. Urgente - Gravidade moderada\n");
      printf("  4. Não urgente - Pode aguardar atendimento\n");
      printf("  5. Consulta - Sem risco à saúde\n");
      printf("Digite a prioridade: ");
      if (scanf("%d", &prioridade) != 1)
      {
         printf("Entrada inválida de prioridade.\n\n");
         while (getchar() != '\n');
         return;
      }
      if (prioridade < 1 || prioridade > 5)
      {
         printf("Prioridade deve estar entre 1 e 5.\n\n");
         return;
      }
      paciente_set_prioridade(paciente_existente, prioridade);
      printf("Reinserindo paciente na fila com nova prioridade.\n\n");
      fila_prioridade_inserir(fila, paciente_existente);
      return;
   } //se não existe paciente com este id: 

   char nome[100];
   printf("Digite o nome do paciente: ");
   fgets(nome, 99, stdin);
   nome[strcspn(nome, "\n")] = '\0';

   int prioridade;
   printf("\nNível de Prioridade de Atendimento:\n");
   printf("  1. Emergência - Risco imediato de vida\n");
   printf("  2. Muito Urgente - Risco potencial de morte\n");
   printf("  3. Urgente - Gravidade moderada\n");
   printf("  4. Não urgente - Pode aguardar atendimento\n");
   printf("  5. Consulta - Sem risco à saúde\n");
   printf("Digite a prioridade: ");
   if (scanf("%d", &prioridade) != 1)
   {
      printf("Entrada inválida de prioridade.\n\n");
      while (getchar() != '\n')
         ;
      return;
   }
   if (prioridade < 1 || prioridade > 5)
   {
      printf("Prioridade deve estar entre 1 e 5.\n\n");
      return;
   }

   PACIENTE *paciente = paciente_criar(id, nome);
   if (paciente != NULL)
   {
      paciente_set_prioridade(paciente, prioridade);
      // caso não exista paciente com este id insere-o na lista de pacientes e na fila de espera
      arvore_inserir(arvore, paciente);
      fila_prioridade_inserir(fila, paciente);
      printf("Paciente registrado com sucesso!\n\n");
   }
   else
   {
      //caso dê erro ao criar o paciente, exibe mensagem de erro
      printf("Erro ao registrar paciente.\n\n");
   }
}

// registra o obito do paciente, ou seja, retira-o do banco de dados do sistema
void registrar_obito(ARVORE *arvore, FILA_PRIORIDADE *fila)
{
   int id;
   printf("Digite o ID do paciente: ");
   scanf("%d", &id);
   PACIENTE *paciente = arvore_buscar(arvore, id);
   if (paciente != NULL)
   {
      if ((fila_prioridade_buscar_paciente(fila, id)) == NULL)
      {
         // se o paciente for encontrado na lista de pacientes e não for encontrado na fila de espera, remove-o da lista e apaga-o
         printf("Óbito de %s registrado com sucesso, paciente removido da base de dados.\n\n", paciente_get_nome(paciente));
         paciente = arvore_remover(arvore, id);
         if (paciente != NULL)
            paciente_apagar(&paciente);
         return;
      }
      // se o paciente existir porém ainda estiver na fila de espera, não permite seu óbito
      printf("Registro de óbito inválido, paciente está na fila de espera.\n\n");
      return;
   }
   // se o paciente não for encontrado imprime mensagem de erro
   printf("Paciente inexistente!\n\n");
}

// desfaz o último procedimento do histórico do paciente
void desfazer_procedimento(ARVORE *arvore)
{
   int id;
   char procedimento[100];
   printf("Digite o ID do paciente: ");
   scanf("%d", &id);
   PACIENTE *paciente = arvore_buscar(arvore, id);
   if (paciente == NULL)
   {
      // imprime mensagem de erro caso o paciente não seja encontrado
      printf("Paciente não encontrado!\n\n");
      return;
   }
   // caso contrário, desempilha o útlimo procedimento do paciente
   if (pilha_desempilhar(paciente_get_historico(paciente), procedimento))
   {
      printf("Procedimento '%s' desfeito para paciente %d.\n\n", procedimento, id);
   }
   else
   {
      // caso a pilha de procedimentos do paciente estja vazia imprime mensagem de erro
      printf("Histórico vazio, nada a desfazer.\n\n");
   }
}

// adiciona procedimento ao histórico médico do paciente
void adicionar_procedimento(ARVORE *arvore)
{
   int id;
   char procedimento[100];
   printf("Digite o ID do paciente: ");
   scanf("%d", &id);
   PACIENTE *paciente = arvore_buscar(arvore, id);
   if (paciente == NULL)
   {
      // se o paciente não for encontrado na busca imprime mensagem de erro
      printf("Paciente não encontrado!\n\n");
      return;
   }
   getchar();
   printf("Digite o procedimento: ");
   fgets(procedimento, 99, stdin);
   procedimento[strcspn(procedimento, "\n")] = '\0';
   if (pilha_cheia(paciente_get_historico(paciente)))
   {
      // caso o paciente tenha atingido o máximo de procedimentos no histórico (10) imprime mensagem de aviso
      printf("Não é possível adicionar procedimento ao histórico do paciente %d pois este já atingiu a quantidade máxima de procedimentos.\n", id);
      return;
   }
   // caso contrário, adiciona procedimento ao histórico do paciente
   pilha_empilhar(paciente_get_historico(paciente), procedimento);
   printf("Procedimento '%s' adicionado ao histórico do paciente %d.\n\n", procedimento, id);
}

// chama o paciente para atendimento, retirando-o da fila de espera
void chamar_paciente(FILA_PRIORIDADE *fila)
{
   PACIENTE *paciente = fila_prioridade_remover(fila);
   if (paciente != NULL)
   {
      // se o paciente for encontrado, retira-o da fila de espera
      printf("Chamando paciente %d para atendimento.\n\n", paciente_get_id(paciente));
   }
   else
   {
      // caso contrário, exibe mensagem de erro
      printf("Nenhum paciente na fila de espera.\n\n");
   }
}

// imprime todos os pacientes na fila de espera
void mostrar_fila(FILA_PRIORIDADE *fila)
{
   if (fila_prioridade_vazia(fila))
   {
      // avisa que a fila está vazia caso esteja
      printf("A fila está vazia!\n");
      return;
   }

   // caso contrário, imprime todos os pacientes da fila
   printf("Fila de espera:\n");
   fila_prioridade_imprimir(fila);
}

// imprime o histórico médico do paciente
void mostrar_historico(ARVORE *arvore)
{
   int id;
   printf("Digite o ID do paciente: ");
   scanf("%d", &id);
   PACIENTE *paciente = arvore_buscar(arvore, id);
   if (paciente == NULL)
   {
      // se o paciente não existir imprime mensagem de erro
      printf("Paciente não encontrado!\n\n");
      return;
   }

   // caso contrário, imprime o histórico
   printf("Histórico Médico de %s:\n", paciente_get_nome(paciente));
   pilha_imprimir(paciente_get_historico(paciente));
}

// chama a função que salva a lista dos pacientes e a fila de espera, garantindo a persistência dos dados
void salvar_pacientes(ARVORE *arvore, FILA_PRIORIDADE *fila)
{
   if (SAVE(arvore, fila))
      printf("Dados salvos com sucesso!\n\n");
   else
      printf("Erro ao salvar os dados!\n\n");
}
