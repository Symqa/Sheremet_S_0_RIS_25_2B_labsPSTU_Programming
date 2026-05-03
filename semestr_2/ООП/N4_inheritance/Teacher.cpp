#include "Teacher.h"

Teacher::Teacher() : Person() {
    subject = "";
    hours = 0;
}

Teacher::~Teacher() {}

Teacher::Teacher(string N, int A, string S, int H) : Person(N, A) {
    subject = S;
    hours = H;
}

Teacher::Teacher(const Teacher& t) : Person(t) {
    subject = t.subject;
    hours = t.hours;
}

void Teacher::SetSubject(string S) { subject = S; }
void Teacher::SetHours(int H) { hours = H; }
void Teacher::IncreaseHours(int delta) { hours += delta; }
void Teacher::DecreaseHours(int delta) { hours -= delta; }

Teacher& Teacher::operator=(const Teacher& t) {
    if (&t == this) return *this;
    Person::operator=(t);
    subject = t.subject;
    hours = t.hours;
    return *this;
}

istream& operator>>(istream& in, Teacher& t) {
    cout << "\nName: "; in >> t.name;
    cout << "Age: "; in >> t.age;
    cout << "Subject: "; in >> t.subject;
    cout << "Hours: "; in >> t.hours;
    return in;
}

ostream& operator<<(ostream& out, const Teacher& t) {
    out << "\nNAME: " << t.name;
    out << "\nAGE: " << t.age;
    out << "\nSUBJECT: " << t.subject;
    out << "\nHOURS: " << t.hours;
    out << "\n";
    return out;
}