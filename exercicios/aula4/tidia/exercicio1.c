/*
 * Exercicio 1 - Calcular media de raizes quadradas usando threads
 * Compilar com: gcc ./exercicio1.c -pthread -lm -std=c99
 * Executar com: ./exercicio1 [N_THREADS] [N_MAX]
 *
 * Nome: Gustavo Danilo Machado
 * RA: 11014507
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

#define fori(x) for(int i = 0; i < x; i++)

int N_MAX = 10e7;
int N_THREADS = 4;
int count = 0;

pthread_mutex_t mutex;

void *Average(void *param) {
	// define attributes
	double mean = 0;
	double *ret = malloc(sizeof(double *));
	double *roots = *((double**) param);
	long step = N_MAX / N_THREADS;

	// increment thread count
	pthread_mutex_lock(&mutex);
	long start = count++ * step;
	pthread_mutex_unlock(&mutex);

	// calculate mean	
	for(long i = start; i < start + step; i++) {
		roots[i] = sqrt(i+1);
		mean += roots[i];
	}
	mean /= step;

	// store result into return pointer, and return it
	*ret = mean;
	return ret;
}


void main(int argc, char *argv[]) {
	switch (argc) {
		case 1:
			break;
		case 2:
			N_THREADS = atoi(argv[1]);
			break;
		case 3:
			N_THREADS = atoi(argv[1]);
			N_MAX = atoi(argv[2]);
			break;
		default:
			printf("Usage: ./exercicio1.o [threads] [numbers]\n\n");
			printf("threads: number of threads to be used (optional, defaults to 10e8)\n");
			printf("numbers: amount of numbers to calculate (optional, defaults to 4)\n");
			exit(1);
			break;
	}

	double *roots = (double*) malloc(N_MAX * sizeof(double));
	double *means = (double*) malloc(N_THREADS * sizeof(double));
	double mean = 0;
	pthread_t threads[N_THREADS];
	void *retval;

	pthread_mutex_init(&mutex, NULL);

	// start all threads
	fori(N_THREADS)
		pthread_create(&threads[i], NULL, Average, (void *)&roots);

	// wait for all threads to finish
	fori(N_THREADS) {
		pthread_join(threads[i], &retval);
		means[i] = *(double*)retval;
	}
	// calculate total mean from partial means
	fori(N_THREADS)
		mean += means[i];
	mean /= N_THREADS;

	printf("Total mean: %f\n", mean);

	// do cleanup
	free(means);
	free(roots);
	free(retval);
	pthread_mutex_destroy(&mutex);

	pthread_exit(NULL);
}