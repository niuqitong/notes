//
// Created by nqt on 3/19/2023.
//

#ifndef NOTES_NAIVE_VECTOR_H
#define NOTES_NAIVE_VECTOR_H

#include <exception>

class vec{
public:
  vec(int n) : size_(n), cap_(n * 2) {
    a_ = new int[n * 2];
    for (int i = 0; i < cap_; ++i) {
      a_[i] = 0;
    }
  }
  int& front() {
    return a_[0];
  }
  int& back() {
    return a_[size_ - 1];
  }
  int size() {
    return size_;
  }

  int& operator[](int i) {
    if (i < size_ && i >= 0)
      return a_[i];
    else throw std::exception();
  }

  void push_back(int v) {
    a_[size_++] = v;
  }
  vec(vec&& source) {
//    delete[] a_;
    a_ = source.a_;
    size_ = source.size_;
    cap_ = source.cap_;
    source.a_ = nullptr;
    source.size_ = 0;
    source.cap_ = 0;
  }
  vec& operator=(vec&& rhs) {
    if (this == &rhs) {
      return *this;
    }
    delete[] a_;
    a_ = rhs.a_;
    size_ = rhs.size_;
    cap_ = rhs.cap_;
    rhs.a_ = nullptr;
    rhs.cap_ = 0;
    rhs.size_ = 0;
    return *this;
  }


//private:
  int* a_;
  int size_;
  int cap_;
//  int end_;
};

#endif //NOTES_NAIVE_VECTOR_H
