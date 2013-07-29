#include <stdio.h>
#include <stdlib.h>

void main() {
	int soma = 0;
	int i;

	int * v = (int*) malloc(10*sizeof(int));
	for(i = 0; i+ < 10; i++) {
		//v[i] = i; // forma 1
		*(v+i) = i; // forma 2
	}

	for(i = 0; i < 10; i++) {
		soma += v[i];
	}

	printf("somatorio eh %d\n", soma);

	free(v);

}
