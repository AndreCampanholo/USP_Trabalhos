## Sistema Hospitalar AED - Versão 2

Este projeto simula um sistema de atendimento médico de pacientes em um Pronto Socorro (PS), utilizando Tipos Abstratos de Dados (TADs) em C.
Desenvolvido por:
- André Campanholo Paschoalini - 14558061
- Eduardo Poltroniere da Silva - 16862892
- Pedro Hamamoto da Palma - 16818280

## Estrutura
- `main.c` - ponto de entrada e loop do menu.

Diretórios principais / TADs:
- `TAD_Paciente/` - (`paciente.c`, `paciente.h`) cadastro, busca, remoção e gerenciamento de pacientes (id, nome, histórico).
- `Arvore_Binaria/` - (`arvore.c`, `arvore.h`) árvore AVL para armazenar e buscar pacientes de forma eficiente por ID.
- `Fila_Prioridade/` - (`fila_prioridade.c`, `fila_prioridade.h`) fila de prioridade (heap) para triagem de pacientes com base na gravidade dos casos.
- `Pilha_Encadeada/` - (`pilha.c`, `pilha.h`) pilha encadeada para histórico de procedimentos (LIFO) — máximo 10 procedimentos, cada um até 100 caracteres.
- `TAD_functions/` - (`functions.c`, `functions.h`) implementa as operações do menu e a lógica de negócio (registrar, óbito, procedimentos, chamada, etc.).
- `TAD_IO/` - (`IO.c`, `IO.h`) persistência: `SAVE` e `LOAD` para ler/gravar `arvore_pacientes.bin` e `fila_pacientes.bin`.

## Principais funcionalidades e onde estão implementadas
- Registrar paciente: `TAD_functions/registrar_paciente` — cria `PACIENTE`, insere na `Arvore_Binaria`(caso seja primeira visita do paciente) e em `Fila_Prioridade` com base na gravidade.
- Registrar óbito: `TAD_functions/registrar_obito` — só permite apagar paciente se ele NÃO estiver na fila (apenas após ter sido chamado); remove da árvore e apaga o `PACIENTE`.
- Adicionar procedimento: `TAD_functions/adicionar_procedimento` — empilha procedimento no `PILHA` do paciente.
- Desfazer procedimento: `TAD_functions/desfazer_procedimento` — desempilha o último procedimento e informa qual foi removido.
- Chamar paciente: `TAD_functions/chamar_paciente` — remove o paciente de maior prioridade da fila (`fila_prioridade_remover`) e o entrega para atendimento.
- Mostrar fila: `TAD_functions/mostrar_fila` — imprime a fila de espera ordenada por prioridade.
- Mostrar histórico: `TAD_functions/mostrar_historico` — imprime o histórico (pilha) do paciente.
- Mostrar árvore: `TAD_Arvore_Binaria/arvore_imprimir` - imprime a árvore de todos os pacientes.
- Salvar/Carregar: `TAD_IO/SAVE` e `TAD_IO/LOAD` carregam e salvam a árvore e a fila de pacientes ao iniciar e ao fechar o programa (`main.c`) respectivamente.

## Persistência
- Ao sair (opção de menu), o programa chama `SAVE(arvore, fila)` e grava `arvore_pacientes.bin` e `fila_pacientes.bin`.
- Ao iniciar, `LOAD(&arvore, &fila)` tenta recarregar os dados. Caso não seja possível, ele alerta.

## Funções da interface
1. Registrar paciente
2. Registrar óbito de paciente
3. Adicionar procedimento ao histórico médico
4. Desfazer procedimento do histórico médico
5. Chamar paciente para atendimento
6. Mostrar fila de espera
7. Mostrar histórico do paciente
8. Mostrar árvore de pacientes
9. Sair

## Escolha dos TADs

**TAD Paciente:** O TAD paciente implementado é equivalente ao TAD item, alterando apenas os campos da struct. Cada paciente possui um ID, um nome, um histórico de procedimentos e uma prioridade. O histórico médico é um ponteiro para pilha (outro TAD utilizado). Existem funções de criar, apagar, ler id e nome e histórico e imprimir as informações (tanto apenas id e nome quanto id, nome e prioridade) de um paciente, todas de custo constante O(1). Outras funções que foram implementadas durante a aula estão presentes no código do TAD porém não são utilizadas no projeto.

