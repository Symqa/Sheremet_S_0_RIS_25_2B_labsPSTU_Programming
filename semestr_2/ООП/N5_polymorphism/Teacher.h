#pragma once
#include "Person.h"
#include <string>
#include <iostream>
using namespace std;

class Teacher : public Person {
public:
    Teacher(void);
    ~Teacher(void);
    void Show(); // переопределённый вывод
    Teacher(string, int, string, int);
    Teacher(const Teacher&);
    string GetSubject() { return subject; }
    int GetHours() { return hours; }
    void SetSubject(string);
    void SetHours(int);
    void IncreaseHours(int); // увеличить часы
    void DecreaseHours(int); // уменьшить часы
    Teacher& operator=(const Teacher&);
    friend istream& operator>>(istream& in, Teacher& t);
    friend ostream& operator<<(ostream& out, const Teacher& t);
protected:
    string subject;
    int hours;
};