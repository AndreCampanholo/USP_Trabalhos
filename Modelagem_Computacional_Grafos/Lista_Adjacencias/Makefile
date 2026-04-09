CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
TARGET = graph
SOURCES = main.c graph_lista_adj.c lista_encadeada.c

all: $(TARGET).exe

$(TARGET).exe: $(SOURCES)
	$(CC) $(CFLAGS) -I. $(SOURCES) -o $(TARGET).exe

run: $(TARGET).exe
	./$(TARGET).exe

clean:
	if exist $(TARGET).exe del /f /q $(TARGET).exe

.PHONY: all run clean