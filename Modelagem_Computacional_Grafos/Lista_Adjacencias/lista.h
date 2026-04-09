#ifndef LISTA_H
	#define LISTA_H
	                       
	typedef struct lista LISTA;

	LISTA *lista_criar();
	bool lista_inserir(LISTA *lista, int id_no, int peso);
	bool lista_remover(LISTA *lista, int chave);
	bool lista_apagar(LISTA **lista);
	int lista_busca(LISTA *lista, int chave);
	int lista_tamanho(LISTA *lista);
	bool lista_vazia(LISTA *lista);
	bool lista_cheia(LISTA *lista);
	void lista_imprimir(LISTA *lista);

	/*Funções adicionais*/
	int lista_inverter(LISTA **lista);
	bool lista_comparar(LISTA *l1, LISTA *l2);
	
	// Funções para lista de adjacências de um grafo
	int *lista_extrair_no_ids(LISTA *l);
	int **lista_percorrer_arestas(LISTA *l);

#endif
