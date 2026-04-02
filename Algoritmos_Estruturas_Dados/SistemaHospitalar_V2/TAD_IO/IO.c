#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "IO.h"
#ifdef _WIN32
#include <direct.h>
#else
#include <sys/stat.h>
#include <sys/types.h>
#endif
#include "../Pilha_Encadeada/pilha.h"

static void ensure_data_dir(void)
{
#ifdef _WIN32
    _mkdir("Persistencia_Dados");
#else
    mkdir("Persistencia_Dados", 0777);
#endif
}

bool SAVE(ARVORE *arvore, FILA_PRIORIDADE *fila)
{
    ensure_data_dir();
    // Salvar pacientes (árvore) em ordem
    FILE *fp_arvore = fopen("Persistencia_Dados/arvore_pacientes.bin", "wb");
    if (!fp_arvore)
        return false;
    int tam_arvore = arvore_tamanho(arvore);
    fwrite(&tam_arvore, sizeof(int), 1, fp_arvore);
    int count_list = 0;
    PACIENTE **lista = arvore_listar_em_ordem(arvore, &count_list);
    for (int i = 0; i < count_list; ++i)
    {
        PACIENTE *paciente = lista[i];
        int id = paciente_get_id(paciente);
        const char *nome = paciente_get_nome(paciente);
        int nome_len = (int)strlen(nome) + 1;
        int prioridade = paciente_get_prioridade(paciente);

        fwrite(&id, sizeof(int), 1, fp_arvore);
        fwrite(&nome_len, sizeof(int), 1, fp_arvore);
        fwrite(nome, sizeof(char), nome_len, fp_arvore);
        fwrite(&prioridade, sizeof(int), 1, fp_arvore);

        PILHA *hist = paciente_get_historico(paciente);
        int hist_tam = pilha_tamanho(hist);
        fwrite(&hist_tam, sizeof(int), 1, fp_arvore);
        for (int h = 0; h < hist_tam; ++h)
        {
            char proc[100];
            pilha_obter_elemento(hist, h, proc);
            fwrite(proc, sizeof(char), 100, fp_arvore);
        }
    }
    arvore_liberar_lista(lista);
    fclose(fp_arvore);

    // Salvar fila de prioridade: id + timestamp
    FILE *fp_fila = fopen("Persistencia_Dados/fila_atendimento.bin", "wb");
    if (!fp_fila)
        return false;
    int tf = fila_prioridade_tamanho(fila);
    fwrite(&tf, sizeof(int), 1, fp_fila);
    int tf_list = 0;
    FILA_ITEM **items = fila_prioridade_listar(fila, &tf_list);
    for (int i = 0; i < tf_list; ++i)
    {
        const PACIENTE *pac = fila_item_get_paciente(items[i]);
        int id = paciente_get_id((PACIENTE *)pac);
        time_t ts = fila_item_get_timestamp(items[i]);
        fwrite(&id, sizeof(int), 1, fp_fila);
        fwrite(&ts, sizeof(time_t), 1, fp_fila);
    }
    fila_prioridade_liberar_lista(items, tf_list);
    fclose(fp_fila);
    return true;
}

bool LOAD(ARVORE **arvore, FILA_PRIORIDADE **fila)
{
    if (!*arvore || !*fila)
        return false;

    // Carregar pacientes da árvore
    FILE *fp_arvore = fopen("Persistencia_Dados/arvore_pacientes.bin", "rb");
    if (!fp_arvore)
        return false;
    int tam = 0;
    if (fread(&tam, sizeof(int), 1, fp_arvore) != 1)
    {
        fclose(fp_arvore);
        return false;
    }
    for (int i = 0; i < tam; ++i)
    {
        int id = 0, nome_len = 0, prioridade = 3, hist_tam = 0;
        if (fread(&id, sizeof(int), 1, fp_arvore) != 1)
            break;
        if (fread(&nome_len, sizeof(int), 1, fp_arvore) != 1)
            break;
        char nome[256] = {0};
        if (nome_len <= 0 || nome_len >= (int)sizeof(nome))
            nome_len = (int)sizeof(nome);
        fread(nome, sizeof(char), nome_len, fp_arvore);
        PACIENTE *paciente = paciente_criar(id, nome);
        fread(&prioridade, sizeof(int), 1, fp_arvore);
        paciente_set_prioridade(paciente, prioridade);
        fread(&hist_tam, sizeof(int), 1, fp_arvore);
        for (int h = 0; h < hist_tam; ++h)
        {
            char proc[100];
            fread(proc, sizeof(char), 100, fp_arvore);
            pilha_empilhar(paciente_get_historico(paciente), proc);
        }
        arvore_inserir(*arvore, paciente);
    }
    fclose(fp_arvore);

    // Carregar fila de prioridade com referência aos pacientes existentes
    FILE *fp_fila = fopen("Persistencia_Dados/fila_atendimento.bin", "rb");
    if (!fp_fila)
        return false;
    int tf = 0;
    if (fread(&tf, sizeof(int), 1, fp_fila) != 1)
    {
        fclose(fp_fila);
        return false;
    }
    for (int i = 0; i < tf; ++i)
    {
        int id = 0;
        time_t ts = 0;
        fread(&id, sizeof(int), 1, fp_fila);
        fread(&ts, sizeof(time_t), 1, fp_fila);
        PACIENTE *paciente = arvore_buscar(*arvore, id);
        if (paciente)
            fila_prioridade_inserir_aux(*fila, paciente, ts);
    }
    fclose(fp_fila);
    return true;
}
