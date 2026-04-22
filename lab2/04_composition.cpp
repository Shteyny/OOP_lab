#include <iostream>
#include <string>
using namespace std;

// ===== КЛАСС КОМПОНЕНТА (будет использоваться в композиции) =====
class Point {
private:
    double x;
    double y;

public:
    Point() : x(0), y(0) {
        cout << "  [Point конструктор БЕЗ параметров] " 
             << "создана ("  << x << ", " << y << ")" << endl;
    }
    
    Point(double px, double py) : x(px), y(py) {
        cout << "  [Point конструктор С параметрами] " 
             << "создана (" << x << ", " << y << ")" << endl;
    }
    
    ~Point() {
        cout << "  [Point деструктор] удалена (" << x << ", " << y << ")" << endl;
    }
    
    void display() {
        cout << "(" << x << ", " << y << ")";
    }
};

// ===== КЛАСС КОМПОНЕНТА (другой) =====
class Color {
private:
    string name;

public:
    Color() : name("unknown") {
        cout << "  [Color конструктор БЕЗ параметров] " 
             << "цвет=" << name << endl;
    }
    
    Color(string n) : name(n) {
        cout << "  [Color конструктор С параметрами] " 
             << "цвет=" << name << endl;
    }
    
    ~Color() {
        cout << "  [Color деструктор] удален цвет=" << name << endl;
    }
    
    void display() {
        cout << name;
    }
};

// ===== КОМПОЗИЦИЯ: ОБЪЕКТ (не указатель) =====
class Circle_WithObject {
private:
    Point center;      // Объект класса Point (НЕ указатель)
    Color color;       // Объект класса Color (НЕ указатель)
    double radius;

public:
    Circle_WithObject() : center(), color(), radius(1.0) {
        cout << "[Circle_WithObject конструктор БЕЗ параметров] создан\n  center: ";
        center.display();
        cout << ", radius=" << radius << endl;
    }
    
    Circle_WithObject(double x, double y, string c, double r) 
        : center(x, y), color(c), radius(r) {
        cout << "[Circle_WithObject конструктор С параметрами] создан\n";
        cout << "  center: ";
        center.display();
        cout << ", color: ";
        color.display();
        cout << ", radius=" << radius << endl;
    }
    
    ~Circle_WithObject() {
        cout << "[Circle_WithObject деструктор] удаляется:\n";
        cout << "  Удаляются композируемые объекты (центр и цвет):" << endl;
    }
    
    void display() {
        cout << "Circle: center=";
        center.display();
        cout << ", color=";
        color.display();
        cout << ", radius=" << radius << endl;
    }
};

// ===== КОМПОЗИЦИЯ: УКАЗАТЕЛЬ =====
class Circle_WithPointer {
private:
    Point *center;      // Указатель на Point
    Color *color;       // Указатель на Color
    double radius;

public:
    Circle_WithPointer() {
        cout << "[Circle_WithPointer конструктор БЕЗ параметров] создан\n";
        center = new Point();
        color = new Color();
        radius = 1.0;
        cout << "  Созданы динамические объекты center и color" << endl;
    }
    
    Circle_WithPointer(double x, double y, string c, double r) {
        cout << "[Circle_WithPointer конструктор С параметрами] создан\n";
        center = new Point(x, y);
        color = new Color(c);
        radius = r;
    }
    
    ~Circle_WithPointer() {
        cout << "[Circle_WithPointer деструктор] удаляется:\n";
        cout << "  Удаляем динамический объект center:" << endl;
        delete center;
        center = nullptr;
        
        cout << "  Удаляем динамический объект color:" << endl;
        delete color;
        color = nullptr;
    }
    
    void display() {
        cout << "Circle: center=";
        center->display();
        cout << ", color=";
        color->display();
        cout << ", radius=" << radius << endl;
    }
};

