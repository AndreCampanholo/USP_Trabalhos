#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "IO.h"
#include "../Lista_Simples_Encadeada/lista.h"
#include "../Fila_Encadeada/fila.h"
#include "../TAD_Paciente/paciente.h"
#include "../Pilha_Encadeada/pilha.h"

bool SAVE(LISTA *lista, FILA *fila)
{
    FILE *fp_lista = fopen("Persistencia_Dados/lista_pacientes.bin", "wb");
    if (!fp_lista)
        return false;
    int tam_lista = lista_tamanho(lista);
    fwrite(&tam_lista, sizeof(int), 1, fp_lista);
    void *no = lista_primeiro_no(lista);
    while (no)
    {
        PACIENTE *paciente = lista_no_paciente(no);
        int id = paciente_get_id(paciente);
        const char *nome = paciente_get_nome(paciente);
        int nome_len = strlen(nome) + 1;
        fwrite(&id, sizeof(int), 1, fp_lista);
        fwrite(&nome_len, sizeof(int), 1, fp_lista);
        fwrite(nome, sizeof(char), nome_len, fp_lista);
        PILHA *hist = paciente_get_historico(paciente);
        int hist_tam = pilha_tamanho(hist);
        fwrite(&hist_tam, sizeof(int), 1, fp_lista);
        for (int h = 0; h < hist_tam; ++h)
        {
            char proc[100];
            pilha_obter_elemento(hist, h, proc);
            fwrite(proc, sizeof(char), 100, fp_lista);
        }
        no = lista_proximo_no(no);
    }
    fclose(fp_lista);

    FILE *fp_fila = fopen("Persistencia_Dados/fila_pacientes.bin", "wb");
    if (!fp_fila)
        return false;
    int tam_fila = fila_tamanho(fila);
    fwrite(&tam_fila, sizeof(int), 1, fp_fila);
    void *no_f = fila_primeiro_no(fila);
    while (no_f)
    {
        PACIENTE *paciente = fila_no_paciente(no_f);
        int id = paciente_get_id(paciente);
        const char *nome = paciente_get_nome(paciente);
        int nome_len = strlen(nome) + 1;
        fwrite(&id, sizeof(int), 1, fp_fila);
        fwrite(&nome_len, sizeof(int), 1, fp_fila);
        fwrite(nome, sizeof(char), nome_len, fp_fila);
        PILHA *hist = paciente_get_historico(paciente);
        int hist_tam = pilha_tamanho(hist);
        fwrite(&hist_tam, sizeof(int), 1, fp_fila);
        for (int h = 0; h < hist_tam; ++h)
        {
            char proc[100];
            pilha_obter_elemento(hist, h, proc);
            fwrite(proc, sizeof(char), 100, fp_fila);
        }
        no_f = fila_proximo_no(no_f);
    }
    fclose(fp_fila);
    return true;
}

bool LOAD(LISTA **lista, FILA **fila)
{
    if (!*lista || !*fila)
        return false;
    FILE *fp_lista = fopen("Persistencia_Dados/lista_pacientes.bin", "rb");
    if (!fp_lista)
        return false;
    int tam_lista = 0;
    fread(&tam_lista, sizeof(int), 1, fp_lista);
    for (int i = 0; i < tam_lista; ++i)
    {
        int id = 0, nome_len = 0, hist_tam = 0;
        fread(&id, sizeof(int), 1, fp_lista);
        fread(&nome_len, sizeof(int), 1, fp_lista);
        char nome[100];
        fread(nome, sizeof(char), nome_len, fp_lista);
        PACIENTE *paciente = paciente_criar(id, nome);
        fread(&hist_tam, sizeof(int), 1, fp_lista);
        for (int h = 0; h < hist_tam; ++h)
        {
            char proc[100];
            fread(proc, sizeof(char), 100, fp_lista);
            pilha_empilhar(paciente_get_historico(paciente), proc);
        }
        lista_inserir(*lista, paciente);
    }
    fclose(fp_lista);

    FILE *fp_fila = fopen("Persistencia_Dados/fila_pacientes.bin", "rb");
    if (!fp_fila)
        return false;
    int tam_fila = 0;
    fread(&tam_fila, sizeof(int), 1, fp_fila);
    for (int i = 0; i < tam_fila; ++i)
    {
        int id = 0, nome_len = 0, hist_tam = 0;
        fread(&id, sizeof(int), 1, fp_fila);
        fread(&nome_len, sizeof(int), 1, fp_fila);
        char nome[100];
        fread(nome, sizeof(char), nome_len, fp_fila);
        PACIENTE *paciente = paciente_criar(id, nome);
        fread(&hist_tam, sizeof(int), 1, fp_fila);
        for (int h = 0; h < hist_tam; ++h)
        {
            char proc[100];
            fread(proc, sizeof(char), 100, fp_fila);
            pilha_empilhar(paciente_get_historico(paciente), proc);
        }
        fila_inserir_paciente(*fila, paciente);
    }
    fclose(fp_fila);
    return true;
}