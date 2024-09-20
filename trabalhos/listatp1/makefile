# Makefile de exemplo (Manual do GNU Make)
     
CFLAGS = -Wall -Werror -Wextra -std=c90 -g  # flags de compilacao
LDFLAGS = -lm

CC = gcc

# arquivos-objeto
	objects = teste_liblista_ordenada.o liblista_ordenada.o 
     
all: teste_liblista_ordenada.o liblista_ordenada.o
	$(CC) -o lista teste_liblista_ordenada.o liblista_ordenada.o $(LDFLAGS)

liblista_ordenada.o: liblista_ordenada.c
	$(CC) -c $(CFLAGS) liblista_ordenada.c

teste_liblista_ordenada.o: teste_liblista_ordenada.c
	$(CC) -c $(CFLAGS) teste_liblista_ordenada.c

clean:
	rm -f $(objects) lista


