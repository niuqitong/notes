//
// Created by nqt on 3/19/2023.
//
#include "naive_vector.h"
#include <iostream>

int main() {
  vec v(10);
  for (int i = 0; i < 5; ++i) {
    v.push_back(i);
  }
  for (int i = 0; i < v.size(); ++i) {
    std::cout << v[i] << ' ';
  }
  std:: cout << '\n';
  for (int i = 0; i < v.size(); ++i) {
    v[i] += i * i;
    std::cout << v[i] << ' ';
  }
  return 0;
}