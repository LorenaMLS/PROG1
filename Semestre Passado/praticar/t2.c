#include <stdio.h>

void ler(int *ptr_alt, int *ptr_peso);
void imprimir(int *ptr_alt, int *ptr_peso);
void altera(int *ptr_alt, int *ptr_peso);

int main()
{
    int alt, peso; /*declaracao de variavel do tipo inteiro*/
    int *ptr_alt, *ptr_peso; /*declaracao de ponteiros*/

    ptr_alt = &alt; /*atribuicao de ponteiro*/
    ptr_peso = &peso; 

    ler(ptr_alt, ptr_peso);
    imprimir(ptr_alt, ptr_peso);
    altera(ptr_alt, ptr_peso);
    imprimir(ptr_alt, ptr_peso);

    return 0;
}

void ler(int *ptr_alt, int *ptr_peso){
    printf("insira a altura \n");
    scanf("%d", ptr_alt);

    printf("insira o peso \n");
    scanf("%d", ptr_peso);
}

void imprimir(int *ptr_alt, int *ptr_peso){
    printf("altura: %d \n", *ptr_alt);
    printf("peso: %d \n", *ptr_peso);

    printf("endereco: %p \n", ptr_alt); /*imprime o endereco*/
    printf("endereco2: %p \n", ptr_peso);
}

void altera(int *ptr_alt, int *ptr_peso){
    *ptr_alt = *ptr_alt + 10;
    *ptr_peso = *ptr_peso + 10;
}