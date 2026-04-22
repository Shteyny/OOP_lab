#include <iostream>
using namespace std;

// ===== БАЗОВЫЙ КЛАСС =====
class Shape {
public:
    Shape() {
        cout << "[Shape конструктор] создана фигура" << endl;
    }
    
    ~Shape() {
        cout << "[Shape деструктор] удалена фигура" << endl;
    }
    
    // Метод в базовом классе
    void describe() {
        cout << "Это фигура" << endl;
    }
    
    void draw() {
        cout << "Рисую абстрактную фигуру" << endl;
    }
};

// ===== НАСЛЕДНИК 1 =====
class Circle : public Shape {
private:
    double radius;

public:
    Circle(double r) : radius(r) {
        cout << "[Circle конструктор] создан круг с radius=" << radius << endl;
    }
    
    ~Circle() {
        cout << "[Circle деструктор] удален круг" << endl;
    }
    
    // Переопределение метода describe
    void describe() {
        cout << "Это круг с radius=" << radius << endl;
    }
    
    // Переопределение метода draw
    void draw() {
        Shape::draw();  // Вызов базового метода (не обязательно, но можно)
        cout << "Рисую круг с radius=" << radius << endl;
    }
    
    // Новый метод только в Circle
    void printArea() {
        cout << "Площадь круга: " << 3.14159 * radius * radius << endl;
    }
};

// ===== НАСЛЕДНИК 2 =====
class Rectangle : public Shape {
private:
    double width, height;

public:
    Rectangle(double w, double h) : width(w), height(h) {
        cout << "[Rectangle конструктор] создан прямоугольник " 
             << width << "x" << height << endl;
    }
    
    ~Rectangle() {
        cout << "[Rectangle деструктор] удален прямоугольник" << endl;
    }
    
    // Переопределение метода describe
    void describe() {
        cout << "Это прямоугольник " << width << "x" << height << endl;
    }
    
    // Переопределение метода draw
    void draw() {
        cout << "Рисую прямоугольник " << width << "x" << height << endl;
    }
    
    // Новый метод только в Rectangle
    void printArea() {
        cout << "Площадь прямоугольника: " << width * height << endl;
    }
};

// ===== НАСЛЕДНИК БЕЗ ПЕРЕОПРЕДЕЛЕНИЯ =====
class Triangle : public Shape {
private:
    double base, height;

public:
    Triangle(double b, double h) : base(b), height(h) {
        cout << "[Triangle конструктор] создан треугольник" << endl;
    }
    
    ~Triangle() {
        cout << "[Triangle деструктор] удален треугольник" << endl;
    }
    
    // НЕ переопределяем describe и draw - используем из базового класса
};

