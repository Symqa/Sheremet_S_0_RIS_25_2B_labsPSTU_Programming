#pragma once
#include <iostream>
#include <fstream>
using namespace std;

class Pair {
private:
    int first;
    double second;
public:
    Pair();
    Pair(int, double);
    Pair(const Pair&);
    ~Pair();
    Pair& operator=(const Pair&);

    // Операции сравнения
    bool operator==(const Pair&) const;
    bool operator!=(const Pair&) const;
    bool operator<(const Pair&) const;
    bool operator>(const Pair&) const;
    bool operator<=(const Pair&) const;
    bool operator>=(const Pair&) const;

    // Вычитание константы: целая – уменьшает first, вещественная – second
    Pair operator-(int) const;
    Pair operator-(double) const;

    // Умножение на целое число (для удвоения)
    Pair& operator*=(int factor);

    // Потоковый ввод-вывод
    friend ostream& operator<<(ostream&, const Pair&);
    friend istream& operator>>(istream&, Pair&);
    friend fstream& operator<<(fstream&, const Pair&);
    friend fstream& operator>>(fstream&, Pair&);
};