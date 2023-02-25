#include <pthread.h>
#include <iostream>
#include <unistd.h>
#include <semaphore.h>

using namespace std;



class rw_lock_reader_first { // writer can only writer when there's currently no reader
public:
    rw_lock_reader_first() : n_readers(0) {
        sem_init(&mutex, 0, 1);
        sem_init(&writelock, 0, 1);
    }

    void get_read_lock() {
        sem_wait(&mutex);
        n_readers++;
        if (n_readers == 1) {
            sem_wait(&writelock);
        }
        sem_post(&mutex);
    }

    void release_read_lock() {
        sem_wait(&mutex);
        n_readers--;
        if (n_readers == 0)
            sem_post(&writelock);
        sem_post(&mutex);
    }

    void get_write_lock() {
        sem_wait(&writelock);
    }

    void release_write_lock() {
        sem_post(&writelock);
    }
    void reader() {
        get_read_lock();
        // read()
        release_read_lock();
    }
    void writer() {
        get_write_lock();
        // write();
        release_write_lock();
    }

private:

    int n_readers;
    sem_t mutex;
    sem_t writelock;

};

class rw_lock_even { // r w have same priority
public:
    rw_lock_even() : n_readers(0) {
        sem_init(&mutex, 0, 1);
        sem_init(&writelock, 0, 1);
        sem_init(&flag, 0, 1);
    }

    void get_read_lock() {
        sem_wait(&flag);
        sem_wait(&mutex);
        n_readers++;
        if (n_readers == 1) {
            sem_wait(&writelock);
        }
        sem_post(&mutex);
        sem_post(&flag);
    }

    void release_read_lock() {
        sem_wait(&mutex);
        n_readers--;
        if (n_readers == 0)
            sem_post(&writelock);
        sem_post(&mutex);
    }

    void get_write_lock() {
        sem_wait(&flag);
        sem_wait(&writelock);
    }

    void release_write_lock() {
        sem_post(&writelock);
        sem_post(&flag);
    }

private:

    int n_readers;
    sem_t mutex;
    sem_t writelock;
    sem_t flag;

};


