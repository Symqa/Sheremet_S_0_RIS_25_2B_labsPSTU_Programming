#include "Pair.h"

Pair::Pair() : first(0), second(0.0) {}
Pair::Pair(int f, double s) : first(f), second(s) {}
Pair::Pair(const Pair& p) : first(p.first), second(p.second) {}
Pair::~Pair() {}

Pair& Pair::operator=(const Pair& p) {
    if (this == &p) return *this;
    first = p.first;
    second = p.second;
    return *this;
}

bool Pair::operator==(const Pair& p) const {
    return (first == p.first) && (second == p.second);
}
bool Pair::operator!=(const Pair& p) const {
    return !(*this == p);
}
bool Pair::operator<(const Pair& p) const {
    if (first < p.first) return true;
    if (first > p.first) return false;
    return second < p.second;
}
bool Pair::operator>(const Pair& p) const {
    return p < *this;
}
bool Pair::operator<=(const Pair& p) const {
    return !(*this > p);
}
bool Pair::operator>=(const Pair& p) const {
    return !(*this < p);
}

Pair Pair::operator-(int val) const {
    Pair res(*this);
    res.first -= val;
    return res;
}
Pair Pair::operator-(double val) const {
    Pair res(*this);
    res.second -= val;
    return res;
}

Pair& Pair::operator*=(int factor) {
    first *= factor;
    second *= factor;
    return *this;
}

ostream& operator<<(ostream& out, const Pair& p) {
    out << p.first << ":" << p.second;
    return out;
}
istream& operator>>(istream& in, Pair& p) {
    cout << "first (int)? "; in >> p.first;
    cout << "second (double)? "; in >> p.second;
    return in;
}
fstream& operator<<(fstream& fout, const Pair& p) {
    fout << p.first << "\n" << p.second << "\n";
    return fout;
}
fstream& operator>>(fstream& fin, Pair& p) {
    fin >> p.first;
    fin >> p.second;
    return fin;
}