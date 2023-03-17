//
// Created by nqt on 3/16/2023.
//
#include <vector>
#include <cstdlib>
#include <functional>
#include <algorithm>
#ifndef NOTES_SORTS_H
#define NOTES_SORTS_H

class Sorts {
public:
  Sorts(int n) : n_(n) {
    sup.resize(n, 0);
  }
  void quicksort(std::vector<int>& a, int l, int r) {
    if (l >= r)
      return;
    int pivot = std::rand() % (r - l + 1) + l;
    int k = partition(a, l, r, pivot);
    quicksort(a, l, k - 1);
    quicksort(a, k + 1, r);
  }

  void mergesort(std::vector<int>& a, int l, int r) {
    if (l >= r) {
      return;
    }
    int mid = (l + r) >> 1;
    mergesort(a, l, mid);
    mergesort(a, mid + 1, r);
    merge(a, l, mid, r);
  }

  void heapsort() {

  }
private:
  void merge(std::vector<int>& a, int l, int mid, int r) {
    int i = l, j = mid + 1;
    int id = l;
    while (i <= mid && j <= r) {
      if (a[i] < a[j]) {
        sup[id++] = a[i++];
      } else {
        sup[id++] = a[j++];
      }
    }
    while (i <= mid) {
      sup[id++] = a[i++];
    }
    while (j <= r) {
      sup[id++] = a[j++];
    }
    for (int i = l; i <= r; ++i) {
      a[i] = sup[i];
    }
  }
  static int partition(std::vector<int>& a, int l, int r, int k) {
    std::swap(a[r], a[k]);
    int id = l;
    for (int i = l; i < r; ++i) {
      if (a[i] < a[k]) {
        std::swap(a[i], a[id++]);
      }
    }
    std::swap(a[id], a[r]);
    return id;
  }

  int n_;
  std::vector<int> sup;
};

#endif //NOTES_SORTS_H
