#include "Book.h"
#include <iostream>
using namespace std;

Book::Book() : Print(), pages(0), publisher("") {}
Book::~Book() {}
Book::Book(string n, string a, int p, string pub) : Print(n, a), pages(p), publisher(pub) {}
Book::Book(const Book& b) : Print(b), pages(b.pages), publisher(b.publisher) {}

void Book::SetPages(int p) { pages = p; }
void Book::SetPublisher(string p) { publisher = p; }

Book& Book::operator=(const Book& b) {
    if (&b == this) return *this;
    Print::operator=(b);
    pages = b.pages;
    publisher = b.publisher;
    return *this;
}

void Book::Show() {
    Print::Show();
    cout << "\nPages: " << pages;
    cout << "\nPublisher: " << publisher;
    cout << "\n";
}

void Book::Input() {
    Print::Input();
    cout << "Pages: "; cin >> pages;
    cout << "Publisher: "; cin >> publisher;
}