// ===== ДЕМОНСТРАЦИЯ =====
int main() {
    cout << "========== ПЕРЕОПРЕДЕЛЕНИЕ МЕТОДОВ ==========\n" << endl;
    
    // 1. БАЗОВЫЙ КЛАСС
    cout << "1. ОБЪЕКТ БАЗОВОГО КЛАССА:" << endl;
    Shape shape;
    shape.describe();
    shape.draw();
    
    // 2. НАСЛЕДНИК 1 СО СВОЕЙ РЕАЛИЗАЦИЕЙ
    cout << "\n2. ОБЪЕКТ Circle (переопределены методы):" << endl;
    Circle circle(5.0);
    circle.describe();
    circle.draw();
    circle.printArea();
    
    // 3. НАСЛЕДНИК 2 СО СВОЕЙ РЕАЛИЗАЦИЕЙ
    cout << "\n3. ОБЪЕКТ Rectangle (переопределены методы):" << endl;
    Rectangle rect(4.0, 6.0);
    rect.describe();
    rect.draw();
    rect.printArea();
    
    // 4. НАСЛЕДНИК БЕЗ ПЕРЕОПРЕДЕЛЕНИЯ
    cout << "\n4. ОБЪЕКТ Triangle (БЕЗ переопределения методов):" << endl;
    Triangle triangle(3.0, 4.0);
    triangle.describe();  // Использует из базового класса!
    triangle.draw();      // Использует из базового класса!
    
    // 5. СТАТИЧЕСКИЙ ОБЪЕКТ vs УКАЗАТЕЛЬ БАЗОВОГО КЛАССА
    cout << "\n5. СТАТИЧЕСКИЕ ОБЪЕКТЫ (каждый свой тип):" << endl;
    cout << "   Каждый объект использует ВСЕ встроенные методы своего класса" << endl;
    
    cout << "\n6. УКАЗАТЕЛЬ БАЗОВОГО КЛАССА (БЕЗ VIRTUAL):" << endl;
    cout << "   Shape *s1 = &shape;" << endl;
    Shape *s1 = &shape;
    cout << "   s1->describe(): ";
    s1->describe();
    cout << "   s1->draw(): ";
    s1->draw();
    
    cout << "\n   Shape *s2 = &circle;" << endl;
    Shape *s2 = &circle;
    cout << "   s2->describe(): ";
    s2->describe();  // ⚠ Вызовет Shape::describe (БЕЗ virtual)!
    cout << "   s2->draw(): ";
    s2->draw();      // ⚠ Вызовет Shape::draw (БЕЗ virtual)!
    
    cout << "\n   Shape *s3 = &rect;" << endl;
    Shape *s3 = &rect;
    cout << "   s3->describe(): ";
    s3->describe();  // ⚠ Вызовет Shape::describe!
    cout << "   s3->draw(): ";
    s3->draw();      // ⚠ Вызовет Shape::draw!
    
    cout << "\n   Shape *s4 = &triangle;" << endl;
    Shape *s4 = &triangle;
    cout << "   s4->describe(): ";
    s4->describe();  // Вызовет Shape::describe (triangle его не переопределяет)
    cout << "   s4->draw(): ";
    s4->draw();      // Вызовет Shape::draw (triangle его не переопределяет)
    
    // 7. ЯВНОЕ ВЫЗОВ МЕТОДА БАЗОВОГО КЛАССА ИЗ НАСЛЕДНИКА
    cout << "\n7. ЯВНЫЙ ВЫЗОВ МЕТОДА БАЗОВОГО КЛАССА:" << endl;
    cout << "   Circle::describe() - в теле методы можно вызвать Shape::describe()" << endl;
    cout << "   Но это нужно делать явно: Shape::describe() или Shape::draw() и т.д." << endl;
    
    // 8. ОБЪЕКТ ДИНАМИЧЕСКИЙ
    cout << "\n8. ДИНАМИЧЕСКИЕ ОБЪЕКТЫ:" << endl;
    Circle *pc = new Circle(7.0);
    cout << "   pc->describe(): ";
    pc->describe();
    cout << "   pc->printArea(): ";
    pc->printArea();
    
    cout << "\n   Shape *ps = dynamic_cast<Shape*>(pc);" << endl;
    Shape *ps = pc;
    cout << "   ps->describe(): ";
    ps->describe();  // ⚠ Shape::describe (БЕЗ virtual)
    
    delete pc;
    pc = nullptr;
    
    // 9. МАССИВ УКАЗАТЕЛЕЙ НА РАЗНЫЕ НАСЛЕДНИКИ
    cout << "\n9. МАССИВ УКАЗАТЕЛЕЙ НА БАЗОВЫЙ КЛАСС:" << endl;
    Shape *shapes[3];
    shapes[0] = new Circle(2.0);
    shapes[1] = new Rectangle(3.0, 4.0);
    shapes[2] = new Triangle(5.0, 6.0);
    
    cout << "   Вызов describe() для всех:" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "   shapes[" << i << "]: ";
        shapes[i]->describe();  // ⚠ Вызовет Shape::describe (БЕЗ virtual)
    }
    
    cout << "\n   Удаление:" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "   Удаляем shapes[" << i << "]: " << endl;
        delete shapes[i];
    }
    
    cout << "\n10. КОНЕЦ MAIN:" << endl;
    
    return 0;
}

/*
КЛЮЧЕВЫЕ МОМЕНТЫ ПЕРЕОПРЕДЕЛЕНИЯ (БЕЗ VIRTUAL):

1. ЧТО ПРОИСХОДИТ БЕЗ VIRTUAL:
   - Shape::describe() - вызовет Shape::describe
   - Circle::describe() - вызовет Circle::describe
   - Rectangle::describe() - вызовет Rectangle::describe
   
   НО если через указатель базового класса:
   - Shape *s = new Circle(...);
   - s->describe(); - вызовет Shape::describe (НЕ Circle::describe!)
   
   Компилятор использует тип УКАЗАТЕЛЯ, не ОБЪЕКТА!

2. ПЕРЕОПРЕДЕЛЕНИЕ (override):
   - Метод в наследнике имеет ТО ЖЕ имя и параметры
   - Полностью заменяет метод базового класса
   - Статическая диспетчеризация (compile-time binding)

3. ДЛЯ ДИНАМИЧЕСКОЙ ДИСПЕТЧЕРИЗАЦИИ (runtime):
   - Нужно использовать virtual методы
   - Shape *s = new Circle(...);
   - s->describe(); - вызовет Circle::describe (правильно)

4. НАСЛЕДНИК БЕЗ ПЕРЕОПРЕДЕЛЕНИЯ:
   - Triangle использует Shape::describe и Shape::draw
   - Это нормально, если поведение подходит

5. СПЕЦИФИЧНЫЕ МЕТОДЫ:
   - pc->printArea(); - работает для Circle
   - ps->printArea(); - НЕ компилируется! Shape не имеет printArea()
   - Нужно явное приведение типа или virtual методы

6. ПРИВЕДЕНИЕ ТИПОВ:
   Shape *ps = new Circle(...);
   Circle *pc = (Circle *)ps;  // C-style cast
   pc->printArea();            // Работает!
   
   Или:
   pc = dynamic_cast<Circle*>(ps);  // Более безопасно
   if (pc) pc->printArea();
*/
