#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 3
#define PRINT_TIMES 10

pthread_t threads[NUM_THREADS];
pthread_mutex_t mutex;
int current_index = 0;

void* print_thread(void* arg) {
  int thread_id = (int)(long)arg;
  char letter = 'A' + thread_id;

  for (int i = 0; i < PRINT_TIMES; i++) {
    pthread_mutex_lock(&mutex);
    while (current_index % NUM_THREADS != thread_id) {
      pthread_mutex_unlock(&mutex);
      sched_yield();
      pthread_mutex_lock(&mutex);
    }

    printf("%c", letter);
    current_index++;
    pthread_mutex_unlock(&mutex);
  }

  return NULL;
}

int main() {
  pthread_mutex_init(&mutex, NULL);

  for (int i = 0; i < NUM_THREADS; i++) {
    pthread_create(&threads[i], NULL, print_thread, (void*)(long)i);
  }

  for (int i = 0; i < NUM_THREADS; i++) {
    pthread_join(threads[i], NULL);
  }

  pthread_mutex_destroy(&mutex);
  printf("\n");
  return 0;
}

