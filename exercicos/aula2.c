/*#include <stdio.h>

/*função de troca 
void troca (int a, int b) {
    int aux = a;
    a = b;
    b = aux;
    printf ("troca -> a = %d, b = %d\n", a,b);
}


int main () {
    int a = 0;
    int b = 1;


}
/*tipos de escopos estudar!*/
/*os indices de vetores em C começam em 0, diferente do pascal que começa em 1*/
/*definir o tamanho do vetor '#define tam 10..'*/

#include <stdio.h>
#define tam 1024;

int main() {
    int n,i;

    scanf ("%d", &n);
    int vet[n];

    for (i=0; i < n; i++);
        vet[i] = i;

    printf ("&d\n", vet[i]);
}
