#include <stdio.h>
#include <stdlib.h>
#include "liblista_circular.h"

int main() {
    lista_t *lista = lista_cria();

    elemento_t *elem1 = malloc(sizeof(elemento_t));
    elem1->chave = 10;

    elemento_t *elem2 = malloc(sizeof(elemento_t));
    elem2->chave = 20;

    elemento_t *elem3 = malloc(sizeof(elemento_t));
    elem3->chave = 30;

    lista_insere_ordenado(lista, elem1);
    lista_insere_ordenado(lista, elem2);
    lista_insere_ordenado(lista, elem3);

    elemento_t *elem_remover = malloc(sizeof(elemento_t));
    elem_remover->chave = 30;
    int resultado = lista_remove_ordenado(lista, elem_remover);

    if (resultado == 1) {
        printf("Elemento removido com sucesso!\n");
    } else {
        printf("Elemento não encontrado na lista!\n");
    }
    return 0;
}