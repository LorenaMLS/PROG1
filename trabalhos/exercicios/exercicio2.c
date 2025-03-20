#include <stdio.h>

int main()
{
    int n, aux;
    
    do
    {
        scanf ("%d", &n);
        aux = n*n;

    } while (n != 0);

    if (n != aux)
    {
        printf("0\n");
        return 0;
    }
    
    printf ("1\n");

    return 0;
}