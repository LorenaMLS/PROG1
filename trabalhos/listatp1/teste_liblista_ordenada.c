#include <stdio.h>
#include <stdlib.h>
#include "liblista_ordenada.h"

int main() {
    lista_t *lista = lista_cria();
    elemento_t *elemento;
    int opcao;

    do {
        printf("1 - Inserir elemento\n");
        printf("2 - Remover elemento\n");
        printf("3 - Imprimir lista\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                elemento = malloc(sizeof(elemento_t));
                printf("Digite a chave do elemento: ");
                scanf("%d", &elemento->chave);
                if (lista_insere_ordenado(lista, elemento))
                    printf("Elemento inserido com sucesso!\n");
                else
                    printf("Erro ao inserir elemento!\n");
                break;
            case 2:
                elemento = malloc(sizeof(elemento_t));
                printf("Digite a chave do elemento a ser removido: ");
                scanf("%d", &elemento->chave);
                if (lista_remove_ordenado(lista, elemento))
                    printf("Elemento removido com sucesso!\n");
                else
                    printf("Elemento não encontrado na lista!\n");
                free(elemento);
                break;
            case 3:
                printf("\nLista: ");
                nodo_t *no = lista->ini;
                while (no != NULL) {
                    printf("%d ", no->elemento->chave);
                    no = no->prox;
                }
                printf("\n\n");
                break;
            case 0:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opção inválida!\n");
                break;
        }
    } while (opcao != 0);

    lista_destroi(&lista);
    return 0;
}