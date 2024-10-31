// TAD lista de números inteiros
// Carlos Maziero - DINF/UFPR, Out 2024
//
// Implementação do TAD - a completar
//
// Implementação com lista encadeada dupla não-circular
#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

struct lista_t *lista_cria()
{
    struct lista_t *lst;

    if (!(lst = malloc(sizeof(struct lista_t))))
        return NULL;

    lst->prim = NULL;
    lst->ult = NULL;
    lst->tamanho = 0;

    return lst;
}

/*função que cria um item, retorna o item ou NUll se erro*/
struct item_t *item_cria(int valor)
{
    struct item_t *novo_item;

    if (!(novo_item = malloc(sizeof(struct item_t))))
        return NULL;

    novo_item->ant = NULL;
    novo_item->prox = NULL;
    novo_item->valor = valor;

    return novo_item;
}

/*função que destroi o item*/
void item_destroi(struct item_t *item)
{
    if (!item)
        return;

    free(item);
    item = NULL;
}

struct lista_t *lista_destroi(struct lista_t *lst)
{
    if (!lst)
        return NULL;

    /*deixa a lista somente com um elemento*/
    while (lst->prim != lst->ult)
    {
        lst->ult = lst->ult->ant;
        item_destroi(lst->ult->prox);
    }
    item_destroi(lst->prim);
    free(lst);
    lst = NULL;

    return lst;
}

int lista_insere(struct lista_t *lst, int item, int pos)
{
    struct item_t *novo_item, *aux;
    int i;

    if (!lst)
        return -1;

    if (!(novo_item = item_cria(item)))
        return -1;

    /*se a lista estiver vazia*/
    if (!lst->prim)
    {
        lst->prim = novo_item;
        lst->ult = novo_item;
    }
    /*insere no fim da lista*/
    else if (pos < 0 || pos > lst->tamanho)
    {
        novo_item->ant = lst->ult;
        lst->ult->prox = novo_item;
        lst->ult = novo_item;
    }
    /*insere conforme a posição dada*/
    else
    {
        aux = lst->prim;
        for (i = 0; i < pos; i++)
            aux = aux->prox;

        novo_item->prox = aux;
        novo_item->ant = aux->ant;

        /*a ordem importa*/
        aux->ant->prox = novo_item;
        aux->ant = novo_item;
    }

    return (lst->tamanho + 1);
}

int lista_retira(struct lista_t *lst, int *item, int pos)
{
    struct item_t *aux;
    int i;

    if (!lst && !item)
        return -1;

    /*remove se tem um elemento*/
    if (lst->tamanho == 1)
    {
        item_destroi(lst->prim);
        lst->prim = NULL;
        lst->ult = NULL;
    }
    /*remove no fim da lista*/
    else if (pos < 0 || pos > lst->tamanho)
    {
        /*aponto o lst->ult pro anterior e destruo ultimo*/
        lst->ult = lst->ult->ant;
        item_destroi(lst->ult->prox);
        lst->ult->prox = NULL;
    }
    /*remove conforme posição dada*/
    else
    {
        aux = lst->prim;
        for (i = 0; i < pos; i++)
            aux = aux->prox;

        /*reapontamentos de itens*/
        aux->ant->prox = aux->prox;
        aux->prox->ant = aux->ant;

        item_destroi(aux);
    }

    return (lst->tamanho - 1);
}

int lista_consulta(struct lista_t *lst, int *item, int pos)
{
    struct item_t *aux;
    int i;

    if (!lst && !item)
        return -1;

    /* se a lista estiver vazia*/
    if (!lst->prim)
        return -1;

    /*consulta no fim da lista*/
    if (pos < 0)
    {
        aux = lst->ult;
    }
    /*consulta conforme posição dada*/
    else
    {
        aux = lst->prim;
        for (i = 0; i <= pos; i++)
            aux = aux->prox;
    }

    /*informo o valor do item consultado*/
    *item = aux->valor;

    return lst->tamanho;
}

int lista_procura(struct lista_t *lst, int valor)
{
    struct item_t *aux;

    if (!lst)
        return -1;

    /*se lista vazia sai*/
    if (!lst->prim)
        return -1;

    /*procura a partir do inicio da lista comparando o valor*/
    else
    {
        aux = lst->prim;
        aux->valor = valor;

        while (!aux || aux->valor != valor)
            aux = aux->prox;
    }

    if (aux != NULL)
        return /*posição*/;
    else
        return -1;
}

int lista_tamanho(struct lista_t *lst)
{
    if (!lst)
        return -1;

    return lst->tamanho;
}

void lista_imprime(struct lista_t *lst)
{
    struct item_t *aux;
    int i;

    aux = lst->prim;
    for (i = 0; i < lst->tamanho; i++)
    {
        printf("%d", aux->valor);
        printf(" ");
        aux = aux->prox;
    }
}