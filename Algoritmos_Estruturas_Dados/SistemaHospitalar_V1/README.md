## Sistema Hospitalar AED

Este projeto simula um sistema de atendimento médico de pacientes em um Pronto Socorro (PS), utilizando Tipos Abstratos de Dados (TADs) em C.
Desenvolvido por:
- André Campanholo Paschoalini - 14558061
- Eduardo Poltroniere da Silva - 16862892
- Pedro Hamamoto da Palma - 16818280

- ## Estrutura
- `main.c` - ponto de entrada e loop do menu.

Diretórios principais / TADs:
- `TAD_Paciente/` - (`paciente.c`, `paciente.h`) cadastro, busca, remoção e gerenciamento de pacientes (id, nome, histórico).
- `Lista_Simples_Encadeada/` - (`lista.c`, `lista.h`) lista dinâmica para armazenar pacientes (a lista é dona das estruturas `PACIENTE`).
- `Fila_Encadeada/` - (`fila.c`, `fila.h`) fila encadeada para triagem (FIFO) com capacidade finita (implementada como 10 no código atual).
- `Pilha_Encadeada/` - (`pilha.c`, `pilha.h`) pilha encadeada para histórico de procedimentos (LIFO) — máximo 10 procedimentos, cada um até 100 caracteres.
- `TAD_functions/` - (`functions.c`, `functions.h`) implementa as operações do menu e a lógica de negócio (registrar, óbito, procedimentos, chamada, etc.).
- `TAD_IO/` - (`IO.c`, `IO.h`) persistência: `SAVE` e `LOAD` para ler/gravar `lista_pacientes.bin` e `fila_pacientes.bin`.

## Principais funcionalidades e onde estão implementadas
- Registrar paciente: `TAD_functions/registrar_paciente` — cria `PACIENTE`, insere na `Lista_Simples_Encadeada` e em `Fila_Encadeada`.
- Registrar óbito: `TAD_functions/registrar_obito` — só permite apagar paciente se ele NÃO estiver na fila (apenas após ter sido chamado); remove da lista e apaga o `PACIENTE`.
- Adicionar procedimento: `TAD_functions/adicionar_procedimento` — empilha procedimento no `PILHA` do paciente.
- Desfazer procedimento: `TAD_functions/desfazer_procedimento` — desempilha o último procedimento e informa qual foi removido.
- Chamar paciente: `TAD_functions/chamar_paciente` — remove o paciente da fila (`fila_remover_paciente`) e o entrega para atendimento.
- Mostrar fila: `TAD_functions/mostrar_fila` — imprime a fila de espera.
- Mostrar histórico: `TAD_functions/mostrar_historico` — imprime o histórico (pilha) do paciente.
- Mostrar lista: `TAD_Lista_Simples_Encadeada/lista_imprimir` - imprime a lista de todos os pacientes.
- Salvar/Carregar: `TAD_IO/SAVE` e `TAD_IO/LOAD` carregam e salvam a lista e a fila de pacientes ao iniciar e ao fechar o programa (`main.c`) respectivamente.

## Persistência
- Ao sair (opção de menu), o programa chama `SAVE(lista, fila)` e grava `lista_pacientes.bin` e `fila_pacientes.bin`.
- Ao iniciar, `LOAD(&lista, &fila)` tenta recarregar os dados.

## Funções da interface
1. Registrar paciente
2. Registrar óbito de paciente
3. Adicionar procedimento ao histórico médico
4. Desfazer procedimento do histórico médico
5. Chamar paciente para atendimento
6. Mostrar fila de espera
7. Mostrar histórico do paciente
8. Mostrar lista de pacientes
9. Sair

## Escolha dos TADs
**TAD Paciente:** O TAD paciente implementado é equivalente ao TAD item, alterando apenas os campos da struct. Cada paciente possui um ID, um nome e um histórico de procedimentos, o último sendo um ponteiro para pilha (outro TAD utilizado). Existem funções de criar, apagar, ler id e nome e histórico e imprimir as informações (id e nome) de um paciente, todas de custo constante O(1). Outras funções que foram implementadas durante a aula estão presentes no código do TAD porém não são utilizadas no projeto.

**TAD Pilha:** O TAD pilha é a estrutura de dados utilizado para armazenar os procedimentos do histórico médico dos pacientes. Desta maneira, cada nó da pilha armazena um string 'procedimento' de no máximo 100 caracteres (além de um ponteiro para o anterior). A pilha possui apenas um ponteiro para o nó do topo e o tamanho inteiro da pilha. A escolha foi a de uma pilha encadeada devido à alocação dinâmica dos nós, tendo em vista que estruturas de dados do tipo encadeada são mais eficientes no geral e queríamos treinar este tipo de implementação. Existem funções de criar, apagar, empilhar, desempilhar, verificar tamanho, verificar se está cheia ou vazia e de impressão da pilha. Todas as funções exceto a de apagar e a de imprimir possuem custo constante O(1), enquanto estas possuem custo O(n), em que n é o número de procedimentos da pilha.

