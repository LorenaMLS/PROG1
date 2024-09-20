#include "libpilha.h"
#include <stdio.h>
#include <stdlib.h>

#define TAM 100

int verificacao(pilha_t *minha_pilha, char *equacao)
{
    int i, dado;

    for (i = 0; equacao[i] != '\0'; i++)
    {
        dado = (int)equacao[i];
          /*Se for algum caracter de fechamento de expressão e a pilha estiver vazia
        retorna erro*/
        if ((pilha_vazia(minha_pilha)) && (equacao[i] == '}' || equacao[i] == ']' || equacao[i] == ')'))
        {
            return 0;
        }

        else if (equacao[i] == '{' || equacao[i] == '[' || equacao[i] == '(')
        {
            if (!push(minha_pilha, dado))
                printf("não empilhou\n");
        }

        else if (equacao[i] == '}' && minha_pilha->topo->dado == '{')
        {
            if (!pop(minha_pilha, &dado))
                printf("não desempilhou\n");
        }
        else if (equacao[i] == ']' && minha_pilha->topo->dado == '[')
        {
            if (!pop(minha_pilha, &dado))
                printf("não desempilhou\n");
        }
        else if (equacao[i] == ')' && minha_pilha->topo->dado == '(')
        {
            if (!pop(minha_pilha, &dado))
                printf("não desempilhou\n");
        }
    }

    if (pilha_vazia(minha_pilha))
        return 1;
    return 0;
}

int main()
{
    pilha_t *minha_pilha;

    char equacao[TAM];

    minha_pilha = pilha_cria();

    scanf("%[^\n]", equacao);

    if (verificacao(minha_pilha, equacao))
        printf("CORRETO\n");
    else
        printf("INCORRETO\n");

    pilha_destroi(&minha_pilha);

    return 0;
}