#include <stdlib.h>
#include "liblista_ordenada.h"

lista_t *lista_cria()
{

    lista_t *l;

    if (!(l = malloc(sizeof(lista_t))))
        return NULL;

    l->ini = NULL;

    return l;
}


void lista_destroi(lista_t **l)
{
    nodo_t *aux;

    while ((*l)->ini != NULL){
        aux = (*l)->ini;
        (*l)->ini = aux->prox;
        free (aux->elemento);
        free (aux);
    }
    free (*l);
    *l = NULL;
}


int lista_insere_ordenado(lista_t *l, elemento_t *elemento)
{
    nodo_t *novo, *aux;

    if (!(novo = malloc(sizeof(nodo_t))))
        return 0;

    novo->elemento = elemento;

    /*caso 1 lista vazia*/
    if (l->ini == NULL){
        l->ini = novo;
        novo->prox = NULL;
        return 1;
    }

    /*se o elemento for menor que o primeiro da lista*/
    if (novo->elemento->chave < (l->ini)->elemento->chave){
        novo->prox = l->ini;
        l->ini = novo;
        return 1;
    }

    aux = l->ini;
    while (aux->prox != NULL && novo->elemento->chave > aux->prox->elemento->chave){
        aux = aux->prox;
    }

    novo->prox = aux->prox;
    aux->prox = novo;
    return 1;
}


int lista_remove_ordenado(lista_t *l, elemento_t *elemento)
{
    nodo_t *aux, *temp;

    if (l->ini == NULL)
        return 0;

    /* se o elemento for o primeiro da lista */
    if (l->ini->elemento->chave == elemento->chave){
        aux = l->ini;
        l->ini = aux->prox;
        free (aux->elemento);
        free (aux);
        return 1;
    }

    aux = l->ini;
    while (aux->prox != NULL && aux->prox->elemento->chave != elemento->chave){
        aux = aux->prox;
    }

    /* se o elemento não estiver na lista*/
    if (aux->prox == NULL)
        return 0;

    temp = aux->prox;
    aux->prox = temp->prox;
    free (temp->elemento);
    free (temp);
    return 1;
}
