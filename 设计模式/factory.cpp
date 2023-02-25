#include <iostream>
using namespace std;

class shoes;
class shirt;
class factory {
public:
    virtual shoes* create_shoes() = 0;
    virtual shirt* create_shirt() = 0; 
    virtual ~factory() {}
};

class shoes {
public:
    virtual void info() = 0;
    virtual ~shoes() {}
};

class nike_shoes : public shoes {
public:
    void info() override {
        cout << "nike shoes\n";
    }
};

class shirt {
public:
    virtual void info() = 0;
    virtual ~shirt() {};
};

class nike_shirt : public shirt {
public:
    void info() override {
        cout << "nike shirt\n";
    }
};

class nike_factory : public factory {
public:
    shoes* create_shoes() override {
        return new nike_shoes();
    }
    shirt* create_shirt() override {
        return new nike_shirt();
    }
};

int main() {
    nike_factory* producer = new nike_factory();
    shirt* shirt = producer->create_shirt();
    shirt->info();
    return 0;
}