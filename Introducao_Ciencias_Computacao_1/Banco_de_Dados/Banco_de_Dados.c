#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct { //struct com os campos de registro
    int id;
    char login[50], password[50], gender;
    double salary;
    int ativo_inativo; //usado para indicar se o usuário ainda está no banco de dados ou se foi excluído (ainda está = ativo = 1, excluído = inativo = 0)
} registro;

void imprimir_busca(int a, char b[50], char c[50], char d, double e) { //imprime cada registro corretamente formatado, chamado sob comando de busca
    printf("{\n    \"id\": %d,\n", a);
    printf("    \"login\": \"%s\",\n", b);
    printf("    \"password\": \"%s\",\n", c);
    printf("    \"gender\": \"%c\",\n", d);
    printf("    \"salary\": %.2lf\n}\n", e);
};

int main() {

    registro *pessoas; //ponteiro para a struct registro, que será alocado dinamicamente
    pessoas = (registro *)malloc(1000 * sizeof(registro)); //alocação dinâmica de memória para cada pessoa do registro

    for(int y = 0; y < 1000; y++) {
        pessoas[y].ativo_inativo = 0; //inicializa todos os registros como inativos
    }

    char nome_arquivo[30];
    scanf(" %29s", nome_arquivo); //string que armazena o nome do arquvio, lido do teclado, que será aberto

    FILE *f;
    if((f = fopen(nome_arquivo, "r")) == NULL) { //abertura do arquivo lido acima em modo de leitura em texto, com nome 'f' 
        printf("Arquivo %s não foi encontrado.\n", nome_arquivo); //falha na abertura do arquivo emite mensagem de erro...
        free(pessoas); //desaloca a memória para evitar vazamentos...
        return 1; //e encerra o programa
    }

    char c;
    int n_registros = 0;
    while((c = fgetc(f)) != EOF) { //conta a quantidade de registros lidos
        if(c == '{') {
            n_registros++;
        }
    }
    for(int y = 0; y < 1000; y++) {
        pessoas[y].ativo_inativo = 0; //inicializa todos os registros como inativos
    }
    printf("%d registro(s) lido(s).\n", n_registros); //informa a quantidade de registros lidos do arquivo

    int i = 0;

    rewind(f); //rebobina f para realizar a leitura de cada campo do json

    char sentenca[300], lixo[15]; //variável 'sentenca' receberá cada linha do arquivo json como string; 'lixo' apenas consumirá texto prévio aos dados de cada registro

    //leitura do arquivo json
    while(fgets(sentenca, sizeof(sentenca), f) && i < 1000) { //garante que não sejam lidos mais do que 1000 registros
        if(strstr(sentenca, "\"id\"")) {
            sscanf(sentenca, "%[^:]: %d", lixo, &pessoas[i].id);
        } else if(strstr(sentenca, "\"login\"")) {
            sscanf(sentenca, "%[^:]: \"%49[^\"]\"", lixo, pessoas[i].login);
        } else if(strstr(sentenca, "\"password\"")) {                            //cada campo da struct recebe seu correspondente valor do arquivo json
            sscanf(sentenca, "%[^:]: \"%49[^\"]\"", lixo, pessoas[i].password);
        } else if(strstr(sentenca, "\"gender\"")) {
            sscanf(sentenca, "%[^:]: \"%c\"", lixo, &pessoas[i].gender);
        } else if(strstr(sentenca, "\"salary\"")) {
            sscanf(sentenca, "%[^:]: %lf", lixo, &pessoas[i].salary);
        } else if(strstr(sentenca, "}")) {
            pessoas[i].ativo_inativo = 1; //inicializa cada pessoa como ativa
            i++; //incrementa o contador i ao final de cada registro para que cada pessoa tenha um índice diferente no vetor 
        }
    }
    
    fclose(f); //fecha o arquivo 'f' que não terá mais uso

    i = n_registros; //seta i para o número de registros, índice que poderá ser utilizado no caso de uma inserção 

    int comando; //determinará se será feita uma inserção, uma busca ou uma remoção
    char dado[100]; //pode ser "id", "login", "password", "gender" ou "salary"... caso seja diferente de algum desses, será emitida uma mensagem de erro
    while (scanf("%d", &comando) == 1) { //loop que continuará até o fim do arquivo de entrada
        if(comando == 1) { //bloco de inserção
            int cont_insert = 0; //contador que denunciará se houve ou não inserção de registros
            for(int x = 0; x < 1000; x++) {
                if(pessoas[x].ativo_inativo == 0) {
                    scanf("%d \"%49[^\"]\" \"%49[^\"]\" \"%c\" %lf", &pessoas[x].id, pessoas[x].login, pessoas[x].password, &pessoas[x].gender, &pessoas[x].salary); //cada campo recebe o valor informado pelo teclado
                    pessoas[x].ativo_inativo = 1; //inicializa este registro como ativo
                    printf("Registro inserido.\n");
                    i++;
                    cont_insert++;
                    break; //caso seja possível realizar a inserção, sai do 'for' para evitar registros repetidos
                }
            }
            if(cont_insert == 0) { //caso não tenha sido possível realizar a inserção, emite mensagem de erro
                int id_lixo;
                char login_lixo[50], password_lixo[50], gender_lixo; //cria variáveis de lixo para consumir os dados que não serão utilizados
                double salary_lixo;
                scanf("%d \"%49[^\"]\" \"%49[^\"]\" \"%c\" %lf", &id_lixo, login_lixo, password_lixo, &gender_lixo, &salary_lixo); //dados inúteis são atribuídas às variáveis de lixo para realizar a limpeza do buffer
                printf("Sem espaço para inserção.\n");
            }
        } else if(comando == 2) { //bloco de busca
            int id_busca, cont_busca = 0; //contador que denunciará se foi encontrado, ou não, registro equivalente
            char login_busca[50], password_busca[50], gender_busca; //cria variáveis de comparação para a realização da busca de semelhantes
            double salary_busca;
            scanf("%99s", dado);
            if(strcmp(dado, "\"id\"") == 0) { 
                scanf("%d", &id_busca); //se dado = "id", comparará o id de cada pessoa com o id de comparação 'id_busca'
                for(int x = 0; x < i; x++) {
                    if(pessoas[x].id == id_busca && pessoas[x].ativo_inativo == 1) {
                        imprimir_busca(pessoas[x].id, pessoas[x].login, pessoas[x].password, pessoas[x].gender, pessoas[x].salary); //caso haja alguma equivalência, imprime o registro das pessoas encontradas
                        cont_busca++; //contador usado para indicar se foi encontrada alguma equivalência ou não (cont_busca > 0 -> encontrou, cont_busca = 0 -> nada encontrado)
                    }
                }
                if(cont_busca == 0) {
                    printf("Nada encontrado.\n");
                } 
            } else if(strcmp(dado, "\"login\"") == 0) {
                scanf(" \"%49[^\"]\"", login_busca); //faz o mesmo que acima, porém para 'login'
                for(int x = 0; x < i; x++) {
                    if((strcmp(pessoas[x].login, login_busca) == 0) && pessoas[x].ativo_inativo == 1) {
                        imprimir_busca(pessoas[x].id, pessoas[x].login, pessoas[x].password, pessoas[x].gender, pessoas[x].salary);
                        cont_busca++;
                    }
                }
                if(cont_busca == 0) {
                    printf("Nada encontrado.\n");
                } 
            } else if(strcmp(dado, "\"password\"") == 0) {
                scanf(" \"%49[^\"]\"", password_busca); //faz o mesmo que acima, porém para 'password'
                for(int x = 0; x < i; x++) {
                    if((strcmp(pessoas[x].password, password_busca) == 0) && pessoas[x].ativo_inativo == 1) {
                        imprimir_busca(pessoas[x].id, pessoas[x].login, pessoas[x].password, pessoas[x].gender, pessoas[x].salary);
                        cont_busca++;
                    }
                }
                if(cont_busca == 0) {
                    printf("Nada encontrado.\n");
                } 
            } else if(strcmp(dado, "\"gender\"") == 0) {
                scanf(" \"%c\"", &gender_busca); //faz o mesmo que acima, porém para 'gender'
                for(int x = 0; x < i; x++) {
                    if(pessoas[x].gender == gender_busca && pessoas[x].ativo_inativo == 1) {
                        imprimir_busca(pessoas[x].id, pessoas[x].login, pessoas[x].password, pessoas[x].gender, pessoas[x].salary);
                        cont_busca++;
                    }
                }
                if(cont_busca == 0) {
                    printf("Nada encontrado.\n");
                } 
            } else if(strcmp(dado, "\"salary\"") == 0) {
                scanf("%lf", &salary_busca); //faz o mesmo que acima, porém para 'salary'
                for(int x = 0; x < i; x++) {
                    if(pessoas[x].salary == salary_busca && pessoas[x].ativo_inativo == 1) {
                        imprimir_busca(pessoas[x].id, pessoas[x].login, pessoas[x].password, pessoas[x].gender, pessoas[x].salary);
                        cont_busca++;
                    }
                }
                if(cont_busca == 0) {
                    printf("Nada encontrado.\n");
                } 
            } else {
                char dado_lixo[100]; //caso 'dado' seja diferente de algum dos campos do registro ("id", "login", "password", "gender", "salary"), cria uma variável de lixo para consumir o dado inválido
                scanf(" %99s", dado_lixo);
                int ch;
                while ((ch = getchar()) != '\n' && ch != EOF); // consome até fim da linha para não deixar lixo no buffer
                printf("Nada encontrado.\n");
            }
        } else if(comando == 3) { //bloco de remoção
            int id_delete, cont_delete = 0;
            char login_delete[50], password_delete[50], gender_delete; //cria variáveis de comparação para a realização da remoção de semelhantes
            double salary_delete;
            scanf("%99s", dado);
            if(strcmp(dado, "\"id\"") == 0) {
                scanf("%d", &id_delete); //se dado = "id", comparará o id de cada pessoa com o id de comparação 'id_delete'
                for(int x = 0; x < i; x++) {
                    if(pessoas[x].id == id_delete && pessoas[x].ativo_inativo == 1) { //caso o id da pessoas seja igual ao id de comparação, será feita a sua remoção
                        pessoas[x].ativo_inativo = 0; //inativa o registro da pessoa que possui o id equivalente ao id de comparação
                        cont_delete++; //armazena a quantidade de registros que serão removidos
                    }
                }
                if(cont_delete > 0) {
                    printf("%d registro(s) removido(s).\n", cont_delete); //informa a quantidade de registros removidos
                } else {
                    printf("Remoção inválida.\n"); //caso cont_delete = 0, não houve nenhuma remoção
                }
            } else if(strcmp(dado, "\"login\"") == 0) {
                scanf(" \"%49[^\"]\"", login_delete); //faz o mesmo que acima porém para 'login'
                for(int x = 0; x < i; x++) {
                    if((strcmp(pessoas[x].login, login_delete) == 0) && pessoas[x].ativo_inativo == 1) {
                        pessoas[x].ativo_inativo = 0;
                        cont_delete++;
                    }
                }
                if(cont_delete > 0) {
                    printf("%d registro(s) removido(s).\n", cont_delete);
                } else {
                    printf("Remoção inválida.\n");
                }
            } else if(strcmp(dado, "\"password\"") == 0) {
                scanf(" \"%49[^\"]\"", password_delete); //faz o mesmo que acima porém para 'password'
                for(int x = 0; x < i; x++) {
                    if((strcmp(pessoas[x].password, password_delete) == 0) && pessoas[x].ativo_inativo == 1) {
                        pessoas[x].ativo_inativo = 0;
                        cont_delete++;
                    }
                }
                if(cont_delete > 0) {
                    printf("%d registro(s) removido(s).\n", cont_delete);
                } else {
                    printf("Remoção inválida.\n");
                }
            } else if(strcmp(dado, "\"gender\"") == 0) {
                scanf(" \"%c\"", &gender_delete); //faz o mesmo que acima porém para 'gender'
                for(int x = 0; x < i; x++) {
                    if(pessoas[x].gender == gender_delete && pessoas[x].ativo_inativo == 1) {
                        pessoas[x].ativo_inativo = 0;
                        cont_delete++;
                    }
                }
                if(cont_delete > 0) {
                    printf("%d registro(s) removido(s).\n", cont_delete);
                } else {
                    printf("Remoção inválida.\n");
                }
            } else if(strcmp(dado, "\"salary\"") == 0) {
                scanf("%lf", &salary_delete); //faz o mesmo que acima porém para 'salary'
                for(int x = 0; x < i; x++) {
                    if(pessoas[x].salary == salary_delete && pessoas[x].ativo_inativo == 1) {
                        pessoas[x].ativo_inativo = 0;
                        cont_delete++;
                    }
                }
                if(cont_delete > 0) {
                    printf("%d registro(s) removido(s).\n", cont_delete);
                } else {
                    printf("Remoção inválida.\n");
                }
            } else {
                char dado_lixo[100]; //caso 'dado' seja diferente de algum dos campos do registro ("id", "login", "password", "gender", "salary"), cria uma variável de lixo para consumir o texto inválido
                int ch;
                scanf(" %99s", dado_lixo); // consome texto inválido e armazena em dado_lixo
                while ((ch = getchar()) != '\n' && ch != EOF); // consome até o fim da linha para não deixar lixo no buffer
                printf("Remoção inválida.\n");
            }
        }
    }
    free(pessoas); //libera memória de pessoas, evitando assim vazamentos
    return 0;
}
