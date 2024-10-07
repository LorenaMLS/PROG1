# Makefile de exemplo (Manual do GNU Make)

CFLAGS = -Wall -Wextra -g -std=c99 # flags de compilacao
CC = gcc
TP = tp2

# gera o executável
all: $(TP).o racional.o
	$(CC) -o $(TP) $(TP).o racional.o

# compila racional.c
racional.o: racional.c racional.h
	$(CC) -c $(CFLAGS) racional.c

# compila tp2.c
$(TP).o: $(TP).c racional.h
	$(CC) -c $(CFLAGS) $(TP).c

# git resumido
git:
	make clean; git add .; git commit -m "$(c)"; git push

# apaga, recompila e executa
ll:
	make clean; clear; make; ./$(TP)

clean:
	rm -f *.o *~ $(TP)

# Define uma variável de comentário padrão
c ?= "[git]subiu pelo make"
