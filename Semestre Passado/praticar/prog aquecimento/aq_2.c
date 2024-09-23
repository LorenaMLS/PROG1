#include <stdio.h>

int main (){

	int x,n;
	
	while (scanf ("%d" , &x ) != 0 && x != 0){
		n = x;
		scanf ("%d" , &x );
		if ( n * n != x){
			printf ("0 \n ");
			return 0;
		}
	}
	printf ("1 \n");
	return 0;
}

