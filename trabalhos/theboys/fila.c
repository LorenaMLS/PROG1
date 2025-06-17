// TAD Fila

#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

struct fila_t *fila_cria()
{
    struct fila_t *fila;

    if (!(fila = malloc(sizeof(struct fila_t))))
        return NULL;

    fila->prim = NULL;
    fila->fim = NULL;
    fila->num = 0;

    return fila;
}

struct fila_nodo_t *nodo_cria(void *item)
{
    struct fila_nodo_t *nodo;

    if (!(nodo = malloc(sizeof(struct fila_nodo_t))))
        return NULL;

    nodo->item = item;
    nodo->prox = NULL;

    return nodo;
}
struct fila_nodo_t *nodo_destroi(struct fila_nodo_t *nodo)
{
    if (!nodo)
        return NULL;

    free(nodo);
    nodo = NULL;

    return nodo;
}

struct fila_t *fila_destroi(struct fila_t *f)
{
    struct fila_nodo_t *aux;

    if (!f)
        return NULL;

    /*destroi com um elemento*/
    if (f->num == 1)
    {
        nodo_destroi(f->prim);
        free(f);
        f = NULL;
        return NULL;
    }

    while (f->prim != f->fim)
    {
        aux = f->prim;
        f->prim = aux->prox;
        nodo_destroi(aux);
    }
    fila_destroi(f->fim);

    free(f);
    f = NULL;
    return NULL;
}

int fila_insere(struct fila_t *f, void *item)
{
    struct fila_nodo_t *novo_nodo, *aux;

    if (!f || !item)
        return -1;

    novo_nodo = nodo_cria(item);

    /*verifica se o item já está na fila*/
    aux = f->prim;
    while (aux != NULL) 
    {
        if (aux->item == item)
            return -1;

        aux = aux->prox;
    }

    /*insere caso fila vazia*/
    if (!f->num)
    {
        f->prim = novo_nodo;
        f->fim = novo_nodo;
    }
    /*insere no final da fila*/
    else
    {
        f->fim->prox = novo_nodo;
        f->fim = novo_nodo;
    }

    f->num++;
    return fila_tamanho(f);
}

void *fila_retira (struct fila_t *f)
{
    if (!f)
        return -1;

    
}

int fila_tamanho (struct fila_t *f)
{
    if (!f)
        return -1;

    return f->num;
}