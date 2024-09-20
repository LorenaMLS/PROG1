#include <stdio.h>

struct pessoa{
    char pl;
    int cpf;
    int peso;
};

void ler(char *ptr_pl,int *prt_cpf, int *ptr_peso);

int main( )
{
    struct pessoa aluno; /*pessoa é o tipo da struct*/
    ler(&aluno.pl, &aluno.cpf, &aluno.peso);
    imprimir(&aluno.pl, &aluno.cpf, &aluno.peso);
    
    return 0;
}
// teste //
void ler(char *ptr_pl,int *ptr_cpf, int *ptr_peso){
    printf("insira o nome: \n");
    scanf ("%c", ptr_pl);

    printf("insira o cpf \n");
    scanf ("%d", ptr_cpf);

    printf("insira o peso \n");
    scanf ("%d", ptr_peso);
}

void imprimir(char *ptr_pl, int *ptr_cpf, int *ptr_peso){
    printf("nome: %c \n", *ptr_pl);
    printf("cpf: %d \n", *ptr_cpf);
    printf("peso: %d \n", *ptr_peso);
}
