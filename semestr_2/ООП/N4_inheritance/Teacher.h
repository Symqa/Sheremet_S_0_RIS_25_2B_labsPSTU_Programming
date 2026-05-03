#pragma once
#include "person.h"

class Teacher : public Person {
protected:
    string subject;
    int hours;
public:
    Teacher();
    ~Teacher();
    Teacher(string, int, string, int);
    Teacher(const Teacher&);
    string GetSubject() const { return subject; }
    int GetHours() const { return hours; }
    void SetSubject(string);
    void SetHours(int);
    void IncreaseHours(int delta);
    void DecreaseHours(int delta);
    Teacher& operator=(const Teacher&);
    friend istream& operator>>(istream& in, Teacher& t);
    friend ostream& operator<<(ostream& out, const Teacher& t);
};