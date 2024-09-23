#include <stdio.h> 
#define TAM 100


int main (){

    int n,i;
    int v[TAM], w[TAM];

    printf ("tamanho do vetor: ");

    scanf ("%d", &n);
    

    for (i=0; i < n; i++) {

        int x,j;
        scanf ("%d", &x);
        v[i]= x;
        printf ("conteudo do vetor v: %d \n", v[i]);
        j = n;
        w[j]= v[i];
        printf ("conteudo do vetor w: %d \n", w[j]);
        j -= 1;
        
    }
}