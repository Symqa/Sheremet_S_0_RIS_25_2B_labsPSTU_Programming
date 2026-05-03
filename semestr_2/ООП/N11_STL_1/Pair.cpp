#include "Pair.h"

Pair& Pair::operator=(const Pair& p) {
    if (this == &p) return *this;
    first = p.first;
    second = p.second;
    return *this;
}

bool Pair::operator<(const Pair& p) const {
    if (first < p.first) return true;
    if (first == p.first && second < p.second) return true;
    return false;
}

bool Pair::operator>(const Pair& p) const {
    if (first > p.first) return true;
    if (first == p.first && second > p.second) return true;
    return false;
}

bool Pair::operator==(const Pair& p) const {
    return first == p.first && second == p.second;
}

bool Pair::operator!=(const Pair& p) const {
    return !(*this == p);
}

Pair Pair::operator+(const Pair& p) const {
    return Pair(first + p.first, second + p.second);
}

Pair Pair::operator/(const Pair& p) const {
    return Pair(first / p.first, second / p.second);
}

Pair Pair::operator/(const int& n) const {
    return Pair(first / n, second / n);
}

istream& operator>>(istream& in, Pair& p) {
    cout << "first? "; in >> p.first;
    cout << "second? "; in >> p.second;
    return in;
}

ostream& operator<<(ostream& out, const Pair& p) {
    return out << p.first << ":" << p.second;
}