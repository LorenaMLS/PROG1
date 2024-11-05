// TAD Fila de prioridades (FPRIO) genérica
// Carlos Maziero, DINF/UFPR, Out 2024
// Implementação com lista encadeada simples

// A COMPLETAR
#include <stdio.h>
#include <stdlib.h>
#include "fprio.h"

struct fprio_t *fprio_cria()
{
    struct fprio_t *fila;

    if (!(fila = malloc(sizeof(struct fprio_t))))
        return NULL;

    fila->prim = NULL;
    fila->num = 0;

    return fila;
}

struct fpnodo_t *fpnodo_cria()
{
    struct fpnodo_t *nodo;

    if (!(nodo = malloc(sizeof(struct fpnodo_t))))
        return NULL;

    nodo->prox = NULL;
    nodo->item = NULL;
    nodo->prio = 0;
    nodo->tipo = 0;

    return nodo;
}

struct fpnodo_t *fpnodo_destroi(struct fpnodo_t *nodo)
{
    if (!nodo)
        return NULL;

    free(nodo->item);
    free(nodo);
    nodo = NULL;

    return NULL;
}

struct fprio_t *fprio_destroi(struct fprio_t *f)
{
    struct fpnodo_t *aux, *aux2;

    if (!f)
        return NULL;
    /*destroi se tiver um elemento*/
    if (f->num == 1)
        fpnodo_destroi(f->prim);
    /*destroi se a lista for maior que 1*/
    else if (f->num > 1)
    {
        aux = f->prim;
        aux2 = f->prim->prox;

        while (aux2 != NULL)
        {
            fpnodo_destroi(aux);
            aux = aux2;
            aux2 = aux2->prox;
        }
        fpnodo_destroi(aux);
    }

    free(f);
    f = NULL;

    return NULL;
}

/*função que atribui os valores para o novo nodo*/
int fpnodo_atribui(struct fpnodo_t *nodo, void *item, int tipo, int prio)
{
    if (!nodo || !item)
        return 0;

    nodo->item = item;
    nodo->tipo = tipo;
    nodo->prio = prio;

    return 1;
}

int fprio_insere(struct fprio_t *f, void *item, int tipo, int prio)
{
    struct fpnodo_t *novo_nodo, *aux_ant, *aux_prox;

    if (!f || !item)
        return -1;

    novo_nodo = fpnodo_cria();
    if (!fpnodo_atribui(novo_nodo, item, tipo, prio))
        return -1;

    /*se a fila estiver vazia*/
    if (!f->num)
        f->prim = novo_nodo;

    /*insere elemento com prioridade maior no inicio da fila*/
    else if (novo_nodo->prio < f->prim->prio)
    {
        novo_nodo->prox = f->prim;
        f->prim = novo_nodo;
    }
    else
    {
        aux_ant = f->prim;
        aux_prox = f->prim->prox;
        while (aux_prox != NULL && novo_nodo->prio >= aux_prox->prio)
        {
            aux_ant = aux_prox;
            aux_prox = aux_prox->prox;
        }
        novo_nodo->prox = aux_prox;
        aux_ant->prox = novo_nodo;
    }

    f->num++;

    return fprio_tamanho(f);
}

void *fprio_retira(struct fprio_t *f, int *tipo, int *prio)
{
    return NULL;
}

int fprio_tamanho(struct fprio_t *f)
{
    if (!f)
        return -1;
    
    return f->num;
}

void fprio_imprime(struct fprio_t *f)
{
}