#include <iostream>
#include <string>

class Base {
public:
    virtual std::string classname() const {
        return "Base";
    }

    virtual bool isA(const std::string& className) const {
        return className == "Base";
    }

    virtual ~Base() {}
};

class Derived : public Base {
public:
    std::string classname() const override {
        return "Derived";
    }

    bool isA(const std::string& className) const override {
        if (className == "Derived") return true;
        return Base::isA(className);
    }
};

class AnotherDerived : public Base {
public:
    std::string classname() const override {
        return "AnotherDerived";
    }

    bool isA(const std::string& className) const override {
        if (className == "AnotherDerived") return true;
        return Base::isA(className);
    }
};

int main() {
    Base* b1 = new Derived();
    Base* b2 = new AnotherDerived();
    Base* b3 = new Base();

    std::cout << "=== classname() ===" << std::endl;
    std::cout << "b1->classname(): " << b1->classname() << std::endl;  // "Derived"
    std::cout << "b2->classname(): " << b2->classname() << std::endl;  // "AnotherDerived"
    // Проблема: classname() не проверяет иерархию, только точный класс.

    std::cout << "\n=== isA() ===" << std::endl;
    std::cout << "b1->isA(\"Base\"): " << b1->isA("Base") << std::endl;  // true (иерархия)
    std::cout << "b1->isA(\"Derived\"): " << b1->isA("Derived") << std::endl;  // true
    std::cout << "b1->isA(\"AnotherDerived\"): " << b1->isA("AnotherDerived") << std::endl;  // false

    std::cout << "\n=== Опасное приведение (static_cast после проверки) ===" << std::endl;
    if (b1->isA("Derived")) {
        Derived* d = static_cast<Derived*>(b1);
        std::cout << "Cast successful" << std::endl;
    }

    std::cout << "\n=== dynamic_cast ===" << std::endl;
    Derived* d1 = dynamic_cast<Derived*>(b1);
    if (d1) std::cout << "dynamic_cast to Derived successful" << std::endl;
    else std::cout << "dynamic_cast to Derived failed" << std::endl;

    Derived* d2 = dynamic_cast<Derived*>(b2);  // b2 - AnotherDerived
    if (d2) std::cout << "dynamic_cast to Derived from AnotherDerived successful" << std::endl;
    else std::cout << "dynamic_cast to Derived from AnotherDerived failed" << std::endl;

    delete b1; delete b2; delete b3;
    return 0;
}
