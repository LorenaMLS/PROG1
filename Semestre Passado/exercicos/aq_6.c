#include <stdio.h>

void olamundo(int,n){
	if (n == 0)
		return;

	olamundo(n-1);
	printf("ola mundo %d/n",n);
	

}

int main(){

	int n;

	scanf("%d", &n);
	olamundo(n);

	return 0;
}

