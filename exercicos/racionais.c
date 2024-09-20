#include <stdio.h>

typedef struct {
    int num;
    int den;
}
racional;

racional ler_racional (racional x) {

    scanf("%d %d \n", &x.num, &x.den);
    return x;
}

racional soma (racional x, racional x1) {

    racional i;

    i.num = ((x.num * x1.den) + (x1.num * x.den ));
    i.den = (x.den * x1.den);

    return i;
}

void imprime_racionais (racional x) {
    printf ("%d \n", x);
}



int main() {
    
    racional numerador, denominador;

    numerador = ler_racional (numerador);
    denominador = ler_racional (denominador);
    imprime_racionais 
    
}