#include <stdlib.h>
#include "libpilha.h"


pilha_t *pilha_cria (){
    pilha_t *Nova_pilha;

    if (!(Nova_pilha = malloc(sizeof(pilha_t))))
        return NULL;

    Nova_pilha->tamanho = 0;
    Nova_pilha->topo = NULL;

    return Nova_pilha;
}


/*utiliza uma variavel auxiliar, que eh um ponterio para struct nodo_t, 
para receber o topo da pilha e remove-lo*/
void pilha_destroi (pilha_t **pilha){
    nodo_t *aux;

    while ((*pilha)->topo != NULL){
        aux = (*pilha)->topo;
        (*pilha)->topo = (*pilha)->topo->prox;
        free (aux);
    }
    free(*pilha);
    *pilha = NULL;
}


/*o ponteiro nodo seria para armazenar temporariamente o dado do topo da pilha*/
int push (pilha_t *pilha, int dado){
    nodo_t *nodo;

    if(!(nodo = malloc(sizeof(nodo_t))))
        return 0;

    nodo->dado = dado;
    nodo->prox = pilha->topo;
    pilha->topo = nodo; 
    pilha->tamanho++;

    return 1;
}

/*o ponteiro nodo recebe o topo da pilha*/
int pop (pilha_t *pilha, int *dado){
    nodo_t *nodo;

    if (pilha_vazia(pilha)) 
        return 0;
    
    nodo = pilha->topo;
    pilha->topo = nodo->prox;
    *dado = nodo->dado;
    pilha->tamanho--;
    free (nodo);

    return 1;
}
 

int pilha_topo (pilha_t *pilha, int *dado){
    if (pilha_vazia(pilha))
        return 0;

    *dado = pilha->topo->dado;
    return 1;
}

    
int pilha_tamanho (pilha_t *pilha){

    return pilha->tamanho;
}


int pilha_vazia (pilha_t *pilha){
    if (pilha->tamanho == 0)
        return 1;

    return 0; 
}
