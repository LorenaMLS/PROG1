#include <stdlib.h>
#include "liblista_circular.h"


lista_t *lista_cria (){

    lista_t *l;
    nodo_t *sentinela;

    if (!(l = malloc(sizeof(lista_t))))
        return NULL;

    if (!(sentinela = malloc(sizeof(nodo_t))))
        return NULL;

    sentinela->elemento = NULL;
    sentinela->prox = sentinela;
    sentinela->prev = sentinela;
    l->ini = sentinela;

    return l;
}


void lista_destroi (lista_t **l){
    nodo_t *aux;

    while ((*l)->ini != NULL){
        aux = (*l)->ini->prox;
        (*l)->ini->prox = aux->prox;
        aux->prox->prev = (*l)->ini->prox;
        free (aux->elemento);
        free (aux);
    }

    free ((*l)->ini->elemento);
    free ((*l)->ini);
    free (*l);
    (*l) = NULL;
}


int lista_insere_ordenado (lista_t *l, elemento_t *elemento){

    nodo_t *novo, *aux;

    if (!(novo = malloc(sizeof(nodo_t))))
        return 0;
    
    novo->elemento = elemento;

    l->ini->elemento = elemento;
    aux = l->ini->prox;

    while (aux != l->ini && elemento->chave > aux->elemento->chave){
        aux = aux->prox;
    }
    
    novo->prev = aux;
    novo->prox = aux->prox;

    aux->prox->prev = novo;
    aux->prox = novo;
    return 1;
}


int lista_remove_ordenado (lista_t *l, elemento_t *elemento){
    nodo_t *aux;

    l->ini->elemento = elemento;
    aux = l->ini->prox;

    while (l->ini->elemento->chave != aux->elemento->chave){
        aux = aux->prox;
    }

    /*se não encontrou o elemento na lista*/
    if (l->ini->elemento->chave == aux->elemento->chave)
        return 0;

    aux->prox->prev = aux->prev;
    aux->prev->prox = aux->prox;
    free (aux->elemento);
    free (aux);

    return 1;

}
