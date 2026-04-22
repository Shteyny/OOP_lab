#include <iostream>
using namespace std;

// ===== КЛАСС С РАЗНЫМИ УРОВНЯМИ ДОСТУПА =====
class Person {
private:
    // PRIVATE - доступны ТОЛЬКО внутри класса
    string ssn;  // Номер социального страхования (конфиденциальные данные)
    double salary;  // Зарплата (конфиденциально)

protected:
    // PROTECTED - доступны в классе и в наследниках
    string name;
    int age;

public:
    // PUBLIC - доступны везде (снаружи класса и в наследниках)
    string department;
    
    // Конструктор
    Person(string n, int a, string d, string s, double sal) {
        name = n;
        age = a;
        department = d;
        ssn = s;
        salary = sal;
    }
    
    // PUBLIC методы для безопасного доступа к private данным
    void displayInfo() {
        cout << "Имя: " << name << endl;
        cout << "Возраст: " << age << endl;
        cout << "Отдел: " << department << endl;
        // Можем получить доступ к private полям ИЗ методов класса
        cout << "Зарплата: $" << salary << endl;
    }
    
    // Метод для получения SSN с проверкой (инкапсуляция)
    string getSSN() {
        return ssn;
    }
    
    // Метод для изменения зарплаты с валидацией
    void setSalary(double newSalary) {
        if (newSalary > 0) {
            salary = newSalary;
            cout << "Зарплата обновлена!" << endl;
        } else {
            cout << "Ошибка: зарплата должна быть положительной!" << endl;
        }
    }
};

// ===== НАСЛЕДНИК КЛАССА =====
class Manager : public Person {
private:
    int teamSize;  // private в менеджере

public:
    int bonusPercent;  // public в менеджере
    
    Manager(string n, int a, string d, string s, double sal, int ts, int bp)
        : Person(n, a, d, s, sal), teamSize(ts), bonusPercent(bp) {}
    
    void displayManagerInfo() {
        cout << "\n--- ИНФОРМАЦИЯ О МЕНЕДЖЕРЕ ---" << endl;
        
        // ✓ Можем получить доступ к protected полям из наследника
        cout << "Имя менеджера: " << name << endl;
        cout << "Возраст: " << age << endl;
        
        // ✓ Можем получить доступ к public полям
        cout << "Отдел: " << department << endl;
        cout << "Размер команды: " << teamSize << endl;
        cout << "Процент бонуса: " << bonusPercent << "%" << endl;
        
        // ✗ НЕ можем получить доступ к private полям базового класса
        // cout << "SSN: " << ssn << endl;  // ОШИБКА КОМПИЛЯТОРА!
        // cout << "Зарплата: " << salary << endl;  // ОШИБКА КОМПИЛЯТОРА!
        
        // Но можем вызвать public методы, которые работают с private
        displayInfo();
    }
};

// ===== ДЕМОНСТРАЦИЯ =====
int main() {
    cout << "=== ДЕМОНСТРАЦИЯ УРОВНЕЙ ДОСТУПА В C++ ===" << endl;
    
    // Создаём объект Person
    Person employee("Иван Петров", 30, "IT", "123-45-6789", 3000);
    
    cout << "\n1. ДОСТУП К PUBLIC ПОЛЯМ (разрешён):" << endl;
    cout << "Отдел: " << employee.department << endl;  // ✓ OK
    employee.department = "HR";
    cout << "Новый отдел: " << employee.department << endl;
    
    cout << "\n2. ДОСТУП К PROTECTED ПОЛЯМ (запрещён снаружи класса):" << endl;
    // cout << "Имя: " << employee.name << endl;  // ✗ ОШИБКА КОМПИЛЯТОРА!
    // employee.age = 25;  // ✗ ОШИБКА КОМПИЛЯТОРА!
    cout << "⚠ Protected поля недоступны снаружи класса" << endl;
    
    cout << "\n3. ДОСТУП К PRIVATE ПОЛЯМ (запрещён снаружи класса):" << endl;
    // cout << "SSN: " << employee.ssn << endl;  // ✗ ОШИБКА КОМПИЛЯТОРА!
    // cout << "Зарплата: " << employee.salary << endl;  // ✗ ОШИБКА КОМПИЛЯТОРА!
    cout << "⚠ Private поля недоступны снаружи класса" << endl;
    
    cout << "\n4. ДОСТУП ЧЕРЕЗ PUBLIC МЕТОДЫ (разрешён):" << endl;
    employee.displayInfo();  // ✓ Метод может получить доступ ко ВСЕМ полям
    
    cout << "\n5. ИЗМЕНЕНИЕ ЧЕРЕЗ МЕТОДЫ (с валидацией):" << endl;
    employee.setSalary(3500);  // ✓ OK
    employee.setSalary(-1000);  // ✗ Валидация не позволит
    
    cout << "\n6. НАСЛЕДОВАНИЕ И PROTECTED:" << endl;
    Manager manager("Мария Сидорова", 35, "IT", "987-65-4321", 5000, 5, 15);
    manager.displayManagerInfo();
    
    cout << "\n" << endl;
    
    // ТАБЛИЦА ПРАВ ДОСТУПА
    cout << "=== ТАБЛИЦА ПРАВ ДОСТУПА ===" << endl;
    cout << "+------------------+--------+----------+--------+" << endl;
    cout << "| Область          | PRIVATE| PROTECTED| PUBLIC |" << endl;
    cout << "+------------------+--------+----------+--------+" << endl;
    cout << "| Внутри класса     |   ✓    |    ✓     |   ✓    |" << endl;
    cout << "| В наследнике      |   ✗    |    ✓     |   ✓    |" << endl;
    cout << "| Снаружи класса    |   ✗    |    ✗     |   ✓    |" << endl;
    cout << "+------------------+--------+----------+--------+" << endl;
    
    return 0;
}

/*
ОБЪЯСНЕНИЕ:

1. PRIVATE (приватный)
   - Доступен ТОЛЬКО внутри класса
   - Используется для скрытия имплементации (инкапсуляция)
   - Наследники НЕ могут получить доступ
   - Пример: ssn, salary

2. PROTECTED (защищённый)
   - Доступен внутри класса и в наследниках
   - Скрыт от внешнего мира
   - Наследники МОГУТ получить доступ
   - Пример: name, age

3. PUBLIC (публичный)
   - Доступен везде: внутри класса, в наследниках, снаружи класса
   - Часть интерфейса класса
   - Пример: department, bonusPercent

ПРАВИЛО ПРИНЦИПА ИНКАПСУЛЯЦИИ:
- Данные обычно private
- Методы для безопасного доступа - public
- Это позволяет контролировать, как данные изменяются
*/