**TAD Fila Encadeada:** Foi utilizada um fila encadeada como estrutura de dados que armazena os pacientes da fila de espera. Escolhemos a implementação encadeada pois existem muitas inserções e remoções de pacientes na fila, equivalentes aos procedimentos de registro e convocação para atendimento de cada paciente. Se trata da melhor escolha pois uma implementação sequencial (se não circular) exige deslocamentos após toda remoção, enquanto o modelo encadeado resolve este problema apenas com ajuste de ponteiros. A estrutura da fila contém um ponteiro para o nó do início, um para o fim e o tamanho inteiro da fila. Cada nó armazena um paciente (mais especificamente, um ponteiro para paciente) e um ponteiro para o próximo nó. Existem funções de criar, apagar, inserir, remover, buscar, consultar a frente e o fim da fila, verificar se está cheia ou vazia, verificar o tamanho e uma função que esvazia a fila sem apagá-la. Destas, possuem complexidade O(n) as funções de apagar, buscar, imprimir e esvaziar a fila, enquanto as demais tem custo O(1).

**TAD Lista Simplesmente Encadeada:** A lista encadeada foi utilizada para armazenar todos os pacientes do banco de dados, e escolhemos esta implementação pelo mesmo motivo da fila encadeada: existem muitas inserções e remoções de pacientes, que se dão na forma de novos cadastros e registros de óbitos, respectivamente. Ademais, na data de implementação do esqueleto do projeto tínhamos visto somente este tipo de lista. A estrutura da lista contém um ponteiro para o nó do início, um para o fim, o tamanho inteiro da lista e uma variável booleana que permite escolher se a lista criada é ordenada ou não (no nosso sistema a lista de pacientes não é ordenada). Cada nó possui um ponteiro para paciente e um ponteiro para o próximo nó. Neste TAD existem funções de criar, apagar, inserir, remover, buscar, verificar se está cheia ou vazia, verificar o tamanho atual, imprimir a lista e esvaziar a lista. As que possuem complexidade O(n), diferente das demais que tem custo constante, são as funções de remoção, de busca, de imprimir, e de esvaziar a lista.

**TAD Functions:** TAD que contém as nove funções da interface do usuário. Esse TAD inclui todos os outros, e usa as funções dele para realizar as operações do hospital. Abaixo, um resumo das funcionalidades de cada uma:

`imprimir_escolha_operacao()`
Exibe no terminal o menu principal de operações (opções **1 a 9**) e retorna ao programa.

`registrar_paciente(LISTA lista, FILA fila)`
Cadastra ou reinsere um paciente na fila de atendimento.
- Se a **fila estiver cheia**, aborta a operação.
- Lê o **ID** do paciente.
- Se **já existir paciente com esse ID**:
  - Se **já estiver na fila**, informa erro.
  - Se **não estiver na fila**, reinsere-o na fila.
- Se **não existir**, lê o nome, cria o `PACIENTE`, insere na `LISTA` e também na `FILA`.

`registrar_obito(LISTA lista, FILA fila)`
Remove definitivamente um paciente do sistema.

- Lê o **ID**.
- Se **existir na LISTA** e **não estiver na FILA**, remove da lista e destrói o registro.
- Se **existir, mas estiver na FILA**, bloqueia o registro de óbito.
- Se **não existir**, informa que o paciente é inexistente.

`desfazer_procedimento(LISTA lista)`
Desfaz o **último procedimento** do histórico médico de um paciente.

- Lê o **ID** e busca o paciente.
- Se o paciente for encontrado:
  - Tenta **desempilhar** o topo da `PILHA` de histórico.
  - Se conseguir, imprime o procedimento desfeito.
  - Se a pilha estiver vazia, informa ao usuário.
- Se o paciente **não for encontrado**, avisa que é inexistente.
  
`adicionar_procedimento(LISTA lista)`
Adiciona um novo procedimento ao histórico médico do paciente.

- Lê o **ID** e a **descrição** do procedimento.
- Verifica se o paciente existe:
  - Se **não existir**, avisa.
  - Se existir, verifica se a `PILHA` está cheia:
    - Se estiver, bloqueia a inserção.
    - Caso contrário, **empilha** o procedimento e confirma.
    
`chamar_paciente(FILA fila)`
Chama o próximo paciente para atendimento.
- Remove (**dequeue**) o primeiro paciente da `FILA`.
- Se havia alguém, imprime o ID chamado.
- Se a fila estiver vazia, informa ao usuário.
  
`mostrar_fila(FILA fila)`
Exibe a **fila de espera**.
- Se a fila estiver **vazia**, informa.
- Caso contrário, imprime todos os pacientes da `FILA`.
  
`mostrar_historico(LISTA lista)`
Mostra o **histórico médico** de um paciente específico.
- Lê o **ID** e busca o paciente.
- Se o paciente **não existir**, informa.
- Se existir:
  - Imprime o nome do paciente.
  - Exibe os procedimentos da `PILHA` de histórico (do **topo ao fundo**, via `pilha_imprimir()`).

`salvar_pacientes(LISTA lista, FILA fila)`
Salva os dados atuais do sistema.

- Chama a função `SAVE(lista, fila)`.
- Informa ao usuário se a operação foi concluída com sucesso ou se houve falha.

**TAD IO:** TAD responsável pela persistência dos dados. As operações de salvar e de carregar as informações são feitas durante o encerramento e o ínicio do programa, respectivamente. Os dados não são salvos on-the-fly. A implementação foi feita com base no TAD IO fornecido pelos professores, com algumas adaptações para se ajustar à implementação do sistema. Foram utilizados recursos de IA para auxiliar no desenvolvimento dessa função, já que houveram dificuldades para adaptá-la para nosso programa.

## Compilação

gcc -o sistema_hospitalar main.c Fila_Encadeada/fila.c Lista_Simples_Encadeada/lista.c Pilha_Encadeada/pilha.c TAD_functions/functions.c TAD_IO/IO.c TAD_Paciente/paciente.c

## Execução
./sistema_hospitalar






