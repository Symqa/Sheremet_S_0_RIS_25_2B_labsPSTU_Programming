#ifndef PAIR_H
#define PAIR_H

#include <iostream>
using namespace std;

class Pair {
    int first;
    int second;
public:
    Pair() : first(0), second(0) {}
    Pair(int f, int s) : first(f), second(s) {}
    Pair(const Pair& p) : first(p.first), second(p.second) {}

    int get_first() const { return first; }
    int get_second() const { return second; }

    Pair& operator=(const Pair& p) {
        if (this != &p) {
            first = p.first;
            second = p.second;
        }
        return *this;
    }

    Pair operator+(const Pair& p) const {
        return Pair(first + p.first, second + p.second);
    }
    Pair operator-(const Pair& p) const {
        return Pair(first - p.first, second - p.second);
    }
    Pair operator*(const Pair& p) const {
        return Pair(first * p.first, second * p.second);
    }
    Pair operator/(const Pair& p) const {
        return Pair(first / p.first, second / p.second);
    }
    Pair operator/(int n) const {
        return Pair(first / n, second / n);
    }

    bool operator<(const Pair& p) const {
        if (first < p.first) return true;
        if (first > p.first) return false;
        return second < p.second;
    }
    bool operator>(const Pair& p) const {
        return p < *this;
    }
    bool operator<=(const Pair& p) const {
        return !(p < *this);
    }
    bool operator>=(const Pair& p) const {
        return !(*this < p);
    }
    bool operator==(const Pair& p) const {
        return first == p.first && second == p.second;
    }
    bool operator!=(const Pair& p) const {
        return !(*this == p);
    }

    friend ostream& operator<<(ostream& os, const Pair& p) {
        os << "(" << p.first << ", " << p.second << ")";
        return os;
    }
    friend istream& operator>>(istream& is, Pair& p) {
        is >> p.first >> p.second;
        return is;
    }
};

#endif