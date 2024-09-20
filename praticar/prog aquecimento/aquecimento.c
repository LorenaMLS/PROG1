#include <stdio.h>

int main(){

	int n,x;
	scanf ("%d", &n);

	x = 1;
	while (x * (x + 1) * (x + 2) <= n){
		if (x * (x + 1) * (x + 2) == n){
			printf ("1\n");
			return 0;
		}
		x++;
	}

	printf ("0 \n");
	return 0;
}

