// TAD Fila genérica
// Lorena Moreira Leite Dos Santos, GRR:20221244
// Implementação com lista encadeada simples

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

    while (f->prim != NULL)
    {
        aux = f->prim;
        f->prim = aux->prox;
        nodo_destroi(aux);
    }

    free(f);
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

void *fila_retira(struct fila_t *f)
{
    struct fila_nodo_t *aux;
    void *item;

    if (!f || !f->num || f->prim == NULL)
        return NULL;

    /*salva o ponteiro*/
    aux = f->prim;
    item = aux->item;        

    /*retira da fila*/
    f->prim = aux->prox;
    nodo_destroi(aux);
    f->num--;

    return item;
}


int fila_tamanho(struct fila_t *f)
{
    if (!f)
        return -1;

    return f->num;
}

void fila_imprime(struct fila_t *f)
{
    struct fila_nodo_t *atual;
    int *valor;

    if (!f || f->num == 0)
        return;

    atual = f->prim;
    while (atual)
    {
        valor = (int *)atual->item;
        printf(" %d", *valor);
        atual = atual->prox;
    }
}

