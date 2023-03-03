#include <cstdio>
#include <semaphore.h>
#include <pthread.h>
#include <list>
#include <iostream>
#include <unistd.h>
using namespace std;

class task {
public:
    task(int i = 0) : value(i) {}
    void run() {
        pthread_t thread = pthread_self();
        printf("Thread ID: %lu, value = ", (unsigned long)thread);
        printf("%d\n", value);
    }
    void set_value(int v) {
        value = v;
    }
private:
    int value;
};

template<typename T>
class thread_pool {

public:
    thread_pool(int n) : n_threads(n) {
        threads = new pthread_t[n];
        if (threads == nullptr) {
            throw std::exception();

        }
        if (pthread_mutex_init(&mutex, NULL) != 0) {
            throw std::exception();
        }
        if (sem_init(&sem, 0, 0) != 0) {
            throw std::exception();
        }
        for (int i = 0; i < n; ++i) {

            if(pthread_create(threads + i, NULL, worker, this) != 0) {
                delete[] threads;
                throw std::exception();
            }
            if (pthread_detach(threads[i]) != 0) {
                delete[] threads;
                throw std::exception();
            }
        }
        
    }
    ~thread_pool() {
        delete[] threads;
    }
    void append(T* task) {
        pthread_mutex_lock(&mutex);
        tasks.push_back(task);
        sem_post(&sem);
        pthread_mutex_unlock(&mutex);
    }

    static void* worker(void* arg) {
        thread_pool* pool = (thread_pool*)arg;
        while (true) {
            sem_wait(&(pool->sem));
            pthread_mutex_lock(&(pool->mutex));
            if (pool->tasks.empty()) {
                pthread_mutex_unlock(&(pool->mutex));
                continue;
            }
            T* task = pool->tasks.front();
            pool->tasks.pop_front();
            pthread_mutex_unlock(&(pool->mutex));
            task->run();

        }
        return pool;
    }


private:
    int n_threads;
    pthread_t* threads;
    list<T*> tasks;
    pthread_mutex_t mutex;
    sem_t sem;

};

int main() {
    int n = 0;
    cin >> n;
    thread_pool<task> pool(n);
    task* tasks = new task[n];
    for (int i = 0; i < n; ++i) {
        tasks[i].set_value(i);
        pool.append(&tasks[i]);
    }
    int i = 0;
    while (1) {
        sleep(1);
        if (++i >= n)
            break;
    }
    return 0;

}