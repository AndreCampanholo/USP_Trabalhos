# Makefile for Sistema Hospitalar V2
# Compatible with Cygwin

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic -g
TARGET = sistema_hospitalar.exe
OBJ_DIR = Objects

# Source directories
SRCDIR_ARVORE = Arvore_Binaria
SRCDIR_FILA = Fila_Prioridade
SRCDIR_PILHA = Pilha_Encadeada
SRCDIR_PACIENTE = TAD_Paciente
SRCDIR_FUNCTIONS = TAD_functions
SRCDIR_IO = TAD_IO

# Source files
SOURCES = main.c \
          $(SRCDIR_ARVORE)/arvore.c \
          $(SRCDIR_FILA)/fila_prioridade.c \
          $(SRCDIR_PILHA)/pilha.c \
          $(SRCDIR_PACIENTE)/paciente.c \
          $(SRCDIR_FUNCTIONS)/functions.c \
          $(SRCDIR_IO)/IO.c

# Object files
OBJECTS = $(SOURCES:%.c=$(OBJ_DIR)/%.o)

# Header files
HEADERS = $(SRCDIR_ARVORE)/arvore.h \
          $(SRCDIR_FILA)/fila_prioridade.h \
          $(SRCDIR_PILHA)/pilha.h \
          $(SRCDIR_PACIENTE)/paciente.h \
          $(SRCDIR_FUNCTIONS)/functions.h \
          $(SRCDIR_IO)/IO.h

# Default target
all: $(TARGET)

# Link executable
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)
    @echo "Build successful! Run with: ./$(TARGET)"

# Compile source files to object files
$(OBJ_DIR)/%.o: %.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Debug build
debug: CFLAGS += -DDEBUG -O0
debug: clean $(TARGET)

# Release build
release: CFLAGS += -O2 -DNDEBUG
release: clean $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Clean build files
clean:
	rm -rf $(OBJ_DIR) $(TARGET)
	@echo "Clean complete."

# Show project info
info:
	@echo "=== Sistema Hospitalar V2 ==="
    @echo "Compiler: $(CC)"
    @echo "Flags: $(CFLAGS)"
    @echo "Target: $(TARGET)"
    @echo "Sources: $(words $(SOURCES)) files"

# Help
help:
    @echo "Available targets:"
	@echo "  make         - Build the project"
	@echo "  make debug   - Build with debug symbols"
	@echo "  make release - Build optimized version"
	@echo "  make run     - Build and run"
	@echo "  make clean   - Remove build files"
	@echo "  make info    - Show project info"
	@echo "  make help    - Show this help"

.PHONY: all debug release run clean info help