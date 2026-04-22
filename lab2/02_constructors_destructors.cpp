#include <iostream>
using namespace std;

// ===== КЛАСС С КОНСТРУКТОРАМИ И ДЕСТРУКТОРОМ =====
class Circle {
private:
    double radius;
    static int count;  // Для отслеживания всех объектов
    int id;

public:
    // Конструктор без параметров
    Circle() {
        radius = 0;
        id = ++count;
        cout << "[КОНСТРУКТОР БЕЗ ПАРАМЕТРОВ] Circle#" << id << " создан: radius=" << radius << endl;
    }
    
    // Конструктор с параметром
    Circle(double r) {
        radius = r;
        id = ++count;
        cout << "[КОНСТРУКТОР С ПАРАМЕТРОМ] Circle#" << id << " создан: radius=" << radius << endl;
    }
    
    // Конструктор копирования (копирование объекта в объект)
    Circle(const Circle& other) {
        radius = other.radius;
        id = ++count;
        cout << "[КОНСТРУКТОР КОПИРОВАНИЯ] Circle#" << id << " создан как копия Circle#" 
             << (other.id) << ": radius=" << radius << endl;
    }
    
    // Деструктор
    ~Circle() {
        cout << "[ДЕСТРУКТОР] Circle#" << id << " удален (был radius=" << radius << ")" << endl;
    }
    
    void display() const {
        cout << "  Circle#" << id << ": radius=" << radius << endl;
    }
    
    double getRadius() const {
        return radius;
    }
    
    void setRadius(double r) {
        radius = r;
        cout << "[Circle#" << id << "] Радиус изменён на " << radius << endl;
    }
};

int Circle::count = 0;  // Инициализация статического члена класса

// ===== ДЕМОНСТРАЦИЯ =====
int main() {
    cout << "========== КОНСТРУКТОРЫ И ДЕСТРУКТОРЫ ==========" << endl;
    
    // 1. КОНСТРУКТОР БЕЗ ПАРАМЕТРОВ - СТАТИЧЕСКИЙ ОБЪЕКТ
    cout << "\n1. КОНСТРУКТОР БЕЗ ПАРАМЕТРОВ (статический объект):" << endl;
    cout << "   Команда: Circle c1;" << endl;
    Circle c1;
    c1.display();
    
    // 2. КОНСТРУКТОР С ПАРАМЕТРОМ - СТАТИЧЕСКИЙ ОБЪЕКТ
    cout << "\n2. КОНСТРУКТОР С ПАРАМЕТРОМ (статический объект):" << endl;
    cout << "   Команда: Circle c2(5.0);" << endl;
    Circle c2(5.0);
    c2.display();
    
    // 3. КОНСТРУКТОР КОПИРОВАНИЯ - СТАТИЧЕСКИЙ ОБЪЕКТ
    cout << "\n3. КОНСТРУКТОР КОПИРОВАНИЯ (статический объект):" << endl;
    cout << "   Команда: Circle c3 = c2;" << endl;
    Circle c3 = c2;
    cout << "   Или: Circle c3(c2);" << endl;
    c3.display();
    
    // 4. ВЫЗОВ МЕТОДОВ
    cout << "\n4. ВЫЗОВ МЕТОДОВ ОБЪЕКТОВ:" << endl;
    cout << "   c1.getRadius() = " << c1.getRadius() << endl;
    cout << "   c2.getRadius() = " << c2.getRadius() << endl;
    c2.setRadius(7.5);
    
    // 5. КОНСТРУКТОР БЕЗ ПАРАМЕТРОВ - ДИНАМИЧЕСКИЙ ОБЪЕКТ
    cout << "\n5. КОНСТРУКТОР БЕЗ ПАРАМЕТРОВ (динамический объект):" << endl;
    cout << "   Команда: Circle *c4 = new Circle();" << endl;
    Circle *c4 = new Circle();
    c4->display();
    
    // 6. КОНСТРУКТОР С ПАРАМЕТРОМ - ДИНАМИЧЕСКИЙ ОБЪЕКТ
    cout << "\n6. КОНСТРУКТОР С ПАРАМЕТРОМ (динамический объект):" << endl;
    cout << "   Команда: Circle *c5 = new Circle(3.0);" << endl;
    Circle *c5 = new Circle(3.0);
    c5->display();
    
    // 7. КОНСТРУКТОР КОПИРОВАНИЯ - ДИНАМИЧЕСКИЙ ОБЪЕКТ
    cout << "\n7. КОНСТРУКТОР КОПИРОВАНИЯ (динамический объект):" << endl;
    cout << "   Команда: Circle *c6 = new Circle(*c5);" << endl;
    Circle *c6 = new Circle(*c5);
    c6->display();
    c6->setRadius(9.9);
    c5->display();  // c5 не изменился!
    
    // 8. ПОРЯДОК СОЗДАНИЯ И УДАЛЕНИЯ
    cout << "\n8. ПОРЯДОК УДАЛЕНИЯ ДИНАМИЧЕСКИХ ОБЪЕКТОВ:" << endl;
    cout << "   Команда: delete c4;" << endl;
    delete c4;
    c4 = nullptr;
    
    cout << "   Команда: delete c5;" << endl;
    delete c5;
    c5 = nullptr;
    
    cout << "   Команда: delete c6;" << endl;
    delete c6;
    c6 = nullptr;
    
    // 9. БЛОК ДЛЯ ПРОВЕРКИ ЛОКАЛЬНЫХ ОБЪЕКТОВ
    cout << "\n9. ЛОКАЛЬНЫЕ ОБЪЕКТЫ В БЛОКЕ:" << endl;
    {
        cout << "   Вход в блок..." << endl;
        Circle c7(2.0);
        Circle c8(4.0);
        cout << "   Объекты в блоке:" << endl;
        c7.display();
        c8.display();
        cout << "   Выход из блока..." << endl;
    }
    cout << "   Объекты c7 и c8 были удалены при выходе из блока" << endl;
    
    // 10. СТАТИЧЕСКИЕ ОБЪЕКТЫ УДАЛЯЮТСЯ ПРИ ВЫХОДЕ ИЗ MAIN
    cout << "\n10. КОНЕЦ MAIN - СТАТИЧЕСКИЕ ОБЪЕКТЫ УДАЛЯЮТСЯ:" << endl;
    cout << "   c1, c2, c3 будут удалены в обратном порядке создания" << endl;
    
    return 0;
}

/*
ПОРЯДОК ВЫЗОВА КОНСТРУКТОРОВ И ДЕСТРУКТОРОВ:

1. СТАТИЧЕСКИЕ ОБЪЕКТЫ:
   - Создаются в порядке объявления
   - Удаляются в ОБРАТНОМ порядке при выходе из блока
   
2. ДИНАМИЧЕСКИЕ ОБЪЕКТЫ:
   - Создаются когда вызовешь new
   - Удаляются ТОЛЬКО когда вызовешь delete
   - Если забыл delete - утечка памяти!
   
3. КОНСТРУКТОР КОПИРОВАНИЯ:
   - Автоматически вызывается когда:
     * Circle c3 = c2;
     * функция принимает объект по значению
     * функция возвращает объект
   - Копирует только значения
   - Объекты после копирования независимы

4. ЛОКАЛЬНЫЕ ОБЪЕКТЫ В БЛОКАХ:
   - Удаляются при выходе из блока
   - Даже если в блоке ошибка - деструктор вызовется
*/
