#include <stdio.h>

int main (){
	
	int n,x,i,soma;

	scanf ("%d", &n);
	soma = n * 37;
	
	for (i=0; i < soma; i++) {
		soma = soma / 100;
		x = soma + soma + soma;
	
		if (x == n){
			printf ("SIM \n");
			return 0;
		}
	}
	printf ("NAO\n");
	return 0;
}
