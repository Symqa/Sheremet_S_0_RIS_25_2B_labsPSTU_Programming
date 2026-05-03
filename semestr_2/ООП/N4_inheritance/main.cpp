#include <iostream>
#include "Person.h"
#include "Teacher.h"
using namespace std;

// Глобальные функции для демонстрации принципа подстановки
void f1(Person& p) {
    cout << "\n--- Inside f1 (takes Person&) ---";
    p.SetName("Ivanov");
    cout << p;
}

Person f2() {
    Teacher t("Petrov", 30, "Math", 20);
    cout << "\n--- Inside f2 (returns Person) ---";
    cout << "\nCreated Teacher: " << t;
    return t;
}

int main() {
    cout << "========== AUTOMATIC TESTS ==========\n";

    // ------------------- Person -------------------
    cout << "\n>>> Testing class Person:\n";

    Person a;
    cout << "Default Person a: " << a;

    Person b("Sidorov", 25);
    cout << "Parameterized Person b: " << b;

    Person c(b);
    cout << "Copy-constructed Person c from b: " << c;

    a = b;
    cout << "After assignment a = b, a: " << a;

    a.SetName("UpdatedName");
    a.SetAge(30);
    cout << "After setters: " << a;

    // ------------------- Teacher -------------------
    cout << "\n>>> Testing class Teacher:\n";

    Teacher t1;
    cout << "Default Teacher t1: " << t1;

    Teacher t2("Kozlov", 40, "Physics", 15);
    cout << "Parameterized Teacher t2: " << t2;

    Teacher t3(t2);
    cout << "Copy-constructed Teacher t3 from t2: " << t3;

    t1 = t2;
    cout << "After assignment t1 = t2, t1: " << t1;

    t1.IncreaseHours(5);
    cout << "After IncreaseHours(5): " << t1;
    t1.DecreaseHours(3);
    cout << "After DecreaseHours(3): " << t1;

    // ------------------- Principle of substitution -------------------
    cout << "\n>>> Testing substitution principle:\n";
    f1(t1);            // Передаём объект Teacher в функцию, ожидающую Person&
    Person aa = f2();  // Возвращаемый Teacher присваивается в Person
    cout << "After f2(), aa (Person) = " << aa;

    // ------------------- Interactive input / output -------------------
    cout << "\n========== INTERACTIVE INPUT ==========\n";
    cout << "Now you can test the overloaded >> and << operators.\n";

    Person pInput;
    cout << "\nEnter data for a Person (name, age):";
    cin >> pInput;
    cout << "You entered: " << pInput;

    Teacher tInput;
    cout << "\nEnter data for a Teacher (name, age, subject, hours):";
    cin >> tInput;
    cout << "You entered: " << tInput;

    cout << "\n========== ALL TESTS COMPLETED ==========\n";
    return 0;
}