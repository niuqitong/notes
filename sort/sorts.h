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
  void heapsort(std::vector<int>& a);
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

private:
  void init_max_heap(std::vector<int>& nums);
  void max_heapify(std::vector<int>& a, int cur, int len);
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

void Sorts::heapsort(std::vector<int>& a) {
  init_max_heap(a);
  for (int i = a.size() - 1; i > 0; --i) {
    std::swap(a[0], a[i]);
    max_heapify(a, 0, i);
  }
}

void Sorts::init_max_heap(std::vector<int> &nums) {
  int last_non_leaf = nums.size() / 2 - 1;
  for (int i = last_non_leaf; i >= 0; --i) {
    max_heapify(nums, i, nums.size());
  }
}

void Sorts::max_heapify(std::vector<int> &a, int cur, int len) {
  int left = cur * 2 + 1;
  int right = cur * 2 + 2;
  int max_id = cur;
  if (left < len && a[left] > a[max_id]) {
    max_id = left;
  }
  if (right < len && a[right] > a[max_id]) {
    max_id = right;
  }
  if (cur != max_id) {
    std::swap(a[cur], a[max_id]);
    max_heapify(a, max_id, len);
  }
}



#endif //NOTES_SORTS_H
