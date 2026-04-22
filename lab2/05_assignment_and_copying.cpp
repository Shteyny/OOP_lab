#include <iostream>
using namespace std;

// ===== КЛАСС БЕЗ ЯВНОГО КОНСТРУКТОРА КОПИРОВАНИЯ =====
class Square {
private:
    double side;

public:
    Square() : side(0) {
        cout << "[Square] Конструктор БЕЗ параметров: side=" << side << endl;
    }
    
    Square(double s) : side(s) {
        cout << "[Square] Конструктор С параметром: side=" << side << endl;
    }
    
    ~Square() {
        cout << "[Square] Деструктор: side=" << side << endl;
    }
    
    void display() {
        cout << "  Square: side=" << side << endl;
    }
    
    double getSide() {
        return side;
    }
    
    void setSide(double s) {
        side = s;
        cout << "[Square] setSide(" << s << ") вызван" << endl;
    }
    
    double area() {
        return side * side;
    }
};

// ===== КЛАСС С ДИНАМИЧЕСКОЙ ПАМЯТЬЮ (НУЖЕН ЯВНЫЙ КОНСТРУКТОР КОПИРОВАНИЯ) =====
class Rectangle {
private:
    double *data;  // Указатель на динамическую память
    double width;
    double height;

public:
    Rectangle(double w, double h) {
        width = w;
        height = h;
        data = new double[100];
        data[0] = width * height;
        cout << "[Rectangle] Конструктор: width=" << width << ", height=" << height 
             << ", data адрес=" << data << endl;
    }
    
    // Явный конструктор копирования (ПРАВИЛЬНО)
    Rectangle(const Rectangle& other) {
        width = other.width;
        height = other.height;
        data = new double[100];  // НОВЫЙ блок памяти!
        data[0] = other.data[0];
        cout << "[Rectangle] КОНСТРУКТОР КОПИРОВАНИЯ: создан новый data адрес=" << data << endl;
    }
    
    ~Rectangle() {
        cout << "[Rectangle] Деструктор: удаляем data адрес=" << data << endl;
        delete[] data;
        data = nullptr;
    }
    
    void display() {
        cout << "  Rectangle: width=" << width << ", height=" << height 
             << ", data адрес=" << data << ", area=" << data[0] << endl;
    }
    
    double getArea() {
        return data[0];
    }
};

