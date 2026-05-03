#include <iostream>
#include "List.h"
#include "Pair.h"
using namespace std;

int main()
{
    // Тестирование для стандартных типов
    cout << "=== Testing List<int> ===" << endl;
    List<int> intList(5, 0);
    cout << "Initial list: " << intList << endl;
    for (int i = 0; i < intList(); i++)
        intList[i] = i + 1;
    cout << "After filling: " << intList << endl;
    cout << "Size: " << intList() << endl;
    List<int> multipliedInt = intList * 2;
    cout << "After *2: " << multipliedInt << endl;
    cout << "Element [2]: " << intList[2] << endl;

    cout << "\n=== Testing List<double> ===" << endl;
    List<double> doubleList(4, 1.5);
    cout << "Initial: " << doubleList << endl;
    doubleList[0] = 2.5;
    cout << "After change: " << doubleList << endl;
    cout << "Size: " << doubleList() << endl;
    List<double> doubledDouble = doubleList * 2.0;
    cout << "After *2.0: " << doubledDouble << endl;

    // Тестирование для пользовательского класса Pair
    cout << "\n=== Testing List<Pair> ===" << endl;
    Pair p(3, 4.5);
    List<Pair> pairList(3, p);
    cout << "Initial list: " << pairList << endl;
    pairList[1] = Pair(1, 2.5);
    cout << "After change [1]: " << pairList << endl;
    cout << "Size: " << pairList() << endl;
    cout << "Element [2]: " << pairList[2] << endl;

    // Умножение списка на число 5 (5 -> Pair(5,5.0))
    cout << "Multiply list by 5 (converted to Pair(5,5.0)):" << endl;
    List<Pair> multipliedPair = pairList * 5;
    cout << multipliedPair << endl;

    // Ввод/вывод одного объекта Pair
    cout << "\nEnter a Pair (format int:double): ";
    Pair inputPair;
    cin >> inputPair;
    cout << "You entered: " << inputPair << endl;

    // Ввод списка пар
    cout << "\nEnter " << pairList() << " pairs for the list (each int:double): ";
    cin >> pairList;
    cout << "Updated list: " << pairList << endl;

    return 0;
}