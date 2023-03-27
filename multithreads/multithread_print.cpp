#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

constexpr int NUM_THREADS = 3;
constexpr int PRINT_TIMES = 10;

std::mutex mtx;
std::condition_variable cv;
int current_index = 0;

void print_thread(int thread_id) {
  char letter = 'A' + thread_id;

  for (int i = 0; i < PRINT_TIMES; ++i) {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [&] { return current_index % NUM_THREADS == thread_id; });

    std::cout << letter;
    ++current_index;
    lock.unlock();
    cv.notify_all();
  }
}

int main() {
  std::thread threads[NUM_THREADS];

  for (int i = 0; i < NUM_THREADS; ++i) {
    threads[i] = std::thread(print_thread, i);
  }

  for (auto& t : threads) {
    t.join();
  }

  std::cout << std::endl;
  return 0;
}
