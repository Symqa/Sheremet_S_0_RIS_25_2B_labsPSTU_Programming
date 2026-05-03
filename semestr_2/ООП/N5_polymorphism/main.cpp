#include "Object.h"
#include "Person.h"
#include "Teacher.h"
#include "Vector.h"
#include <iostream>
using namespace std;

int main() {
    Vector v(5);                     // вектор из 5 элементов
    Person p;
    Teacher t;

    cout << "Enter data for Person:" << endl;
    cin >> p;
    cout << "Enter data for Teacher:" << endl;
    cin >> t;

    Object* ptr = &p;
    v.Add(ptr);                      // добавляем Person
    ptr = &t;
    v.Add(ptr);                      // добавляем Teacher

    cout << "\nVector contents (polymorphic Show):" << endl;
    cout << v;                       // вывод всех элементов

    // Демонстрация методов Teacher
    cout << "\n--- Change teacher hours ---" << endl;
    t.IncreaseHours(10);
    cout << "After increase: " << t << endl;
    t.DecreaseHours(5);
    cout << "After decrease: " << t << endl;

    system("pause");
    return 0;
}