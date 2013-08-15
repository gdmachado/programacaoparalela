#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>

#define loop(x,y) for(int x = 0; x < y; x++)

pthread_mutex_t mutex;
long **a, **b, **c;
int count = 0;

void *Multiply(void) {


    loop(i, N)
        loop(j, N)
            loop(k, N)
                c[i][j] += a[i][k] * b[k][j];
}

int main(int argc, char **argv) {

    switch (argc) {
        case 1:
            break;
        case 2:
            N = atoi(argv[1]);
            assert(N > 0);
            break;
        case 3:
            N = atoi(argv[1]);
            THREADS = atoi(argv[2]);
            assert(N > 0);
            assert(THREADS > 0);
            if (N / THREADS == 0) {
                printf("Matrix size must be divisible by number of threads! Exiting...\n");
                exit(1);
            }
            break;
        default:
            printf("Usage: ./exercicio2 [matrix size] [number of threads]\n\n");
            printf("matrix size: n, in a nxn matrix, defaults to 100\n");
            printf("number of threads: amount of threads to be created, defaults to 2\n");
            exit(1);
            break;
    }

    int N = 100, THREADS = 2;
    pthread_t threads[THREADS];

    int mul=5;
    int col_sum = N * (N-1) / 2;

    a = (long **)malloc (N * sizeof(long *));
    b = (long **)malloc (N * sizeof(long *));
    c = (long **)malloc (N * sizeof(long *));

    loop(i, N) {
        a[i] = (long *)malloc (N * sizeof(long));
        b[i] = (long *)malloc (N * sizeof(long));
        c[i] = (long *)malloc (N * sizeof(long));
    }


    loop(i, N) {
        loop(j, N) {
            a[i][j] = i*mul;
            b[i][j] = i;
            c[i][j] = 0;
        }

    printf ("Matrix generation finished.\n");         

    loop(i, THREADS)
        pthread_create(&threads[i], NULL, Multiply, NULL);

    printf ("Thread creation finished. Starting work...\n");

    loop(i, THREADS)
        pthread_join(&threads[i], NULL);

    printf ("Multiplication finished.\n");         

    loop(i, N)
        loop(j, N)
            assert ( c[i][j] == i*mul * col_sum);  

    printf ("Test finished.\n");         
}