#include <stdio.h>
#include <stdlib.h>

struct semestre {
	int indice;
	double *notas;
}

main() {
	struct semestre * s1 = (struct semestre*) malloc(sizeof(struct semestre));
	struct semestre s2;

	s1->notas = (double*) malloc(10*sizeof(double));
	s2.notas = (double*) malloc(10*sizeof(double));

	int i;	

	// gerando notas
	for(i = 0; i < 10; i++) {
		s1->notas[i] = rand() % 10;
		s2.notas[i] = rand() % 10;
	}

	double media[10];

	// calculo das medias
	for(i = 0; i < 10; i++) {
		media[i] = (s1->notas[i] + s2.notas[i])/2;
	}

	for(i = 0; i < 10; i++) {
		printf("media materia %d = %g\n", i, media[i]);
		printf("semestre 1: nota materia %d = %g\n", i, s1->notas[i]);
		printf("semestre 2: nota materia %d = %g\n", i, s2.notas[i]);
	}
}
