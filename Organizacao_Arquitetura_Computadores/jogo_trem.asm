	.data
	.align 0

# Strings de inicialização
boas_vindas:	
        .asciz "Bem-vindo! Este é o jogo Montagem de Trem! Divirta-se!\n" 
menu_opcoes:	
        .asciz "\nSelecione uma operação abaixo:\n1 - Adicionar vagão no início do trem.\n2 - Adicionar vagão no final do trem.\n3 - Remover vagão por ID.\n4 - Listar trem.\n5 - Buscar vagão por ID.\n6 - Sair do jogo.\n"
digite_opcao:	
        .asciz "Digite operação: "

# Strings de informação de ID
informar_id_add:
	.asciz "\nDigite o ID do vagão a ser inserido: "
informar_id_busca:
	.asciz "\nDigite o ID do vagão que deseja-se buscar: "
informar_id_rem:
	.asciz "\nDigite o ID do vagão a ser removido: "
msg_id_negativo:
	.asciz "\nID negativo! IDs devem ser números inteiros positivos, por favor, informe outro ID.\n"
msg_id_repetido:
	.asciz "\nID repetido! IDs devem ser únicos, por favor, informe outro ID.\n"

# Strings de opereções bem-sucedidas
sucesso_add: 
	.asciz "\n\nVagão inserido com sucesso!\n"
sucesso_rem:
	.asciz "\nVagão removido com sucesso!\n"

# Strings de informação de código (tipo de vagão)
informar_tipo:	
       	.asciz "\nInforme o tipo de vagão a ser inserido, de acordo com o código de três letras:\nLOC - Locomotiva\nCAR - Carga\nPAS - Passageiro\nCOM - Combustível\n"
digite_codigo:	
        .asciz "Digite o código: "
codigo_invalido:
	.asciz "\nCódigo inválido! Use um dos códigos válidos: LOC, CAR, PAS ou COM.\n"

# Strings de busca
vagao_encontrado:
	.asciz "\nVagão encontrado: <"
nao_encontrado:	
        .asciz "\nNão existe vagão com esse ID, tente novamente.\n"

# Strings de operações inválidas
rem_locomotiva:	
        .asciz "\nNão é permitida a remoção do primeiro vagão.\n"
opcao_invalida:	
        .asciz "\nOperação inválida. Insera um número de opção válido.\n"

# Strings de formatação
hifen_str:	
        .asciz " - "
pipe_str:	
        .asciz " | "

# String de encerramento
encerrar_jogo:
        .asciz "\nEncerrando programa...\n"

# Variáveis globais
	.align 2
		
codigo_vagao:   
	.space 4 # Buffer para leitura do código do tipo de vagão
head_ptr:	
	.word 0 # Ponteiro para o início do trem (primeiro nó)

# Tabela de códigos válidos para os tipos de vagão (LOC, CAR, PAS, COM)
codigos_validos:
	.byte 'L', 'O', 'C', 0
	.byte 'C', 'A', 'R', 0
	.byte 'P', 'A', 'S', 0
	.byte 'C', 'O', 'M', 0


# Estrutura do nó (locomotiva) => 12 bytes
locomotiva:
	.word 0 # ID => (0,3)
	.byte 'L','O','C',0 # Tipo(Código) => (4,7)
	.word 0 # Next (8, 11)
	
	.text
	.align 2
	.globl main

# Rotina principal do programa
main:
	# Inicializa o trem com a locomotiva fixa no primeiro nó.
	la s0, head_ptr
	la t1, locomotiva
	sw t1, 0(s0)

	# Mensagem de Boas-vindas
	li a7, 4
	la a0, boas_vindas
	ecall

# Loop principal do menu
menu_loop:	
	li a7, 4
	la a0, menu_opcoes
	ecall
	li a7, 4
	la a0, digite_opcao
	ecall
	li a7, 5
	ecall
	mv s1, a0

	addi t0, zero, 1
	beq s1, t0, add_inicio
	addi t0, zero, 2
	beq s1, t0, add_final
	addi t0, zero, 3
	beq s1, t0, remover_vagao
	addi t0, zero, 4
	beq s1, t0, listar_trem
	addi t0, zero, 5
	beq s1, t0, buscar_vagao
	addi t0, zero, 6
	beq s1, t0, sair_jogo

	li a7, 4
	la a0, opcao_invalida
	ecall
	j menu_loop

