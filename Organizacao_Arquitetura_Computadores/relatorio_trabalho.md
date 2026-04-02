# Relatório — 1º Trabalho Prático (SSC0902)

**Jogo "Montagem de Trem" em Assembly RISC-V**

## Objetivo e escopo

Implementamos o jogo descrito no enunciado: o trem é uma lista encadeada simples, com a locomotiva fixa como primeiro nó e os demais vagões contendo **ID** (inteiro), **tipo** (códigos LOC, CAR, PAS e COM) e **ponteiro para o próximo nó**. O programa exibe mensagem de boas-vindas, menu com as seis opções pedidas (inserir no início, inserir no final, remover por ID, listar, buscar e sair) e trata casos como remoção da locomotiva proibida, IDs únicos e código de tipo válido.

## Processo de desenvolvimento

Começamos modelando a estrutura de cada nó (12 bytes) e um ponteiro global para o início da lista (`head_ptr`). Para novos vagões usamos **alocação dinâmica** via syscall (`ecall` com serviço de alocação de memória). As operações de inserção no início (logo após a locomotiva), no final, remoção com ajuste de ponteiros, percurso para listar e busca por ID seguem a lógica usual de listas encadeadas, traduzida para loads/stores e desvios condicionais em RISC-V.

## Desafios enfrentados

**Sintaxe e estilo em assembly.** Por ser linguagem de baixo nível, a leitura e a escrita do código não foram imediatas. Diferente de C ou Java, não há "variáveis com nome" nos registradores; o mesmo registrador muda de papel ao longo do programa. Por isso foi essencial manter **comentários claros e objetivos** e **rótulos** que deixassem explícito o que cada trecho fazia, tanto para nós quanto para quem for corrigir.

**Lista ligada, ponteiros e memória dinâmica.** A parte logicamente mais exigente foi manipular ponteiros, encadear e desencadear nós e garantir que inserções e remoções (inclusive no meio e no fim) não quebrassem a lista. Ter estudado o tema antes em **C** (alocação, `next`, percorrer a lista) ajudou muito na hora de "traduzir" para loads, stores e offsets fixos em bytes.

**Procedimentos e `jal`.** O uso de rotinas com `jal` trouxe outra dificuldade: é preciso cuidar do registrador de retorno `ra` e, quando necessário, **salvar e restaurar registradores na pilha**, para chamadas aninhadas ou para não perder valores ao voltar do procedimento.

## Soluções e lições aprendidas

Concentramos a alocação de um novo vagão em uma rotina dedicada (`aloca_vagao`), o que evitou repetir syscall e deixou o fluxo das opções do menu mais legível. Validar entrada (ID, tipo, opção de menu) cedo reduziu erros difíceis de depurar depois. No geral, o trabalho reforçou a noção de **layout de dados na memória**, **convenções de chamada** e o porquê de linguagens de alto nível abstraírem ponteiros e pilha — o que torna a matéria mais concreta para nós.

## Conclusão

O trabalho cumpre as funcionalidades obrigatórias e foi útil para relacionar **Organização e Arquitetura de Computadores** com programação estruturada que já conhecíamos: a mesma ideia de lista ligada aparece aqui "por baixo do capô", com registradores, memória e syscalls explícitos.