#include <stdio.h>

void main() {

	int variavel = 1;

	printf("valor da variavel = %d\n", variavel);
	
	int * ponteiro = &variavel;

	*ponteiro = 5;

	printf("valor alterado = %d (capturado pela variavel)\n", variavel);
	printf("valor alterado = %d (capturado pelo ponteiro)\n", *ponteiro);

}
