#include <iostream>
using namespace std;

// ===== БАЗОВЫЙ КЛАСС =====
class Shape {
private:
    string color;

protected:
    string name;

public:
    Shape() {
        name = "Shape";
        color = "unknown";
        cout << "[КОНСТРУКТОР Shape] Базовый класс создан: name=" << name << endl;
    }
    
    Shape(string n, string c) {
        name = n;
        color = c;
        cout << "[КОНСТРУКТОР Shape] Базовый класс создан: name=" << name << ", color=" << color << endl;
    }
    
    ~Shape() {
        cout << "[ДЕСТРУКТОР Shape] Базовый класс удален: name=" << name << endl;
    }
    
    void displayBase() {
        cout << "  Фигура: " << name << ", цвет: " << color << endl;
    }
    
    string getName() const {
        return name;
    }
};

// ===== КЛАСС-НАСЛЕДНИК (с собственным конструктором и деструктором) =====
class Rectangle : public Shape {
private:
    double width;
    double height;

public:
    Rectangle() {
        width = 0;
        height = 0;
        cout << "[КОНСТРУКТОР Rectangle] Наследник создан: width=" << width << ", height=" << height << endl;
    }
    
    Rectangle(string n, string c, double w, double h) : Shape(n, c) {
        width = w;
        height = h;
        cout << "[КОНСТРУКТОР Rectangle] Наследник создан: width=" << width << ", height=" << height << endl;
    }
    
    Rectangle(const Rectangle& other) : Shape(other.getName(), "copied") {
        width = other.width;
        height = other.height;
        cout << "[КОНСТРУКТОР КОПИРОВАНИЯ Rectangle] Наследник скопирован" << endl;
    }
    
    ~Rectangle() {
        cout << "[ДЕСТРУКТОР Rectangle] Наследник удален: width=" << width << ", height=" << height << endl;
    }
    
    void display() {
        displayBase();
        cout << "  Прямоугольник: " << width << " x " << height << endl;
    }
    
    double area() {
        return width * height;
    }
};

// ===== КЛАСС-НАСЛЕДНИК (БЕЗ конструктора и деструктора) =====
class Triangle : public Shape {
private:
    double base;
    double height;

public:
    void display() {
        cout << "  Треугольник: base=" << base << ", height=" << height << endl;
    }
    
    void setDimensions(double b, double h) {
        base = b;
        height = h;
        cout << "[Triangle] Размеры установлены: base=" << base << ", height=" << height << endl;
    }
};

