#include "Pair.h"
#include <iostream>
#include <cstdlib>

using namespace std;

Pair::Pair() {
    setFirst(rand()%100);
    setSecond(rand()%100);
}

Pair::Pair(int f, double s) {
    setFirst(f);
    setSecond(s);
}

Pair::Pair(const Pair &obj) {
    setFirst(obj.getFirst());
    setSecond(obj.getSecond());
}

void Pair::setFirst(int f) {
    this->first = f;
}

void Pair::setSecond(double s) {
    this->second = s;
}

int Pair::getFirst() const {
    return this->first;
}

double Pair::getSecond() const {
    return this->second;
}

Pair& Pair::operator=(const Pair &other) {
    if (this == &other) return *this;
    first = other.first;
    second = other.second;
    return *this;
}

bool Pair::operator==(const Pair &other) const {
    return (this->getFirst() == other.getFirst() && this->getSecond() == other.getSecond());
}

bool Pair::operator!=(const Pair &other) const {
    return !(this->getFirst() == other.getFirst() && this->getSecond() == other.getSecond());;
}

void Pair::operator-(const double num) {
    if (num - static_cast<int>(num) > 0) {
        this->setSecond(this->getSecond()-num);
    } else {
        this->setFirst(this->getFirst()-num);
    }
}

istream&operator>>(istream &in, Pair &pair) {
    cout << "first?"; in>>pair.first;
    cout << "second?"; in>>pair.second;
    return in;
}

ostream&operator<<(ostream &out, const Pair &pair) {
    return (out << pair.first << " : " << pair.second << endl);
}

Pair::~Pair() {
    cout << "Пара: " << first << " : " << second << " удалена." << endl;
}