#include <iostream>
#include <memory>

class Base {
public:
    Base() { std::cout << "Base constructor" << std::endl; }
    ~Base() { std::cout << "Base destructor" << std::endl; }
};

void func(std::unique_ptr<Base> ptr) {
    std::cout << "func with unique_ptr" << std::endl;
}

std::unique_ptr<Base> createUnique() {
    return std::make_unique<Base>();
}

void funcShared(std::shared_ptr<Base> ptr) {
    std::cout << "func with shared_ptr" << std::endl;
}

std::shared_ptr<Base> createShared() {
    return std::make_shared<Base>();
}

int main() {
    std::cout << "=== unique_ptr ===" << std::endl;
    auto u1 = std::make_unique<Base>();
    func(std::move(u1));  // Передача владения

    auto u2 = createUnique();

    std::cout << "\n=== shared_ptr ===" << std::endl;
    auto s1 = std::make_shared<Base>();
    auto s2 = s1;  // Совместное владение
    funcShared(s1);

    auto s3 = createShared();

    return 0;
}