// ===== ДЕМОНСТРАЦИЯ =====
int main() {
    cout << "========== ПРИСВАИВАНИЕ И КОПИРОВАНИЕ ОБЪЕКТОВ ==========" << endl;
    
    // 1. КОПИРОВАНИЕ ОБЪЕКТА ПРОСТОГО КЛАССА (значения копируются)
    cout << "\n1. КОПИРОВАНИЕ ОБЪЕКТА (простой класс - только значения):" << endl;
    cout << "   Команда: Square sq1(5.0);" << endl;
    Square sq1(5.0);
    sq1.display();
    cout << "   area=" << sq1.area() << endl;
    
    cout << "\n   Команда: Square sq2 = sq1;  // Копирование" << endl;
    Square sq2 = sq1;
    cout << "   (Компилятор автоматически скопировал поля sq1 в sq2)" << endl;
    sq2.display();
    cout << "   area=" << sq2.area() << endl;
    
    // 2. НЕЗАВИСИМОСТЬ КОПИЙ
    cout << "\n2. НЕЗАВИСИМОСТЬ КОПИЙ (изменяем sq1):" << endl;
    cout << "   Команда: sq1.setSide(10.0);" << endl;
    sq1.setSide(10.0);
    cout << "   После изменения sq1:" << endl;
    cout << "   sq1: area=" << sq1.area() << endl;
    cout << "   sq2: area=" << sq2.area() << " (не изменилась!)" << endl;
    
    // 3. ПРИСВАИВАНИЕ ОБЪЕКТА
    cout << "\n3. ПРИСВАИВАНИЕ ОБЪЕКТА (оператор =):" << endl;
    cout << "   Команда: Square sq3; sq3 = sq1;  // Присваивание" << endl;
    Square sq3;
    sq3 = sq1;
    cout << "   После присваивания:" << endl;
    cout << "   sq3: area=" << sq3.area() << " (копия значений sq1)" << endl;
    
    // 4. КОПИРОВАНИЕ УКАЗАТЕЛЯ НА ПРОСТОЙ КЛАСС
    cout << "\n4. КОПИРОВАНИЕ УКАЗАТЕЛЯ (указатели на простой класс):" << endl;
    cout << "   Команда: Square *ptr1 = new Square(3.0);" << endl;
    Square *ptr1 = new Square(3.0);
    cout << "   ptr1 адрес: " << ptr1 << endl;
    
    cout << "\n   Команда: Square *ptr2 = ptr1;  // Копирование указателя" << endl;
    Square *ptr2 = ptr1;
    cout << "   ptr2 адрес: " << ptr2 << " (ТОТЖЕ адрес!)" << endl;
    cout << "   Оба указателя указывают на ОДИН объект!" << endl;
    
    cout << "\n   Команда: ptr1->setSide(15.0);" << endl;
    ptr1->setSide(15.0);
    cout << "   После изменения через ptr1:" << endl;
    cout << "   ptr1 area: " << ptr1->area() << endl;
    cout << "   ptr2 area: " << ptr2->area() << " (ИЗМЕНИЛАСЬ - один объект!)" << endl;
    
    cout << "\n   ВАЖНО: Нельзя удалять оба указателя!" << endl;
    cout << "   Команда: delete ptr1;" << endl;
    delete ptr1;
    cout << "   Объект удален" << endl;
    // ptr2->display();  // ОШИБКА: ptr2 указывает на удалённый объект (dangling pointer)
    ptr1 = nullptr;
    ptr2 = nullptr;
    
    // 5. КОПИРОВАНИЕ УКАЗАТЕЛЯ С ДИНАМИЧЕСКОЙ ПАМЯТЬЮ (проблема)
    cout << "\n5. КОПИРОВАНИЕ ОБЪЕКТА С ДИНАМИЧЕСКОЙ ПАМЯТЬЮ:" << endl;
    cout << "   Команда: Rectangle r1(4.0, 5.0);" << endl;
    Rectangle r1(4.0, 5.0);
    r1.display();
    
    cout << "\n   Команда: Rectangle r2 = r1;  // Конструктор копирования" << endl;
    Rectangle r2 = r1;
    r2.display();
    cout << "   ВАЖНО: Созданы ДВА разных блока памяти (data) !" << endl;
    
    cout << "\n6. УЧАСТЬ УКАЗАТЕЛЕЙ НА ОБЪЕКТЫ С ДИНАМИЧЕСКОЙ ПАМЯТЬЮ:" << endl;
    cout << "   Команда: Rectangle *rptr1 = new Rectangle(2.0, 3.0);" << endl;
    Rectangle *rptr1 = new Rectangle(2.0, 3.0);
    rptr1->display();
    
    cout << "\n   Команда: Rectangle *rptr2 = new Rectangle(*rptr1);  // Копирование" << endl;
    Rectangle *rptr2 = new Rectangle(*rptr1);
    rptr2->display();
    cout << "   Два раза вызвался конструктор копирования - два разных объекта" << endl;
    
    cout << "\n   Команда: delete rptr1; delete rptr2;" << endl;
    delete rptr1;
    delete rptr2;
    rptr1 = nullptr;
    rptr2 = nullptr;
    
    // 7. БАСОВЫЙ КЛАСС vs НАСЛЕДНИК
    cout << "\n7. КОПИРОВАНИЕ ОБЪЕКТА НАСЛЕДНИКА К БАЗОВОМУ:" << endl;
    cout << "   ⚠ ОПАСНО: базовый класс = наследник" << endl;
    cout << "   (произойдёт срезание объекта!)" << endl;
    
    // 8. КОНЕЦ ПРОГРАММЫ
    cout << "\n8. КОНЕЦ MAIN - УДАЛЕНИЕ СТАТИЧЕСКИХ ОБЪЕКТОВ:" << endl;
    cout << "   sq1, sq2, sq3 удаляются в ОБРАТНОМ порядке создания" << endl;
    
    return 0;
}

/*
КЛЮЧЕВЫЕ МОМЕНТЫ КОПИРОВАНИЯ:

1. КОПИРОВАНИЕ ОБЪЕКТОВ (значения):
   Square sq1(5.0);
   Square sq2 = sq1;
   
   - Все поля копируются побайтово
   - Два НЕЗАВИСИМЫХ объекта
   - Если изменить sq1 - sq2 не изменится
   - Безопасно для простых типов (int, double, string)

2. КОПИРОВАНИЕ УКАЗАТЕЛЕЙ:
   Square *ptr1 = new Square(3.0);
   Square *ptr2 = ptr1;
   
   - Копируется АДРЕС, а не объект
   - ptr1 и ptr2 указывают на ОДИН объект
   - Если изменить через ptr1 - изменится и для ptr2
   - НЕЛЬЗЯ удалять оба: delete ptr1; delete ptr2; - ОШИБКА!
   - После delete ptr1 - ptr2 становится dangling pointer

3. КОНСТРУКТОР КОПИРОВАНИЯ (copy constructor):
   Rectangle(const Rectangle& other) {
       data = new double[100];  // НОВЫЙ блок памяти!
       data[0] = other.data[0];
   }
   
   - Вызывается при: Rectangle r2 = r1; или Rectangle r2(r1);
   - НУЖЕН если есть динамическая память!
   - Если не определить - копируется адрес (ОПАСНО - две стрелки на один блок!)
   - Rule of Three: если определил destructor - нужны copy constructor и operator=

4. ПРИСВАИВАНИЕ (оператор =):
   Square sq3;
   sq3 = sq1;  // Уже существующий объект!
   
   - Отличается от конструктора копирования
   - Может быть перегружен
   - Default версия копирует поля

5. СРЕЗАНИЕ ОБЪЕКТА:
   Shape s = rectangle;  // rectangle - это Rectangle
   
   - Копируется только часть Rectangle которая является Shape
   - Остальные данные теряются
   - РЕШЕНИЕ: использовать указатели и virtual методы

6. DANGLING POINTER:
   int *p = new int(5);
   int *p2 = p;
   delete p;  // Объект удален
   p2->...   // ОШИБКА - dangling pointer!
*/
