// TAD Fila de prioridades (FPRIO) genérica
// Carlos Maziero, DINF/UFPR, Out 2024
// Implementação com lista encadeada simples

// A COMPLETAR
#include <stdio.h>
#include <stdlib.h>
#include "fprio.h"

struct fprio_t *fprio_cria ()
{
    struct fprio_t *fila;

    if(!(fila = malloc(sizeof(struct fprio_t))))
        return NULL;
    
    fila->prim = NULL;
    fila->num = 0;

    return fila;
}

struct fpnodo_t *fpnodo_cria ()
{
    struct fpnodo_t *nodo;

    if(!(nodo = malloc(sizeof(struct fpnodo_t))))
        return NULL;
    
    nodo->prox = NULL;
    nodo->item = NULL;
    nodo->prio = 0;
    nodo->tipo = 0;

    return nodo;
}