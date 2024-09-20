

#include <stdio.h>
#define TAM 1024

int main() {
    int n,i,aux;

    printf ("digite o tamanho do vetor");

    scanf ("%d", &n);
    int vet[TAM];
    aux = n;

    for (i=0; i < n; i++) {
        vet[i] = aux;
        aux = aux-1;
        printf ("%d\n", vet[i]);
    }
return 0;
} 