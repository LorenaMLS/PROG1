// TAD Fila de prioridades (FPRIO) genérica
// Lorena Moreira Leite Dos Santos, GRR:20221244
// Implementação com lista encadeada simples

#include <stdio.h>
#include <stdlib.h>
#include "fprio.h"

struct fprio_t *fprio_cria()
{
    struct fprio_t *fila;

    if (!(fila = malloc(sizeof(struct fprio_t))))
        return NULL;

    fila->prim = NULL;
    fila->fim = NULL;
    fila->num = 0;

    return fila;
}

struct fpnodo_t *fpnodo_cria(void *item, int tipo, int prio)
{
    struct fpnodo_t *nodo;

    if (!(nodo = malloc(sizeof(struct fpnodo_t))))
        return NULL;

    nodo->prox = NULL;
    nodo->item = item;
    nodo->prio = prio;
    nodo->tipo = tipo;

    return nodo;
}

struct fpnodo_t *fpnodo_destroi(struct fpnodo_t *nodo)
{
    if (!nodo)
        return NULL;

    free(nodo);
    nodo = NULL;

    return NULL;
}

struct fprio_t *fprio_destroi(struct fprio_t *f)
{
    struct fpnodo_t *aux;

    if (!f)
        return NULL;

    while (f->prim != NULL)
    {
        aux = f->prim;
        f->prim = aux->prox;

        /* libera o item antes de destruir o nodo */
        if (aux->item)
            free(aux->item);

        fpnodo_destroi(aux);
    }

    free(f);
    return NULL;
}

int fprio_insere(struct fprio_t *f, void *item, int tipo, int prio)
{
    struct fpnodo_t *novo_nodo, *aux_ant, *aux_prox;

    if (!f || !item)
        return -1;

    novo_nodo = fpnodo_cria(item, tipo, prio);
    if (!novo_nodo)
        return -1;

    /*insere na fila vazia*/
    if (!f->prim)
    {
        f->prim = novo_nodo;
        f->fim = novo_nodo;
        f->num++;
        return f->num;
    }

    aux_ant = NULL;
    aux_prox = f->prim;

    while (aux_prox && prio >= aux_prox->prio)
    {
        /*evita duplicatas*/
        if (item == aux_prox->item && tipo == aux_prox->tipo && prio == aux_prox->prio)
        {
            fpnodo_destroi(novo_nodo);
            return -1;
        }

        aux_ant = aux_prox;
        aux_prox = aux_prox->prox;
    }

    if (!aux_ant)
    {
        /*insere no início*/
        novo_nodo->prox = f->prim;
        f->prim = novo_nodo;
    }
    else
    {
        novo_nodo->prox = aux_prox;
        aux_ant->prox = novo_nodo;
    }

    if (!novo_nodo->prox)
        f->fim = novo_nodo;

    f->num++;
    return f->num;
}

void *fprio_retira(struct fprio_t *f, int *tipo, int *prio)
{
    struct fpnodo_t *aux;
    void *salva_item;

    if (!f || !tipo || !prio)
        return NULL;

    if (!f->num)
        return NULL;

    /*retira da fila*/
    aux = f->prim;
    f->prim = f->prim->prox;

    if (!f->prim)
        f->fim = NULL;

    /*devolve os parametros*/
    *tipo = aux->tipo;
    *prio = aux->prio;

    /*salvo item no ponteiro tipo void para retornar
    pra fora da função*/
    salva_item = aux->item;
    fpnodo_destroi(aux);
    f->num--;

    return salva_item;
}

int fprio_tamanho(struct fprio_t *f)
{
    if (!f)
        return -1;

    return f->num;
}

void fprio_imprime(struct fprio_t *f)
{
    struct fpnodo_t *aux;

    if (!f || !f->prim)
        return;

    /*imprime até o penultimo elemento*/
    aux = f->prim;
    while (aux && aux->prox)
    {
        printf("(%d %d) ", aux->tipo, aux->prio);
        aux = aux->prox;
    }
    /*imprime o ultimo sem espaço*/
    printf("(%d %d)", aux->tipo, aux->prio);
}
