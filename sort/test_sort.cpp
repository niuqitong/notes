//
// Created by nqt on 3/16/2023.
//
#include <iostream>
#include "sorts.h"
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

int main() {
  test2();
  return 0;
}
