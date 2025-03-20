#include <stdio.h>

int main()
{
    int n, i, triangular;
    
    scanf("%d", &n);
    printf("triangular lido %d\n", n);
    
    i = 1;
    triangular = 0;
    while (triangular < n)
    {   
        /*calcula o triangular*/
        triangular = (i * (i + 1) * (i + 2));
        i++;
        printf("triangular %d\n", triangular);
    }

    /*se for triangular, imprime 1 se não 0*/
    if (triangular != n)
        printf("0\n");
    else
        printf("1\n");

    return 0;
}