## Ordem de Prioridades

1. **Emergência** - Risco imediato de vida
2. **Muito Urgente** - Risco potencial de morte
3. **Urgente** - Gravidade moderada
4. **Não urgente** - Pode aguardar atendimento
5. **Consulta** - Sem risco à saúde

**TAD Pilha:** O TAD pilha é a estrutura de dados utilizada para armazenar os procedimentos do histórico médico dos pacientes. Desta maneira, cada nó da pilha armazena um string 'procedimento' de no máximo 100 caracteres (além de um ponteiro para o anterior). A pilha possui apenas um ponteiro para o nó do topo e o tamanho inteiro da pilha. A escolha foi a de uma pilha encadeada devido à alocação dinâmica dos nós, que é mais eficiente no quesito memória em relação a pilhas estáticas, além de que já havia sido implementado desta maneira na versão anterior do projeto. Existem funções de criar, apagar, empilhar, desempilhar, verificar tamanho, verificar se está cheia ou vazia e de impressão da pilha. Todas as funções exceto a de apagar e a de imprimir possuem custo constante O(1), enquanto estas possuem custo O(n), em que n é o número de procedimentos da pilha.

**TAD Fila de Prioridade:** Foi utilizada uma fila de prioridade implementada como **max-heap** (em termos de urgência/gravidade) para gerenciar os pacientes aguardando atendimento. Embora utilize números de 1 (máxima urgência) a 5 (mínima urgência), o heap é estruturado para colocar os números **menores no topo**, realizando atendimento por maior gravidade primeiro. Esta escolha substitui a fila simples FIFO da versão anterior, permitindo que pacientes com maior gravidade sejam atendidos primeiro. A prioridade é determinada no momento do registro do paciente. A estrutura da fila de prioridade contém um vetor de estruturas (paciente + timestamp) e o tamanho atual da fila. As operações principais incluem: inserção com reposicionamento (fix-up), remoção do elemento de maior prioridade (fix-down), busca, verificação de capacidade e impressão ordenada. A complexidade de inserção e remoção é O(log n), onde n é o número de pacientes na fila, enquanto a busca possui complexidade O(n). O timestamp é utilizado para desempate (FIFO) quando dois pacientes possuem a mesma prioridade. Esta implementação garante atendimento prioritário aos casos mais graves.

**TAD Árvore Binária de Busca (AVL):** Foi implementada uma **árvore AVL** (auto-balanceada) para armazenar todos os pacientes do banco de dados, substituindo a lista simplesmente encadeada da versão anterior. Esta mudança proporciona busca, inserção e remoção eficientes com complexidade garantida O(log n) mesmo no pior caso, através do balanceamento automático. A árvore é organizada pelos IDs dos pacientes. A estrutura contém um ponteiro para o nó raiz, e cada nó possui: um ponteiro para paciente, ponteiros para os filhos esquerdo e direito, e a altura para cálculo do fator de balanceamento. As operações implementadas incluem: criar, apagar, inserir com balanceamento, remover com rebalanceamento, buscar, verificar se está vazia, e imprimir em ordem. O balanceamento automático (através de rotações simples e duplas) garante desempenho eficiente mesmo em sistemas com grande quantidade de pacientes cadastrados.

**TAD Functions:** TAD que contém as **nove operações** da interface do usuário (mais a especial 471728 para reset). Esse TAD orquestra todos os outros TADs (Paciente, Árvore, Fila, Pilha) para implementar a lógica de negócio do hospital. Abaixo, um resumo das funcionalidades de cada uma:

`imprimir_escolha_operacao()`
Exibe no terminal o menu principal de operações (opções **1 a 9**) e retorna ao programa.

