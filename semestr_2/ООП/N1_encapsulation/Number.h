#ifndef NUMBER_H
#define NUMBER_H

#include <iostream>
using namespace std;


class Number {
    public:

        unsigned int first;
        double second;

        Number();
        void Init(int first, double second);
        void Read();
        void Show() const;
        double multiply(double k);
        double getValue() const;
};

Number make_Number(int f, double s);

#endif