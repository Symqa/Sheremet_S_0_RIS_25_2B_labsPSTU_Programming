#include "Pair.h"

Pair::Pair() : first(0), second(0.0) {}

Pair::Pair(int f, double s) : first(f), second(s) {}

Pair::Pair(int f) : first(f), second(static_cast<double>(f)) {}

Pair::Pair(const Pair& p) : first(p.first), second(p.second) {}

Pair::~Pair() {}

Pair& Pair::operator=(const Pair& p)
{
    if (this == &p) return *this;
    first = p.first;
    second = p.second;
    return *this;
}

Pair Pair::operator*(const Pair& p) const
{
    return Pair(first * p.first, second * p.second);
}

ostream& operator<<(ostream& out, const Pair& p)
{
    out << p.first << ":" << p.second;
    return out;
}

istream& operator>>(istream& in, Pair& p)
{
    int f;
    char colon;
    double s;
    in >> f >> colon >> s;
    if (colon == ':')
    {
        p.first = f;
        p.second = s;
    }
    else
    {
        in.setstate(ios::failbit);
    }
    return in;
}