// ===== ДЕМОНСТРАЦИЯ =====
int main() {
    cout << "========== НАСЛЕДОВАНИЕ И ИЕРАРХИЯ КЛАССОВ ==========" << endl;
    
    // 1. ОБЪЕКТ БАЗОВОГО КЛАССА
    cout << "\n1. ОБЪЕКТ БАЗОВОГО КЛАССА (статический):" << endl;
    cout << "   Команда: Shape s1;" << endl;
    Shape s1;
    s1.displayBase();
    
    cout << "\n   Команда: Shape s2(\"MyShape\", \"red\");" << endl;
    Shape s2("MyShape", "red");
    s2.displayBase();
    
    // 2. ОБЪЕКТ НАСЛЕДНИКА (с конструктором) - СТАТИЧЕСКИЙ
    cout << "\n2. ОБЪЕКТ НАСЛЕДНИКА с конструктором (статический):" << endl;
    cout << "   Команда: Rectangle r1;" << endl;
    Rectangle r1;
    cout << "   Обратите внимание: сначала конструктор Shape, потом Rectangle!" << endl;
    r1.display();
    
    // 3. ОБЪЕКТ НАСЛЕДНИКА С ПАРАМЕТРАМИ
    cout << "\n3. ОБЪЕКТ НАСЛЕДНИКА с параметрами:" << endl;
    cout << "   Команда: Rectangle r2(\"Square\", \"blue\", 4.0, 4.0);" << endl;
    Rectangle r2("Square", "blue", 4.0, 4.0);
    r2.display();
    cout << "   Площадь: " << r2.area() << endl;
    
    // 4. КОНСТРУКТОР КОПИРОВАНИЯ НАСЛЕДНИКА
    cout << "\n4. КОНСТРУКТОР КОПИРОВАНИЯ НАСЛЕДНИКА:" << endl;
    cout << "   Команда: Rectangle r3 = r2;" << endl;
    Rectangle r3 = r2;
    r3.display();
    
    // 5. ОБЪЕКТ НАСЛЕДНИКА БЕЗ КОНСТРУКТОРА
    cout << "\n5. ОБЪЕКТ НАСЛЕДНИКА без собственного конструктора:" << endl;
    cout << "   Команда: Triangle t1;" << endl;
    Triangle t1;
    cout << "   Вызвался конструктор базового класса Shape (без параметров)" << endl;
    t1.display();
    
    // 6. ДИНАМИЧЕСКИЙ ОБЪЕКТ НАСЛЕДНИКА
    cout << "\n6. ДИНАМИЧЕСКИЙ ОБЪЕКТ НАСЛЕДНИКА:" << endl;
    cout << "   Команда: Rectangle *r4 = new Rectangle(\"Rect\", \"green\", 3.0, 5.0);" << endl;
    Rectangle *r4 = new Rectangle("Rect", "green", 3.0, 5.0);
    r4->display();
    cout << "   Площадь: " << r4->area() << endl;
    
    // 7. УКАЗАТЕЛЬ БАЗОВОГО КЛАССА НА ОБЪЕКТ НАСЛЕДНИКА
    cout << "\n7. УКАЗАТЕЛЬ БАЗОВОГО КЛАССА НА ОБЪЕКТ НАСЛЕДНИКА:" << endl;
    cout << "   Команда: Shape *shape = new Rectangle(\"Poly\", \"yellow\", 2.0, 3.0);" << endl;
    Shape *shape = new Rectangle("Poly", "yellow", 2.0, 3.0);
    cout << "   Важно: shape - это указатель на Shape, но указывает на Rectangle!" << endl;
    shape->displayBase();  // ✓ Можем вызвать метод базового класса
    // ВНИМАНИЕ: shape->area() - НЕ сработает! Компилятор не знает об area() в Shape
    cout << "   ⚠ shape->area() - нельзя вызвать, так как Shape не содержит area()" << endl;
    Rectangle *rect = (Rectangle *)shape;  // Приведение типа
    cout << "   После приведения типа: rect->area() = " << rect->area() << endl;
    
    // 8. ОБЪЕКТ НАСЛЕДНИКА В ПЕРЕМЕННУЮ БАЗОВОГО КЛАССА (БЕЗ указателя)
    cout << "\n8. ПРИСВАИВАНИЕ ОБЪЕКТА НАСЛЕДНИКА К ОБЪЕКТУ БАЗОВОГО КЛАССА:" << endl;
    cout << "   Команда: Shape s3 = r2;" << endl;
    Shape s3 = r2;
    cout << "   ВАЖНО: Произойдёт СРЕЗАНИЕ объекта (только базовая часть скопируется)!" << endl;
    s3.displayBase();
    cout << "   Данные класса Rectangle потеряны!" << endl;
    
    // 9. ПОРЯДОК ВЫЗОВА ДЕСТРУКТОРОВ
    cout << "\n9. УДАЛЕНИЕ ДИНАМИЧЕСКИХ ОБЪЕКТОВ:" << endl;
    cout << "   При удалении наследника сначала вызывается ДЕСТРУКТОР НАСЛЕДНИКА," << endl;
    cout << "   затем ДЕСТРУКТОР БАЗОВОГО КЛАССА" << endl;
    cout << "\n   Команда: delete r4;" << endl;
    delete r4;
    r4 = nullptr;
    
    cout << "\n   Команда: delete shape;" << endl;
    delete shape;
    shape = nullptr;
    
    // 10. КОНЕЦ MAIN
    cout << "\n10. КОНЕЦ MAIN - ПОРЯДОК УДАЛЕНИЯ СТАТИЧЕСКИХ ОБЪЕКТОВ:" << endl;
    cout << "   s1, s2, r1, r2, r3, t1, s3 удаляются в ОБРАТНОМ порядке создания" << endl;
    cout << "   Для каждого объекта наследника: сначала его деструктор, потом базового класса" << endl;
    
    return 0;
}

/*
КЛЮЧЕВЫЕ МОМЕНТЫ НАСЛЕДОВАНИЯ:

1. БЕЗ КОНСТРУКТОРА В НАСЛЕДНИКЕ:
   - Используется конструктор базового класса
   - Поля наследника не инициализируются!

2. С КОНСТРУКТОРОМ В НАСЛЕДНИКЕ:
   - СНАЧАЛА вызывается конструктор базового класса (или явно через :)
   - ПОТОМ конструктор наследника
   - Список инициализации: Rectangle(...) : Shape(...) {...}

3. УКАЗАТЕЛЬ БАЗОВОГО КЛАССА НА ОБЪЕКТ НАСЛЕДНИКА:
   - Shape *s = new Rectangle(...); - ОК
   - Можем вызывать методы базового класса
   - Нельзя вызывать специфичные методы наследника
   - Нужно приведение типа или virtual методы

4. ПОРЯДОК УДАЛЕНИЯ:
   - delete (Rectangle*) - сначала ~Rectangle, потом ~Shape
   - Это важно, если в наследнике есть динамическая память

5. СРЕЗАНИЕ ОБЪЕКТА:
   - Shape s = rectangle; - копируется только базовая часть
   - Данные наследника теряются
   - Нужно использовать указатели!
*/
