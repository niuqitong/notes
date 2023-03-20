//
// Created by nqt on 3/19/2023.
//
#include <vector>
#include <cstdlib>
#include <functional>
#include <algorithm>
#ifndef NOTES_PQ_H
#define NOTES_PQ_H

class pq{
public:
  explicit pq(int cap) : cap_(cap) {
    q.reserve(cap);
  }
  void push(int v);
  int top();
  void pop();
  bool empty();

private:
  void max_heapify(int cur);
  std::vector<int> q;
  int cap_;
};

int pq::top() {
  return q[0];
}

void pq::pop() {
  std::swap(q.front(), q.back());
  q.pop_back();
  max_heapify(0);
}

void pq::push(int v) {
  q.push_back(v);
  int n = q.size();
  int cur = q.size() / 2 - 1;
  if (cur >= 0)
    max_heapify(cur);
}
void pq::max_heapify(int cur) {
  int left = cur * 2 + 1;
  int right = cur * 2 + 2;
  int max_id = cur;
  if (left < q.size() && q[max_id] < q[left]) {
    max_id = left;
  }
  if (right < q.size() && q[max_id] < q[right]) {
    max_id = right;
  }
  if (max_id != cur) {
    std::swap(q[cur], q[max_id]);
    max_heapify((cur - 1) / 2);
    max_heapify(max_id);
  }
}
bool pq::empty() {
  return q.empty();
}

#endif //NOTES_PQ_H
