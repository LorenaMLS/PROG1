// TAD lista de números inteiros
// Carlos Maziero - DINF/UFPR, Out 2024
//

#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

/*percorre lista e retorna um ponteiro na posição indicada*/
struct item_t *item_poteiro_pos(struct lista_t *lst, int pos)
{
    struct item_t *aux;

    if (!lst)
        return NULL;

    /*percorre lista e decrementa posição até achar elemento*/
    aux = lst->prim;
    while (aux != NULL && pos != 0)
    {
        aux = aux->prox;
        pos--;
    }

    /*retorna NULL caso não encontre*/
    return aux;
}

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

    if (!lst)
        return -1;

    if (!(novo_item = item_cria(item)))
        return -1;

    /*insere se lista vazia*/
    if (!lst->tamanho)
    {
        lst->prim = novo_item;
        lst->ult = novo_item;
    }
    /*insere no inicio na lista*/
    else if (!pos)
    {
        novo_item->prox = lst->prim;
        lst->prim->ant = novo_item;
        lst->prim = novo_item;
    }
    /*insere no final da lista*/
    else if (pos < 0 || pos > lst->tamanho)
    {
        novo_item->ant = lst->ult;
        lst->ult->prox = novo_item;
        lst->ult = novo_item;
    }
    /*insere conforme posição dada*/
    else
    {
        aux = item_poteiro_pos(lst, pos);

        /*apontando o prox e ant do novo item*/
        novo_item->prox = aux;
        novo_item->ant = aux->ant;

        /*inserindo entre elementos da lista*/
        aux->ant->prox = novo_item;
        aux->ant = novo_item;
    }

    lst->tamanho++;

    return lst->tamanho;
}

int lista_retira(struct lista_t *lst, int *item, int pos)
{
    struct item_t *aux;

    if (!lst || !item || !lst->tamanho)
        return -1;

    /*retira no inicio da lista*/
    if (!pos)
    {
        /*resolvendo um problema caso lista tenha um elemento*/
        aux = lst->prim;
        if (lst->tamanho == 1)
        {
            lst->prim = NULL;
            lst->ult = NULL;
        }
        else
        {
            /*só faz se aux->prox for diferente de NULL*/
            lst->prim = aux->prox;
            aux->prox->ant = NULL;
        }
    }
    /*retira no fim da lista*/
    else if (pos < 0 || pos > lst->tamanho)
    {
        aux = lst->ult;
        aux->ant->prox = NULL;
        lst->ult = aux->ant;
    }
    /*retira conforme posição dada*/
    else
    {
        aux = item_poteiro_pos(lst, pos);
        aux->ant->prox = aux->prox;
        aux->prox->ant = aux->ant;
    }

    /*retorna o valor retirado por referencia*/
    *item = aux->valor;
    item_destroi(aux);
    lst->tamanho--;

    return lst->tamanho;
}

int lista_consulta(struct lista_t *lst, int *item, int pos)
{
    struct item_t *aux;

    if (!lst || !item)
        return -1;

    /* se a lista estiver vazia*/
    if (!lst->prim || pos > lst->tamanho - 1)
        return -1;

    /*consulta no fim da lista*/
    if (pos < 0)
        aux = lst->ult;
    /*consulta conforme posição dada*/
    else
        aux = item_poteiro_pos(lst, pos);

    /*informo o valor do item consultado*/
    *item = aux->valor;

    return lst->tamanho;
}

int lista_procura(struct lista_t *lst, int valor)
{
    struct item_t *aux;
    int pos;

    if (!lst || !lst->tamanho)
        return -1;

    /*procura a partir do inicio da lista até achar o valor*/
    else
    {
        aux = lst->prim;
        pos = 0;
        while (aux != NULL && aux->valor != valor)
        {
            aux = aux->prox;
            pos++;
        }
    }

    /*se não encontrou elemento retorna -1, caso contrario a posição*/
    if (!aux)
        return -1;
    else
        return pos;
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

    if (!lst)
        return;

    /*enquanto não chegar no final da lista
    imprime os elementos*/
    aux = lst->prim;
    while (aux != NULL)
    {
        printf("%d", aux->valor);
        aux = aux->prox;

        /*garantindo que não imprima um espaço
        a mais no final da impressao*/
        if (aux)
            printf(" ");
    }
}