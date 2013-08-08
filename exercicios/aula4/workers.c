#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS 8

pthread_mutex_t mutex;
pthread_cond_t cond;

int count = 0, chegaram = 0;

void preparaTarefas (int id) {
  usleep (1000000 + (rand()%10)*100000); // between 1 and 2 seconds
  printf("Thread %d: pronta!\n", id);
}


void realizaTarefas (int id) {
  printf("Thread %d: realizando tarefas!\n", id);
}

void *DoWork(void *param) 
{
  pthread_mutex_lock (&mutex);
  int tid = count++;
  pthread_mutex_unlock (&mutex);
  srand (tid+1);

  /* Prepare the thread to execute the tasks */
  preparaTarefas (tid);

  /* Perform the tasks */
  pthread_mutex_lock(&mutex);
  chegaram++;
  if (chegaram < NUM_THREADS)
    pthread_cond_wait(&cond, &mutex);
  else {
    pthread_cond_broadcast(&cond);
    chegaram = 0;
  }
  realizaTarefas (tid);
  pthread_mutex_unlock(&mutex);

  pthread_exit(NULL);
}

int main (int argc, char *argv[]) 
{
  pthread_t threads[NUM_THREADS];
  pthread_mutex_init (&mutex,NULL);
  pthread_cond_init(&cond, NULL);
  long t;
  for(t=0; t<NUM_THREADS; t++)
    pthread_create(&threads[t],NULL,DoWork,NULL);
  pthread_exit(NULL);    
}
