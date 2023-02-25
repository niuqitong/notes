#include <pthread.h>
#include <iostream>
using std::cout;
using std::endl;
class singleton {
public:
    static singleton& get_singleton() {
        static singleton instance;
        return instance;
    }
private:
    singleton() {}
    singleton(const singleton& source) {}
    singleton& operator=(const singleton& rhs) {}

};

class singleton_lazy {
public:
    static singleton_lazy* get_singleton_pointer() {
        if (p == nullptr) {
            // cout << "mutex used before init\n";
            pthread_mutex_lock(&mutex);
            if (p == nullptr) {
                p = new singleton_lazy();
                // cout << "singleton created\n";
            }
            pthread_mutex_unlock(&mutex);
        }
        return p;
    }
private:
    static pthread_mutex_t mutex;
    static singleton_lazy* p;

    singleton_lazy() {
        // cout << "mutex initialized\n";
        // pthread_mutex_init(&mutex, NULL);
    }
    singleton_lazy(const singleton_lazy& source) {}
    singleton_lazy& operator=(const singleton_lazy& rhs) {}

};

singleton_lazy* singleton_lazy::p = nullptr;
pthread_mutex_t singleton_lazy::mutex = PTHREAD_MUTEX_INITIALIZER;
int main() {

    singleton_lazy* ins1 = singleton_lazy::get_singleton_pointer();
    singleton_lazy* ins2 = singleton_lazy::get_singleton_pointer();
    cout << ins1 << endl;
    cout << ins2 << endl;
    return 0;
}

