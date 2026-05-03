#include "Teacher.h"

Teacher::Teacher(void) : Person() {
    subject = "";
    hours = 0;
}

Teacher::~Teacher(void) {}

void Teacher::Show() {
    cout << "Name: " << name << ", Age: " << age
         << ", Subject: " << subject << ", Hours: " << hours << endl;
}

Teacher::Teacher(string n, int a, string s, int h) : Person(n, a) {
    subject = s;
    hours = h;
}

Teacher::Teacher(const Teacher& t) : Person(t) {
    subject = t.subject;
    hours = t.hours;
}

void Teacher::SetSubject(string s) {
    subject = s;
}

void Teacher::SetHours(int h) {
    hours = h;
}

void Teacher::IncreaseHours(int n) {
    hours += n;
}

void Teacher::DecreaseHours(int n) {
    if (hours >= n)
        hours -= n;
    else
        hours = 0;
}

Teacher& Teacher::operator=(const Teacher& t) {
    if (this == &t) return *this;
    Person::operator=(t);
    subject = t.subject;
    hours = t.hours;
    return *this;
}

istream& operator>>(istream& in, Teacher& t) {
    cout << "Enter name: ";
    in >> t.name;
    cout << "Enter age: ";
    in >> t.age;
    cout << "Enter subject: ";
    in >> t.subject;
    cout << "Enter hours: ";
    in >> t.hours;
    return in;
}

ostream& operator<<(ostream& out, const Teacher& t) {
    out << "Name: " << t.name << ", Age: " << t.age
        << ", Subject: " << t.subject << ", Hours: " << t.hours;
    return out;
}