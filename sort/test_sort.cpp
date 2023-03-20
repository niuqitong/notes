//
// Created by nqt on 3/16/2023.
//
#include <iostream>
#include "sorts.h"
#include "pq.h"
void test1() {
  int n = 15;

  Sorts sorter(n);
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    a[i] = std::rand() % 1000;
  }
  for (int i : a)
    std::cout << i << ' ';
  sorter.quicksort(a, 0, n - 1);
  std::cout << '\n';
  for (int i : a)
    std::cout << i << ' ';
}
void test2() {
  int n = 15;

  Sorts sorter(n);
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    a[i] = std::rand() % 1000;
  }
  for (int i : a)
    std::cout << i << ' ';
  sorter.mergesort(a, 0, n - 1);
  std::cout << '\n';
  for (int i : a)
    std::cout << i << ' ';
}
void test3() {
  int n = 20;
  Sorts sorter(n);
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    a[i] = std::rand() % 1000;
  }
  for (int i : a)
    std::cout << i << ' ';
  sorter.heapsort(a);
  std::cout << '\n';
  for (int i : a)
    std::cout << i << ' ';
}

void test4() {
  int n = 30;

  pq q(100);
//  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    int v = std::rand() % 1000;
    q.push(v);
    std::cout << v << ' ';
  }
  std::cout << '\n';
  while (!q.empty()) {
    std::cout << q.top() << ' ';
    q.pop();
  }
}

int main() {
//  test3();
  test4();
  return 0;
}