`registrar_paciente(ARVORE arvore, FILA_PRIORIDADE fila)`
Cadastra ou reinsere um paciente na fila de atendimento com prioridade.
- Se a **fila estiver cheia**, aborta a operação.
- Lê o **ID** do paciente e sua **prioridade** (gravidade do caso).
- Se **já existir paciente com esse ID**:
  - Se **já estiver na fila**, informa erro.
  - Se **não estiver na fila**, reinsere-o na fila com a prioridade especificada.
- Se **não existir**, lê o nome e a prioridade, cria o `PACIENTE`, insere na `ARVORE` e também na `FILA_PRIORIDADE`.

`registrar_obito(ARVORE arvore, FILA_PRIORIDADE fila)`
Remove definitivamente um paciente do sistema.

- Lê o **ID**.
- Se **existir na ARVORE** e **não estiver na FILA**, remove da árvore e destrói o registro.
- Se **existir, mas estiver na FILA**, bloqueia o registro de óbito.
- Se **não existir**, informa que o paciente é inexistente.

`desfazer_procedimento(ARVORE arvore)`
Desfaz o **último procedimento** do histórico médico de um paciente.

- Lê o **ID** e busca o paciente na árvore.
- Se o paciente for encontrado:
  - Tenta **desempilhar** o topo da `PILHA` de histórico.
  - Se conseguir, imprime o procedimento desfeito.
  - Se a pilha estiver vazia, informa ao usuário.
- Se o paciente **não for encontrado**, avisa que é inexistente.
  
`adicionar_procedimento(ARVORE arvore)`
Adiciona um novo procedimento ao histórico médico do paciente.

- Lê o **ID** e a **descrição** do procedimento.
- Busca o paciente na árvore:
  - Se **não existir**, avisa.
  - Se existir, verifica se a `PILHA` está cheia:
    - Se estiver, bloqueia a inserção.
    - Caso contrário, **empilha** o procedimento e confirma.
    
`chamar_paciente(FILA_PRIORIDADE fila)`
Chama o próximo paciente para atendimento (aquele de **maior prioridade**, numericamente menor).
- Remove o paciente de **maior prioridade** (menor número) da `FILA_PRIORIDADE`.
- Se havia alguém, imprime o ID chamado.
- Se a fila estiver vazia, informa ao usuário.
  
`mostrar_fila(FILA_PRIORIDADE fila)`
Exibe a **fila de espera** ordenada por prioridade.
- Se a fila estiver **vazia**, informa.
- Caso contrário, imprime todos os pacientes da `FILA_PRIORIDADE` em ordem de prioridade.
  
`mostrar_historico(ARVORE arvore)`
Mostra o **histórico médico** de um paciente específico.
- Lê o **ID** e busca o paciente na árvore.
- Se o paciente **não existir**, informa.
- Se existir:
  - Imprime o nome do paciente.
  - Exibe os procedimentos da `PILHA` de histórico (do **topo ao fundo**, via `pilha_imprimir()`).

`salvar_pacientes(ARVORE arvore, FILA_PRIORIDADE fila)`
Salva os dados atuais do sistema.

- Chama a função `SAVE(arvore, fila)`.
- Informa ao usuário se a operação foi concluída com sucesso ou se houve falha.

**TAD IO:** TAD responsável pela **persistência dos dados** em formato binário. As operações principais são:
- `SAVE(ARVORE, FILA_PRIORIDADE)`: Salva todos os pacientes da árvore e da fila nos arquivos `arvore_pacientes.bin` e `fila_atendimento.bin`.
- `LOAD(ARVORE, FILA_PRIORIDADE)`: Carrega os dados salvos e reconstrói as estruturas (árvore e fila) com os mesmos pacientes e timestamps.

Os dados são salvos ao encerrar (opção 9) e carregados ao iniciar o programa. O timestamp de cada paciente é preservado para manter a ordem FIFO em caso de prioridades iguais. Compatibilidade com Windows e Unix.

## Compilação

gcc -o sistema_hospitalar main.c Arvore_Binaria/arvore.c Fila_Prioridade/fila_prioridade.c Pilha_Encadeada/pilha.c TAD_functions/functions.c TAD_IO/IO.c TAD_Paciente/paciente.c

## Execução
./sistema_hospitalar
