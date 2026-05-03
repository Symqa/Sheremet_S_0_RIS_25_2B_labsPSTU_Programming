#include "Number.h"
#include <iostream>

using namespace std;


Number::Number() {
    first = 1;
    second = 0.0;
}


void Number::Init(int f, double s) {
    if (f <= 0) {
        cout << endl << "Ошибка: аргумент first должен быть > 0" << endl;
        f = 1;
    }
    if (s < 0 || s >= 1) {
        cout << endl << "Ошибка: аргумент second должен быть 0 <= second < 1" << endl;
        s = 0.0;
    }
    

    first = f;
    second = s;
    
}


void Number::Read() {
    int f;
    double s;

    cout << "Введите целую часть (>0): ";
    cin >> f;
    cout << "Введите дробную часть (>=0): ";
    cin >> s;
    Init(f, s);
}


void Number::Show() const {

    cout << "Целая часть: " << first << ", дробная часть: " << second << endl;
}


double Number::multiply(double k) {
    return getValue()*k;
} 


double Number::getValue() const {
    return first+second;
}


Number make_Number(int f, double s) {
    Number temp;
    temp.Init(f, s);
    return temp;
}