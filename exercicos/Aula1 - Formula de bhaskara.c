#include <stdio.h>
#include <math.h>

int main() {
    double a, b, c,delta,x1,x2;
    scanf (" %d "," %d "," %d ",&a,&b,&c);
    
    /*calcula delta*/
    delta= pow (b,2) - (4 * a *c);

    /*resultado das raizes*/
    x1= ((-b + sqrt (delta)) / 2*a);
    x2= ((-b - sqrt (delta)) / 2*a);

    printf ("resultado: %f" "%f\n",x1, x2); 

    return 0;
}