// ===== ДЕМОНСТРАЦИЯ =====
int main() {
    cout << "========== КОМПОЗИЦИЯ ОБЪЕКТОВ ==========" << endl;
    
    // 1. КОМПОЗИЦИЯ С ОБЪЕКТОМ (не указатель)
    cout << "\n1. КОМПОЗИЦИЯ С ОБЪЕКТОМ (статический объект):" << endl;
    cout << "   Команда: Circle_WithObject c1;" << endl;
    Circle_WithObject c1;
    cout << "   После создания c1:" << endl;
    c1.display();
    
    cout << "\n   Команда: Circle_WithObject c2(3.5, 4.5, \"red\", 2.5);" << endl;
    Circle_WithObject c2(3.5, 4.5, "red", 2.5);
    cout << "   После создания c2:" << endl;
    c2.display();
    
    // 2. ПОРЯДОК ДЕСТРУКТОРОВ ДЛЯ КОМПОЗИЦИИ С ОБЪЕКТОМ
    cout << "\n2. УДАЛЕНИЕ ЛОКАЛЬНОГО ОБЪЕКТА (композиция с объектом):" << endl;
    {
        cout << "   Вход в блок..." << endl;
        Circle_WithObject c3(1.0, 2.0, "blue", 3.0);
        c3.display();
        cout << "   Выход из блока..." << endl;
    }
    cout << "   ВАЖНО: Сначала удаляется сам Circle_WithObject," << endl;
    cout << "   потом его композируемые объекты Point и Color" << endl;
    
    // 3. КОМПОЗИЦИЯ С УКАЗАТЕЛЕМ
    cout << "\n3. КОМПОЗИЦИЯ С УКАЗАТЕЛЕМ (динамический объект):" << endl;
    cout << "   Команда: Circle_WithPointer *c4 = new Circle_WithPointer();" << endl;
    Circle_WithPointer *c4 = new Circle_WithPointer();
    cout << "   После создания c4:" << endl;
    c4->display();
    
    cout << "\n   Команда: Circle_WithPointer *c5 = new Circle_WithPointer(2.5, 3.5, \"green\", 4.5);" << endl;
    Circle_WithPointer *c5 = new Circle_WithPointer(2.5, 3.5, "green", 4.5);
    cout << "   После создания c5:" << endl;
    c5->display();
    
    // 4. УДАЛЕНИЕ КОМПОЗИЦИИ С УКАЗАТЕЛЕМ
    cout << "\n4. УДАЛЕНИЕ ДИНАМИЧЕСКИХ ОБЪЕКТОВ (композиция с указателем):" << endl;
    cout << "   Команда: delete c4;" << endl;
    delete c4;
    c4 = nullptr;
    
    cout << "\n   Команда: delete c5;" << endl;
    delete c5;
    c5 = nullptr;
    
    // 5. СРАВНЕНИЕ: ОБЪЕКТ vs УКАЗАТЕЛЬ
    cout << "\n5. СРАВНЕНИЕ КОМПОЗИЦИИ:" << endl;
    cout << "\n   КОМПОЗИЦИЯ С ОБЪЕКТОМ:" << endl;
    cout << "   - Композируемые объекты создаются в стеке (часть основного объекта)" << endl;
    cout << "   - Удаляются автоматически со своим объектом" << endl;
    cout << "   - ГАРАНТИРУЕТ, что Point и Color всегда существуют" << endl;
    cout << "   - Безопаснее, но может быть больше памяти" << endl;
    
    cout << "\n   КОМПОЗИЦИЯ С УКАЗАТЕЛЕМ:" << endl;
    cout << "   - Композируемые объекты создаются в куче (динамически)" << endl;
    cout << "   - НУЖНО удалять в деструкторе основного класса" << endl;
    cout << "   - Если забыть delete - утечка памяти!" << endl;
    cout << "   - Более гибкая (можно менять объекты)" << endl;
    
    // 6. КОНЕЦ MAIN
    cout << "\n6. КОНЕЦ MAIN - УДАЛЕНИЕ СТАТИЧЕСКИХ ОБЪЕКТОВ:" << endl;
    cout << "   c1 и c2 удаляются в ОБРАТНОМ порядке создания" << endl;
    
    return 0;
}

/*
КЛЮЧЕВЫЕ РАЗЛИЧИЯ:

1. КОМПОЗИЦИЯ С ОБЪЕКТОМ (Point center; Color color;):
   Создание:
   - Вход в конструктор Circle_WithObject
   - Инициализация списка: center(x, y), color(c)
   - В списке вызываются конструкторы Point и Color
   - Потом выполняется тело конструктора Circle_WithObject
   
   Удаление:
   - При удалении Circle_WithObject вызывается его деструктор
   - Потом АВТОМАТИЧЕСКИ вызываются деструкторы center и color
   - Всё происходит автоматически!

2. КОМПОЗИЦИЯ С УКАЗАТЕЛЕМ (Point *center; Color *color;):
   Создание:
   - new Point(x, y) в конструкторе (ручное создание)
   - new Color(c)
   - Объекты в куче, сам указатель в центре
   
   Удаление:
   - НУЖНО вручную delete center;
   - НУЖНО вручную delete color;
   - Если забыть - утечка памяти!
   - Компилятор не поможет!

3. РЕКОМЕНДАЦИЯ:
   - Используй объекты (не указатели) если возможно
   - Это безопаснее (RAII - Resource Acquisition Is Initialization)
   - Указатели нужны для полиморфизма и гибкости

4. СПИСОК ИНИЦИАЛИЗАЦИИ:
   - Circle_WithObject(...) : center(x, y), color(c), radius(r) {...}
   - Вызывает конструкторы членов ПЕРЕД телом конструктора
   - ВАЖНО для constexpr объектов и правильного порядка
*/
