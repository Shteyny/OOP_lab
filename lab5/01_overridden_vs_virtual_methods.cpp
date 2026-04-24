#include <iostream>

class Base {
public:
    // Невиртуальный метод
    void nonVirtualMethod() {
        std::cout << "Base::nonVirtualMethod called" << std::endl;
        internalMethod();  // Вызывает невиртуальный internalMethod
    }

    // Виртуальный метод
    virtual void virtualMethod() {
        std::cout << "Base::virtualMethod called" << std::endl;
        internalVirtualMethod();  // Вызывает виртуальный internalVirtualMethod
    }

    void internalMethod() {
        std::cout << "Base::internalMethod called" << std::endl;
    }

    virtual void internalVirtualMethod() {
        std::cout << "Base::internalVirtualMethod called" << std::endl;
    }

    virtual ~Base() {
        std::cout << "Base destructor called" << std::endl;
    }
};

class Derived : public Base {
public:
    // Перекрываемый метод (не виртуальный в базовом)
    void nonVirtualMethod() {
        std::cout << "Derived::nonVirtualMethod called" << std::endl;
    }

    // Виртуальный метод
    void virtualMethod() override {
        std::cout << "Derived::virtualMethod called" << std::endl;
        internalVirtualMethod();  // Вызывает переопределенный
    }

    void internalMethod() {
        std::cout << "Derived::internalMethod called" << std::endl;
    }

    void internalVirtualMethod() override {
        std::cout << "Derived::internalVirtualMethod called" << std::endl;
    }

    ~Derived() override {
        std::cout << "Derived destructor called" << std::endl;
    }
};

int main() {
    std::cout << "=== Перекрываемые методы ===" << std::endl;
    Derived d;
    d.nonVirtualMethod();  // Вызывается Derived::nonVirtualMethod

    Base* pb = &d;
    pb->nonVirtualMethod();  // Вызывается Base::nonVirtualMethod (не виртуальный)

    std::cout << "\n=== Виртуальные методы ===" << std::endl;
    d.virtualMethod();  // Вызывается Derived::virtualMethod
    pb->virtualMethod();  // Вызывается Derived::virtualMethod (виртуальный)

    std::cout << "\n=== Вызов из базового метода ===" << std::endl;
    // nonVirtualMethod вызывает internalMethod (невиртуальный) - Base::internalMethod
    pb->nonVirtualMethod();
    // virtualMethod вызывает internalVirtualMethod (виртуальный) - Derived::internalVirtualMethod
    pb->virtualMethod();

    std::cout << "\n=== Виртуальный деструктор ===" << std::endl;
    Base* p = new Derived();
    delete p;  // Вызывается Derived::~Derived, затем Base::~Base

    return 0;
}
