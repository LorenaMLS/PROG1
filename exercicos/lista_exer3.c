

#include <stdio.h>
#define TAM 1024

int main() {
    int n,i;

    printf ("digite o tamanho do vetor: ");

    scanf ("%d", &n);
    int vet[TAM];

    for (i=0; i < n; i++) {
        int x;
        scanf ("%d", &x );
        vet[i] = x;
        printf ("vetor:%d\n", vet[i]);
    }
return 0;
} 