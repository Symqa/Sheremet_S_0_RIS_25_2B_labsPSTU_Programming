#pragma once
#include <iostream>
#include <list>
#include <cstdlib>
#include <ctime>
#include "Pair.h"
using namespace std;

template <class T>
class List {
    list<T> lst;
public:
    List() {}
    List(int n) {
        for (int i = 0; i < n; ++i) {
            T a;
            cin >> a;
            lst.push_back(a);
        }
    }
    List(const List<T>& l) : lst(l.lst) {}

    void Print() const {
        for (auto it = lst.begin(); it != lst.end(); ++it)
            cout << *it << " ";
        cout << endl;
    }

    T Min() const {
        auto it = lst.begin();
        T m = *it;
        for (++it; it != lst.end(); ++it)
            if (*it < m) m = *it;
        return m;
    }

    void AddMinAtPos(int pos) {
        T m = Min();
        if (pos < 0 || pos > (int)lst.size()) throw 1;
        auto it = lst.begin();
        advance(it, pos);
        lst.insert(it, m);
    }

    T Average() const {
        T sum = T(); // предполагается, что T имеет конструктор по умолчанию (0,0)
        for (auto it = lst.begin(); it != lst.end(); ++it)
            sum = sum + *it;
        return sum / (int)lst.size();
    }

    void RemoveLessThanAverage() {
        T avg = Average();
        lst.remove_if([avg](const T& val) { return val < avg; });
    }

    T Max() const {
        auto it = lst.begin();
        T m = *it;
        for (++it; it != lst.end(); ++it)
            if (*it > m) m = *it;
        return m;
    }

    void DivideByMax() {
        T m = Max();
        // если m равен "нулю", нужно быть осторожным; в учебных целях пропускаем проверку
        for (auto it = lst.begin(); it != lst.end(); ++it)
            *it = *it / m;
    }
};

void task3_main() {
    try {
        cout << "\nTask3: List<int> test (change to Pair in actual)\n";
        // Для демонстрации с Pair замените int на Pair и используйте ввод.
        // В реальной работе нужно использовать List<Pair>.
        List<int> li;
        li = List<int>(5);   // требуется ввод 5 целых
        li.Print();

        int pos;
        cout << "Pos for adding min? "; cin >> pos;
        li.AddMinAtPos(pos);
        cout << "After adding min:\n";
        li.Print();

        li.RemoveLessThanAverage();
        cout << "After removing < average:\n";
        li.Print();

        li.DivideByMax();
        cout << "After dividing by max:\n";
        li.Print();
    } catch (int) {
        cout << "Error!\n";
    }
}