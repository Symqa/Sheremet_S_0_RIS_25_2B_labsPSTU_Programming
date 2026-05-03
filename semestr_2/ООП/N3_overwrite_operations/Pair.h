#ifndef PAIR_H
#define PAIR_H
#include <iostream>

class Pair {
    private:
        int first;
        double second;
    public:
        Pair();
        Pair(int f, double s);
        Pair(const Pair &obj);

        void setFirst(int f);
        void setSecond(double s);
        int getFirst() const;
        double getSecond() const;

        Pair& operator=(const Pair &other);
        bool operator==(const Pair &other) const;
        bool operator!=(const Pair &other) const;
        void operator-(const double num);
        
        friend std::istream&operator>>(std::istream &in, Pair &pair);
        friend std::ostream&operator<<(std::ostream &out, const Pair &pair);
        
        ~Pair();
};


#endif 
