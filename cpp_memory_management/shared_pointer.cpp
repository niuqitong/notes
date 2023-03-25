//
// Created by Qitong Niu on 2023/3/23.
//
#include <iostream>
#include <memory>

using namespace  std;

class B;

class A {
public:
  std::weak_ptr<B> b;
};

class B {
public:
  std::weak_ptr<A> a;
};

int test() {
  std::shared_ptr<A> pA(new A);
  std::shared_ptr<B> pB(new B);
  cout << " cyclic ref\n";
//  cout <<pA->b.use_count() << ' ' << pB->a.use_count() << endl;
  cout << pA.use_count() << ' ' << pB.use_count() << endl;
  pA->b = pB;
  cout <<pA.use_count() << ' ' << pB.use_count() << endl;

  pB->a = pA;
  cout <<pA->b.use_count() << ' ' << pB->a.use_count() << endl;

  return 0;
}

int main() {
  test();
  shared_ptr<int> p = make_shared<int>(43);

  shared_ptr<int> q = make_shared<int>(42);
//  q.reset(p.get());
  cout << *p;

  // 这里p和q指向同一个地址, 但是p和q的引用计数都是1, 会导致以下错误:
  // shared_pointer(67325,0x20844c140) malloc: *** error for object 0x6000017151f8: pointer being freed was not allocated

//  q.reset(make_shared<int>(44));
  cout << endl << *q << endl;
  cout << "p and q points to the same memory\n";
  cout << p.use_count() << endl;
  cout << q.use_count() << endl;

  std::shared_ptr<int> p1(new int(42));  // 创建一个 shared_ptr 对象
  std::shared_ptr<int> p2(std::move(p1));  // 使用移动构造函数将 p1 的资源转移给 p2
  cout << p1.get() << endl;
  std::cout << *p2 << std::endl;  // 输出 42

}