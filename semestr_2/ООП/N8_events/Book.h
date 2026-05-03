#pragma once
#include "Print.h"

class Book : public Print {
public:
    Book();
    ~Book();
    void Show();
    void Input();
    Book(string, string, int, string);
    Book(const Book&);
    int GetPages() { return pages; }
    string GetPublisher() { return publisher; }
    void SetPages(int);
    void SetPublisher(string);
    Book& operator=(const Book&);
protected:
    int pages;
    string publisher;
};