#include <iostream>

class Base {
public:
    Base() { std::cout << "Base constructor" << std::endl; }
    Base(const Base& obj) { std::cout << "Base copy constructor" << std::endl; }
    ~Base() { std::cout << "Base destructor" << std::endl; }
};

Base func1() { Base b; return b; }  // Статический объект
Base* func2() { Base* b = new Base(); return b; }  // Динамический
Base& func3() { static Base b; return b; }  // Статический

Base func4() { return Base(); }  // Динамический (new внутри)
Base* func5() { return new Base(); }
Base& func6() { static Base b; return b; }

int main() {
    std::cout << "=== Возврат статического объекта ===" << std::endl;
    Base b1 = func1();  // Копирование
    Base* b2 = func2();  // Указатель, нужно delete
    Base& b3 = func3();  // Ссылка на статический

    std::cout << "\n=== Возврат динамического объекта ===" << std::endl;
    Base b4 = func4();  // Копирование временного
    Base* b5 = func5();  // Указатель
    Base& b6 = func6();  // Ссылка

    delete b2; delete b5;  // Правильное управление памятью
    return 0;
}
