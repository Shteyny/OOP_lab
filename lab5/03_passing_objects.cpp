#include <iostream>

class Base {
public:
    Base() { std::cout << "Base default constructor" << std::endl; }
    Base(const Base* obj) { std::cout << "Base copy constructor from pointer" << std::endl; }
    Base(const Base& obj) { std::cout << "Base copy constructor from reference" << std::endl; }
    ~Base() { std::cout << "Base destructor" << std::endl; }
};

class Desc : public Base {
public:
    Desc() { std::cout << "Desc default constructor" << std::endl; }
    Desc(const Desc* obj) { std::cout << "Desc copy constructor from pointer" << std::endl; }
    Desc(const Desc& obj) { std::cout << "Desc copy constructor from reference" << std::endl; }
    ~Desc() { std::cout << "Desc destructor" << std::endl; }
};

void func1(Base obj) { std::cout << "func1 called" << std::endl; }
void func2(Base* obj) { std::cout << "func2 called" << std::endl; }
void func3(Base& obj) { std::cout << "func3 called" << std::endl; }

int main() {
    std::cout << "=== Создание объектов ===" << std::endl;
    Base b;
    Desc d;

    std::cout << "\n=== Передача по значению ===" << std::endl;
    func1(b);  // Копирование
    func1(d);  // Срезка до Base

    std::cout << "\n=== Передача по указателю ===" << std::endl;
    func2(&b);
    func2(&d);

    std::cout << "\n=== Передача по ссылке ===" << std::endl;
    func3(b);
    func3(d);

    // Приведение внутри func1: невозможно безопасно привести Base к Desc, так как объект срезан.

    return 0;
}
