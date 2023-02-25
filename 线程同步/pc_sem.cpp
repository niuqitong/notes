#include <pthread.h>
#include <iostream>
#include <unistd.h>
#include <semaphore.h>

using namespace std;

const int BUFSIZE = 5;

// char buf[BUFSIZE];
int count = 0;
int max_product = 0;
sem_t mutex;
sem_t empty;
sem_t full;
void put() {
    count++;
    
    cout << "producer, " << count << " products in the buffer\n";

}

void get() {

    count--;

    cout << "consumer, " << count << " products in the buffer\n";
}

void* producer(void* arg) {

    int* p = (int*)arg;
    int n = *p;
    for (int i = 0; i < n; i++) {
        sem_wait(&empty);
        sem_wait(&mutex);
        put();
        sem_post(&mutex);
        sem_post(&full);
        sleep(1);
    }

    return NULL;
}

void* consumer(void* arg) {
    int* p = (int*)arg;
    int n = *p;
    for (int i = 0; i < n; i++) {
        sem_wait(&full);
        sem_wait(&mutex);
        get();
        sem_post(&mutex);
        sem_post(&empty);
        sleep(1);
    }

    return NULL;
}
void* producer_deadlock(void* arg) {

    int* p = (int*)arg;
    int n = *p;
    for (int i = 0; i < n; i++) {
        sem_wait(&mutex);
        sem_wait(&empty);
        put();
        sem_post(&full);
        sem_post(&mutex);
        sleep(1);
    }

    return NULL;
}

void* consumer_deadlock(void* arg) {
    int* p = (int*)arg;
    int n = *p;
    for (int i = 0; i < n; i++) {
        sem_wait(&mutex);
        sem_wait(&full);

        get();

        sem_post(&empty);
        sem_post(&mutex);
        sleep(1);
    }

    return NULL;
}


int main() {
    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, BUFSIZE);
    sem_init(&full, 0, 0);
    pthread_t t_producer;
    pthread_t t_consumer;
    pthread_create(&t_consumer, NULL, consumer, (void*)&BUFSIZE);
    pthread_create(&t_producer, NULL, producer, (void*)&BUFSIZE);
    pthread_join(t_producer, NULL);
    pthread_join(t_consumer, NULL);
    // while (1) {
    //     sleep(1);
    // }
}