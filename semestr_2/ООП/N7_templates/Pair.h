#ifndef PAIR_H
#define PAIR_H

#include <iostream>
using namespace std;

class Pair
{
public:
    Pair();
    Pair(int f, double s);
    Pair(int f);                      // преобразование из int
    Pair(const Pair& p);
    ~Pair();

    Pair& operator=(const Pair& p);

    // умножение пар поэлементное
    Pair operator*(const Pair& p) const;

    friend ostream& operator<<(ostream& out, const Pair& p);
    friend istream& operator>>(istream& in, Pair& p);

private:
    int first;
    double second;
};

#endif // PAIR_H