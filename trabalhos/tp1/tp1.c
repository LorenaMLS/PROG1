/*
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 16/09/2024 para a disciplina CI1001 - Programação 1.
 */

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

/* programa principal */
int main()
{
    struct racional r1, r2;
    int n, max, i;
    srand(0); /* use assim, com zero */

    /*leitura n, no intervalo 0 e 100*/
    do
    {
        scanf("%d", &n);
    } while (n < 0 || n > 100);

    /*leitura max, no intervalo 0 e 30*/
    do
    {
        scanf("%d", &max);
    } while (max < 0 || max > 30);

    for (i = 1; i <= n; i++)
    {
        printf("%d: ", i);

        /*sorteia e em seguida imprime*/
        r1 = sorteia_r(max * -1, max);
        r2 = sorteia_r(max * -1, max);

        imprime_r(r1);
        imprime_r(r2);

        /*se pelo menos um for invalido, imprime e sai*/
        if (!valido_r(r1) || !valido_r(r2))
        {
            printf("NUMERO INVALIDO\n");
            return 1;
        }

        /*se divisão não for valida sai*/
        if (!valido_r(divide_r(r1, r2)))
        {
            printf("DIVISAO INVALIDA\n");
            return 1;
        }

        /*imprime respectivamente soma, subtrai, multiplica e divide*/
        imprime_r(soma_r(r1, r2));
        imprime_r(subtrai_r(r1, r2));
        imprime_r(multiplica_r(r1, r2));
        imprime_r(divide_r(r1, r2));

        printf("\n");
    }

    return 0;
}
