#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N_NUMBERS 1000
#define BUFFER_SIZE 10

int *buffer;
int count;
pthread_mutex_t mutex;
pthread_cond_t condp, condc;

int produzItem (int base) {
  usleep(100);
  return base;
}

int consomeItem (int item) {
  usleep(100);
  return item;
}

void *produtor(void *param) {

  int k=1, in=0;

  while ( k<=N_NUMBERS ) {

    pthread_mutex_lock(&mutex);
    if (count == BUFFER_SIZE)
	pthread_cond_wait(&condp, &mutex);
    pthread_mutex_unlock(&mutex);

    int item = produzItem (k);
    buffer[in] = item;
    in = (in + 1) % BUFFER_SIZE;
    k++;

    pthread_mutex_lock(&mutex);
    count++;
    if(count == 1)
	pthread_cond_signal(&condc);
    pthread_mutex_unlock(&mutex);
  }
  
  pthread_exit(NULL);
}

void *consumidor(void *param) {

  int k=1, out=0;
  double mean=0;

  while (k<=N_NUMBERS) {
    pthread_mutex_lock(&mutex);
    if (count == 0)
	pthread_cond_wait(&condc, &mutex);
    pthread_mutex_unlock(&mutex);

    int item =  buffer[out];
    out = (out + 1) % BUFFER_SIZE;
    k++;

    pthread_mutex_lock(&mutex);
    count--; // controla o numero de itens no BUFFER
    if (count == BUFFER_SIZE - 1)
	pthread_cond_signal(&condp);
    pthread_mutex_unlock(&mutex);

    mean += consomeItem (item);
  }
  mean /= N_NUMBERS;

  printf ("Consumer: Mean value is %.1f.\n", mean);    

  pthread_exit(NULL);
}

int main (int argc, char *argv[])
{
    buffer = (int *)malloc( BUFFER_SIZE * sizeof(int) );
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&condp, NULL);
    pthread_cond_init(&condc, NULL);
    pthread_t prod_t;
    pthread_t cons_t;    
    pthread_create(&prod_t, NULL, produtor, NULL);
    pthread_create(&cons_t, NULL, consumidor, NULL);

    printf ("Main(): Launched all threads.\n");
    
    /* Clean up and exit */
    pthread_exit(NULL);   
}
