#include <stdio.h>

void printar(int a, int b); 

int somar(int a, int b);

void soma_ponteiro(int *a, int *b,int *soma);

void add(int *a, int *b);

int main()
{
    int a,b,soma;
    int *ptr_a;
    ptr_a = &a;

    printf("digite um primeiro numero \n");
    scanf ("%d", &a);

    printf("digite um segundo numero \n");
    scanf ("%d", &b);

    printar(a,b);
    add(&a,&b);

    //soma_ponteiro(ptr_a,&b,&soma);// o e comercial//
    //printf("resultado %d\n", soma);
    printar(a,b);

    return 0;
}

void printar(int a, int b){
    printf("Numero a: %d \n", a);
    printf("Numero b: %d \n", b);
} 

int somar(int a, int b){ //por copia//
    return (a+b);
}

void soma_ponteiro(int *a, int *b,int *soma){ //por refencia e ponterio//
    *soma = *a+*b;
}

void add(int *a, int *b){
    *a = *a + 1;
    *b = *b + 1;
}