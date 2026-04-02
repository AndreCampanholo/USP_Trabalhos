# Makefile para Sistema Hospitalar AED
# Projeto: Sistema de Atendimento Médico usando TADs em C

# Configurações do compilador
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic -g
TARGET = sistema_hospitalar
OBJ_DIR = Objects
DATA_DIR = Persistencia_Dados

# Arquivos fonte
SRCDIR_LISTA = Lista_Simples_Encadeada
SRCDIR_FILA = Fila_Encadeada
SRCDIR_PILHA = Pilha_Encadeada
SRCDIR_PACIENTE = TAD_Paciente
SRCDIR_FUNCTIONS = TAD_functions
SRCDIR_IO = TAD_IO

SOURCES = main.c \
          $(SRCDIR_LISTA)/lista.c \
          $(SRCDIR_FILA)/fila.c \
          $(SRCDIR_PILHA)/pilha.c \
          $(SRCDIR_PACIENTE)/paciente.c \
          $(SRCDIR_FUNCTIONS)/functions.c \
          $(SRCDIR_IO)/IO.c

# Arquivos objeto (convertendo .c para .o no diretório Objects/)
OBJECTS = $(SOURCES:%.c=$(OBJ_DIR)/%.o)

# Dependências de header
HEADERS = $(SRCDIR_LISTA)/lista.h \
          $(SRCDIR_FILA)/fila.h \
          $(SRCDIR_PILHA)/pilha.h \
          $(SRCDIR_PACIENTE)/paciente.h \
          $(SRCDIR_FUNCTIONS)/functions.h \
          $(SRCDIR_IO)/IO.h

# Regra principal
all: $(TARGET)

# Criação do executável
$(TARGET): $(OBJECTS) | $(DATA_DIR)
	$(CC) $(OBJECTS) -o $(TARGET)
	@echo "Sistema compilado com sucesso! Execute com: ./$(TARGET)"

# Regra genérica para compilar arquivos .c em .o
$(OBJ_DIR)/%.o: %.c $(HEADERS) | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Criar diretório de objetos se não existir
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/$(SRCDIR_LISTA)
	@mkdir -p $(OBJ_DIR)/$(SRCDIR_FILA)
	@mkdir -p $(OBJ_DIR)/$(SRCDIR_PILHA)
	@mkdir -p $(OBJ_DIR)/$(SRCDIR_PACIENTE)
	@mkdir -p $(OBJ_DIR)/$(SRCDIR_FUNCTIONS)
	@mkdir -p $(OBJ_DIR)/$(SRCDIR_IO)

# Criar diretório de dados se não existir
$(DATA_DIR):
	@mkdir -p $(DATA_DIR)
	@echo "Diretório de persistência de dados criado."

# Compilação com debug
debug: CFLAGS += -DDEBUG -O0
debug: $(TARGET)

# Compilação otimizada para release
release: CFLAGS += -O2 -DNDEBUG
release: clean $(TARGET)

# Executar o programa
run: $(TARGET)
	./$(TARGET)

# Limpeza de arquivos gerados
clean:
	-@rm -rf $(OBJ_DIR)
	-@rm -f $(TARGET).exe $(TARGET)
	@echo "Arquivos temporários removidos."

# Limpeza completa (inclui dados salvos)
clean-all: clean
	-@rm -rf $(DATA_DIR)
	@echo "Todos os arquivos gerados removidos."

# Mostrar informações do projeto
info:
	@echo "=== Sistema Hospitalar AED ==="
	@echo "Compilador: $(CC)"
	@echo "Flags: $(CFLAGS)"
	@echo "Executável: $(TARGET)"
	@echo "Arquivos fonte: $(words $(SOURCES)) arquivos"
	@echo "Diretórios: $(OBJ_DIR)/, $(DATA_DIR)/"

# Instalar dependências (caso necessário)
install-deps:
	@echo "Nenhuma dependência externa necessária."
	@echo "Sistema utiliza apenas bibliotecas padrão do C."

# Verificar se todos os arquivos fonte existem
check:
	@echo "Verificando arquivos fonte..."
	@$(foreach src,$(SOURCES),$(if $(wildcard $(src)),,$(error Arquivo não encontrado: $(src))))
	@echo "Todos os arquivos fonte estão presentes."

# Ajuda
help:
	@echo "=== Makefile do Sistema Hospitalar AED ==="
	@echo ""
	@echo "Comandos disponíveis:"
	@echo "  make         - Compila o projeto"
	@echo "  make all     - Compila o projeto (mesmo que make)"
	@echo "  make debug   - Compila com informações de debug"
	@echo "  make release - Compila otimizado para produção"
	@echo "  make run     - Compila e executa o programa"
	@echo "  make clean   - Remove arquivos objeto e executável"
	@echo "  make clean-all - Remove tudo (incluindo dados salvos)"
	@echo "  make info    - Mostra informações do projeto"
	@echo "  make check   - Verifica se todos os arquivos fonte existem"
	@echo "  make help    - Mostra esta ajuda"
	@echo ""
	@echo "Estrutura do projeto:"
	@echo "  $(TARGET)      - Executável principal"
	@echo "  $(OBJ_DIR)/         - Diretório de arquivos objeto"
	@echo "  $(DATA_DIR)/        - Diretório de persistência de dados"

# Declarar phony targets
.PHONY: all debug release run clean clean-all info install-deps check help