#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

#define N_MAX 10e8
#define N_THREADS 1

int main(int argc, char **argv) {
	float *roots = (float*) malloc(N_MAX * sizeof(float));
	int i;

	// fill list with square roots from 1 to 10^8
	for(i = 0; i < N_MAX; i++) {
		roots[i] = sqrt(i+1);
	}

	// thread stuff here
}