# Opção 1 - Adicionar vagão no início do trem
add_inicio:	
	jal valores_add
	jal aloca_vagao

	sw t1, 0(t3) # armazena o ID do vagão

	la t2, codigo_vagao 
	lw t2, 0(t2) # carrega o código do tipo de vagão
	sw t2, 4(t3) # armazena o código do tipo de vagão

	lw t4, 0(s0) # carrega o head_ptr (nó atual)
	lw t5, 8(t4) # carrega o próximo nó do trem
	sw t5, 8(t3) # novo nó aponta para o próximo nó atual
	sw t3, 8(t4) # cabeça aponta para o novo nó

	li a7, 4
	la a0, sucesso_add
	ecall
	j menu_loop
# Opção 2 - Adicionar vagão no final do trem
add_final: 	
	jal valores_add
	jal aloca_vagao

	sw t1, 0(t3) # armazena o ID do vagão

	la t2, codigo_vagao
	lw t2, 0(t2) # carrega o código do tipo de vagão
	sw t2, 4(t3) # armazena o código do tipo de vagão

	sw zero, 8(t3) # novo nó aponta para nulo (final do trem)
	lw t4, 0(s0) # carrega o ponteiro do início		
loop_encadear:	
	lw t5, 8(t4) # o próximo nó
	beq t5, zero, encadear_final # se nulo, está no final
	lw t4, 8(t4) # avança para o próximo nó
	j loop_encadear			
encadear_final: 
	sw t3, 8(t4) # conecta novo nó ao final
		
	li a7, 4
	la a0, sucesso_add
	ecall
	j menu_loop

# Opção 3 - Remover vagão por ID
remover_vagao:
	li a7, 4
	la a0, informar_id_rem
	ecall
	li a7, 5
	ecall
	mv t0, a0 # o ID do vagão a ser removido
	beq t0, zero, remocao_proibida
	lw t1, 0(s0) # o primeiro nó (locomotiva, não pode ser removida)
loop_remover:	
	lw t2, 8(t1) # o próximo nó (candidato para remoção)
	beq t2, zero, vagao_nao_encontrado
	lw t3, 0(t2)
	beq t0, t3, remover_no
	lw t1, 8(t1)
	j loop_remover
vagao_nao_encontrado:
	li a7, 4
	la a0, nao_encontrado
	ecall
	j menu_loop
remover_no:
	lw t4, 8(t2) # o próximo nó do removido
	sw t4, 8(t1) # conecta o anterior ao próximo
	sw zero, 8(t2) # limpa o next do nó removido
	li a7, 4
	la a0, sucesso_rem
	ecall
	j menu_loop
remocao_proibida:
	li a7, 4
	la a0, rem_locomotiva
	ecall
	j menu_loop

# Opção 4 - Listar trem
listar_trem:
	li a7, 11 # syscall de impressão de caractere
	addi a0, zero, 10 # nova linha
	ecall
	lw t4, 0(s0)
loop_imprime_trem:
	beq t4, zero, fim_loop_imprime_trem
	li a7, 1
	lw a0, 0(t4) 
	ecall
	li a7, 4
	la a0, hifen_str
	ecall
	li a7, 4
	addi a0, t4, 4 # o endereço do código do tipo de vagão
	ecall 
	lw t5, 8(t4) # o próximo nó
	beq t5, zero, fim_loop_imprime_trem
	li a7, 4
	la a0, pipe_str
	ecall
	mv t4, t5
	j loop_imprime_trem
fim_loop_imprime_trem:
	li a7, 11 # syscall de impressão de caractere
	addi a0, zero, 10 # nova linha
	ecall
	j menu_loop

# Opção 5 - Buscar vagão por ID
buscar_vagao:
	li a7, 4
	la a0, informar_id_busca
	ecall
	li a7, 5
	ecall
	mv t0, a0
	lw t1, 0(s0)
