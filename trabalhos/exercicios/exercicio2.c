#include <stdio.h>
#define lin 3
#define col 3

int soma_matriz(int matriz, int tamanho)
{
    int *i, *j, soma;

    for (i = 0; i < tamanho; i++)
        for (j = 0; j < tamanho; j++)
            soma += matriz[i][j];
    
    return soma;
}

int main()
{
    int matriz[lin][col];

    /*lê a matriz*/
    for (int i = 0; i < lin; i++)
        for (int j = 0; j < lin; j++)
            scanf("%d", &matriz[i][j]);

    /*imprime a matriz*/
    for (int i = 0; i < lin; i++)
        for (int j = 0; j < lin; j++)
            printf("m[%d] %d\n", matriz[i], i);

    printf ("soma %d\n", soma_matriz(matriz[lin][col], lin));

    return 0;
}