#include <pthread.h>
#include <iostream>
#include <unistd.h>

using namespace std;

const int BUFSIZE = 5;

// char buf[BUFSIZE];
int count = 0;
int max_product = 0;
void put() {
    count++;
    
    cout << "producer, " << count << " products in the buffer\n";

}

void get() {

    count--;

    cout << "consumer, " << count << " products in the buffer\n";
}

pthread_cond_t empty;
pthread_cond_t full;
pthread_mutex_t mutex;

void* producer(void* arg) {

    int* p = (int*)arg;
    int n = *p;
    for (int i = 0; i < n; i++) {
        pthread_mutex_lock(&mutex);
        while (count == BUFSIZE) {
            pthread_cond_wait(&empty, &mutex); // 会在阻塞时释放锁, 唤醒时获得锁
        }
        put();
        pthread_cond_signal(&full);
        // sleep(1);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }

    return NULL;
}

void* consumer(void* arg) {
    int* p = (int*)arg;
    int n = *p;
    for (int i = 0; i < n; i++) {
        pthread_mutex_lock(&mutex);
        while (count == 0) {
            pthread_cond_wait(&full, &mutex);
        }
        get();
        pthread_cond_signal(&empty);
        // sleep(1);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }

    return NULL;
}

int main() {
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&empty, NULL);
    pthread_cond_init(&full, NULL);
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