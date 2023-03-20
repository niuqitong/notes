#include <stdlib.h>
#include <iostream>
#include <cassert>
using std::cout;
using std::endl;
class MyMovableClass
{
private:
    int _size;
    int *_data;

public:
    bool invalid() { return this->_data == nullptr; }
    int get_size() { return this->_size; }
    void show_data_address() { cout << "data address of   " << this << " == " << _data << endl; }
    void show_object_address() { cout << "object address == " << this << endl; }
    MyMovableClass(size_t size) // constructor
    {
        _size = size;
        _data = new int[_size];
        std::cout << "CREATING instance of MyMovableClass at " << this << " allocated with size = " << _size*sizeof(int)  << " bytes" << std::endl;
    }

    ~MyMovableClass() // 1 : destructor
    {
        std::cout << "DELETING instance of MyMovableClass at " << this << std::endl;
        delete[] _data;
    }
    
    MyMovableClass(MyMovableClass &&source) // 4 : move constructor
    {
        std::cout << "MOVING (c’tor) instance " << &source << " to instance " << this << std::endl;
        _data = source._data;
        _size = source._size;
        source._data = nullptr;
        source._size = 0;
    }
    
    MyMovableClass &operator=(MyMovableClass &&source) // 5 : move assignment operator
    {
        std::cout << "MOVING (assign) instance " << &source << " to instance " << this << std::endl;
        if (this == &source)
            return *this;

        delete[] _data;

        _data = source._data;
        _size = source._size;

        source._data = nullptr;
        source._size = 0;

        return *this;
    }
    
    MyMovableClass(const MyMovableClass &source) // 2 : copy constructor
    {
        _size = source._size - 1;
        _data = new int[_size];
        *_data = *source._data;
        std::cout << "COPYING content of instance " << &source << " to instance " << this << std::endl;
    }
    
    MyMovableClass &operator=(const MyMovableClass &source) // 3 : copy assignment operator
    {
        std::cout << "ASSIGNING content of instance " << &source << " to instance " << this << std::endl;
        if (this == &source)
            return *this;
        delete[] _data;
        _data = new int[source._size - 1];
        *_data = *source._data;
        _size = source._size - 1;
        return *this;
    }
};
void useObject(MyMovableClass obj)
{
    std::cout << "using object " << &obj << std::endl;
    obj.show_data_address();
}

MyMovableClass createObject(size_t size) {
    MyMovableClass a(size);
    // a.show_data_address();
    cout << "size in create == ";
    cout << a.get_size() << endl;
    return a;
}

int main()
{
    MyMovableClass obj1(100); // constructor
    cout << obj1.get_size() << endl;
    MyMovableClass obj3 = obj1;
    cout << obj3.get_size() << endl;
    // obj3 = MyMovableClass(100);
    cout << "test create\n";
    MyMovableClass obj2(150); // when a function returns an object by value, 
    obj2 = createObject(300); // temporary object createObject(300) is treated as an rvalue, so move assign is called. 
    cout << "---------------\n";
    MyMovableClass obj4 = createObject(12); // doesn't call copy constructor or copy assign, so how ????
    cout << "size in main == " << obj4.get_size() << endl;
    // obj4.show_data_address();
    // MyMovableClass obj1 = obj2;
    // obj1.show_data_address();
    // the compiler creates a temporary object as an RVALUE
    // std::cout << "phase 1\n";
    // useObject(std::move(obj2));
    // cout << "phase 2\n";
    // assert(obj1._data == nullptr);
    // if (obj1.invalid())
    //     std::cout << "obj1 deleted" << std::endl;
    /* 
    Note that after the call to useObject, the instance obj1
     has been invalidated by setting its internal handle to null 
     and thus may not be used anymore within the scope of main
     */
//     MyMovableClass obj2 = obj1;
    return 0;
}