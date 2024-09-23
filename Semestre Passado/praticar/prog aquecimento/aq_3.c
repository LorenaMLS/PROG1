#include <stdio.h>

int main (){

	int k,atual,perf,soma;
	scanf ("%d" , &k);

	if  (k == 1){
		printf ("6 \n");
		return 0;
	}
	atual = 1;
	perf = 0;

	while (perf < k) {
		soma = 0;

		for (int i = 1 ; i < atual ; i++) {
			if (atual % i == 0){
				soma += i;
			}
		}

		if (soma == atual){
			printf ("%d " , atual);
			perf++;
		}
		atual++;
	}
	return 0;
}