loop_buscar:
	beq t1, zero, nao_encontrou_vagao
	lw t2, 0(t1) # o ID do nó atual
	lw t3, 4(t1) # o tipo do nó atual
	beq t0, t2, encontrou_vagao
	lw t1, 8(t1) # o próximo nó
	j loop_buscar
encontrou_vagao:
	li a7, 4
	la a0, vagao_encontrado
	ecall
	li a7, 1
	add a0, zero, t2 
	ecall
	li a7, 4
	la a0, hifen_str
	ecall
	li a7, 4
	addi a0, t1, 4 
	ecall
	li a7, 11
	addi a0, zero, 62 # imprime ">" 
	ecall
	li a7, 11
	addi a0, zero, 10 # nova linha
	ecall
	j menu_loop
nao_encontrou_vagao:
	li a7, 4
	la a0, nao_encontrado
	ecall
	j menu_loop

# Opção 6 - Sair do jogo
sair_jogo:
	li a7, 4
	la a0, encerrar_jogo
	ecall
	li a7,10 
	ecall

# Seção de rotinas auxiliares
    # Rotina para ler ID e código do vagão. Retorna ID em t1 e código em t2.
valores_add:	
	addi sp, sp, -4 # reserva o espaço na pilha para o ra
	sw ra, 0(sp) # preserva o endereço de retorno
ler_id:
	li a7, 4
	la a0, informar_id_add
	ecall
	li a7, 5 # leitura do ID
	ecall
	mv t1, a0
	jal verificar_id
	beq a0, zero, ler_id
	li a7, 4
	la a0, informar_tipo
	ecall
ler_codigo:
	li a7, 4
	la a0, digite_codigo
	ecall
	li a7, 8
	la a0, codigo_vagao
	addi a1, zero, 4  # o máximo de bytes a ler
	ecall
	jal verificar_codigo
	beq a0, zero, codigo_invalido_msg
	la t2, codigo_vagao
	lw t2, 0(t2) # carrega o código do tipo
	lw ra, 0(sp)
	addi sp, sp, 4
	jr ra
codigo_invalido_msg:
	li a7, 4
	la a0, codigo_invalido
	ecall
	j ler_codigo

    # Rotina para verificar se o ID do vagão a ser inserido é único. Retorna 1 (a0) se o ID for livre, 0 se negativo ou já existir no trem.
verificar_id:
	blt t1, zero, id_negativo # verifica se o ID é negativo
	lw t3, 0(s0) # inicia o percurso da lista
loop_verificar_id:
	beq t3, zero, id_livre # se chegou ao final (t3 = NULL), o ID é livre
	lw t4, 0(t3) # carrega o ID armazenado no nó atual
	beq t1, t4, id_repetido # compara novo ID com ID do nó

	lw t3, 8(t3) # próximo nó
	j loop_verificar_id
id_negativo:
	li a7, 4
	la a0, msg_id_negativo
	ecall
	li a0, 0
	jr ra
id_repetido:
	li a7, 4
	la a0, msg_id_repetido
	ecall
       	li a0, 0
    	jr ra
id_livre:
       	li a0, 1
       	jr ra

    # Rotina para verificar se o código do tipo do vagão é válido (LOC, CAR, PAS ou COM). Retorna 1 (a0) se válido, 0 se inválido.
verificar_codigo:
	la t5, codigo_vagao
	lw t0, 0(t5) # código inserido
	
	la t6, codigos_validos
	li t2, 4 # o contador de tipos
loop_verif_codigos:
	lw t3, 0(t6)
	beq t0, t3, codigo_valido
		
	addi t6, t6, 4 # o próximo código
	addi t2, t2, -1
	bne t2, zero, loop_verif_codigos
		
	li a0, 0 
	jr ra
codigo_valido:
	li a0, 1
	jr ra

    # Rotina para alocar espaço para um novo vagão (12 bytes) e retornar endereço em t3
aloca_vagao:
	li a7, 9
	addi a0, zero, 12 # aloca o espaço do nó
	ecall 
	mv t3, a0
	jr ra