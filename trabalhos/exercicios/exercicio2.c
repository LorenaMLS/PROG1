#include <stdio.h>

void imprime_vet(int *vet, int tam)
{
    if(!vet)
        return;

    int i = 0;
    while (i < tam)
    {
        printf("%d ", vet[i]);
        i++;
    }
    printf("\n");
}

int main ()
{
    int r[10], par[10], impar[10];
    int i;

    i = 0;
    while (i < 10)
    {
        par[i] = i * 2;
        impar[i] = i * 2 + 1;
        r[i] = 0;
        i++;
    }

    i = 0;
    while (i < 10)
    {
        r[i]= par[i] + impar[i];
        i++;
    }

    imprime_vet(par, 10);
    imprime_vet(impar, 10);
    imprime_vet(r, 10);

    return 0;
}