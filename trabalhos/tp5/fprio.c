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
    struct fpnodo_t *aux_ant, *aux_prox;

    if (!f)
        return NULL;

    /*destroi se tiver um elemento*/
    if (f->num == 1)
        fpnodo_destroi(f->prim);
    /*destroi se a lista for maior que 1*/
    else if (f->num > 1)
    {
        aux_ant = f->prim;
        aux_prox = f->prim->prox;

        while (aux_prox != NULL)
        {
            fpnodo_destroi(aux_ant);
            aux_ant = aux_prox;
            aux_prox = aux_prox->prox;
        }
        fpnodo_destroi(aux_ant);
    }

    free(f);
    f = NULL;

    return NULL;
}

int fpnodo_compara(struct fpnodo_t *nodo1, struct fpnodo_t *nodo2)
{
    if (!nodo1 || !nodo2)
        return 0;

    /*compara se os dois nodos são exatamente iguais*/
    if (nodo1->item == nodo2->item && nodo1->tipo == nodo2->tipo && nodo1->prio == nodo2->prio)
        return 1;

    return 0;
}

int fprio_insere(struct fprio_t *f, void *item, int tipo, int prio)
{
    struct fpnodo_t *novo_nodo, *aux_ant, *aux_prox;

    if (!f || !item)
        return -1;

    novo_nodo = fpnodo_cria(item, tipo, prio);
    if (!novo_nodo)
        return -1;

    /*se a fila estiver vazia*/
    if (!f->num)
        f->prim = novo_nodo;

    /*se tiver a prioridade igual insere conforme FIFO*/
    else if (novo_nodo->prio == f->prim->prio)
    {
        if (fpnodo_compara(novo_nodo, f->prim))
        {
            fpnodo_destroi(novo_nodo);
            return -1;
        }
        novo_nodo->prox = f->prim->prox;
        f->prim->prox = novo_nodo;
    }

    /*insere elemento com prioridade maior no inicio da fila*/
    else if (novo_nodo->prio < f->prim->prio)
    {
        novo_nodo->prox = f->prim;
        f->prim = novo_nodo;
    }
    /*insere com prioridade menor e compara se tem elementos iguais*/
    else
    {
        aux_ant = f->prim;
        aux_prox = f->prim->prox;
        while (aux_prox != NULL && novo_nodo->prio >= aux_prox->prio)
        {
            if (fpnodo_compara(novo_nodo, aux_ant))
            {
                fpnodo_destroi(novo_nodo);
                return -1;
            }

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
    struct fpnodo_t *aux;
    void *salva_item;

    if (!f || !tipo || !prio)
        return NULL;

    if (!f->num)
        return NULL;

    /*retira da lista*/
    aux = f->prim;
    f->prim = f->prim->prox;
    f->num--;

    /*devolve os parametros*/
    *tipo = aux->tipo;
    *prio = aux->prio;

    /*salvo item no ponteiro tipo void para retornar
    pra fora da função*/
    salva_item = aux->item;
    fpnodo_destroi(aux);

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

    if (!f)
        return;

    aux = f->prim;
    while (aux != NULL)
    {
        printf("(");
        printf("%d %d", aux->tipo, aux->prio);
        printf(")");

        /*condição para não dar espaço no final da fila*/
        if (aux->prox)
            printf(" ");

        aux = aux->prox;
    }
}