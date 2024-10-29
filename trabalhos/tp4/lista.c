// TAD lista de números inteiros
// Carlos Maziero - DINF/UFPR, Out 2024
//
// Implementação do TAD - a completar
//
// Implementação com lista encadeada dupla não-circular
#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

struct lista_t *lista_cria ()
{
    struct lista_t *lst;

    if (!(lst = malloc(sizeof(struct lista_t))))
        return NULL;
    
    lst->prim = NULL;
    lst->ult = NULL;
    lst->tamanho = 0;

    return lst;
}

struct lista_t *lista_destroi (struct lista_t *lst)
{
    struct lista_t *aux;

    while (lst->prim != NULL)
    {
        aux->prim = lst->prim;
        lst->prim = lst->prim->prox;
        free (aux);
        lst->tamanho--;
    }

    lst->ult = NULL;
    free(lst);
    lst = NULL;

    return NULL; /*não tenho ctz*/
}

int lista_insere (struct lista_t *lst, int item, int pos)
{
    
}

int lista_retira (struct lista_t *lst, int *item, int pos)
{
    struct lista_t *aux;

    if (pos == -1)
    {

    }
    else
    {
        aux = lista_procura(lst, item);
        aux->ult = aux->ult->prox->prox;
        free(aux);
        lst->tamanho--;
    }
}
