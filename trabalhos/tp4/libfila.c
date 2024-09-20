#include <stdlib.h>
#include "libfila.h"


fila_t *fila_cria (){
    fila_t *nova_fila;

    if(!(nova_fila = malloc(sizeof(fila_t))))
        return NULL;

    nova_fila->cabeca = NULL;
    nova_fila->cauda = NULL;
    nova_fila->tamanho = 0; 

    return nova_fila;
}


void fila_destroi (fila_t **fila){
nodo_t *nodo;

    while ((*fila)->cabeca){
        nodo = (*fila)->cabeca;
        (*fila)->cabeca = (*fila)->cabeca->prox;
        free (nodo);
    }
    nodo = NULL;
    free(*fila);
    *fila = NULL;
}



int enqueue (fila_t *fila, int dado){
    nodo_t *novo;

    if(!(novo = malloc(sizeof(nodo_t))))
        return 0;

    novo->dado = dado;
    novo->prox = NULL;
    fila->tamanho++;
    

    /*se a fila estiver vazia o inicio e o fim apontam pra null
    temos que apontar os dois para o novo nó*/
    if (fila_vazia(fila)){

        fila->cabeca = novo;
        fila->cauda = novo;
        return 1;
    }

    fila->cauda->prox = novo;
    fila->cauda = novo;
    return 1;
}


int dequeue (fila_t *fila, int *dado){
    nodo_t *aux;

    if (fila_vazia(fila))
        return 0;
        
    aux = fila->cabeca;
    fila->cabeca = (fila->cabeca)->prox;
    *dado = aux->dado;
    fila->tamanho--;

    free(aux);
    aux = NULL;
    return 1;
}


int fila_tamanho (fila_t *fila){

    return fila->tamanho;
}


int fila_vazia (fila_t *fila){
 if (fila->cabeca != NULL && fila->cauda != NULL)
        return 0;
    
    return 1;
}