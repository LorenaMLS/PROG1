# Makefile de exemplo (Manual do GNU Make)
     
CFLAGS = -Wall -Werror -Wextra -std=c90 -g  # flags de compilacao
LDFLAGS = -lm

CC = gcc

# arquivos-objeto
	objects = teste_liblista_circular.o liblista_circular.o 
     
all: teste_liblista_circular.o liblista_circular.o
	$(CC) -o listacircular teste_liblista_circular.o liblista_circular.o $(LDFLAGS)

liblista_circular.o: liblista_circular.c
	$(CC) -c $(CFLAGS) liblista_circular.c

teste_liblista_circular.o: teste_liblista_circular.c
	$(CC) -c $(CFLAGS) teste_liblista_circular.c

clean:
	rm -f $(objects) listacircular


