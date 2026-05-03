#pragma once
#include <string>
#include <iostream>
using namespace std;

class Error {
public:
    virtual void what() const = 0;
    virtual ~Error() {}
};

class IndexError : public Error {
protected:
    string msg;
public:
    IndexError() : msg("Index Error\n") {}
    virtual void what() const { cout << msg; }
};

class SizeError : public Error {
protected:
    string msg;
public:
    SizeError() : msg("Size Error\n") {}
    virtual void what() const { cout << msg; }
};

class CursorError : public IndexError {
    string msg_;
public:
    CursorError() : IndexError(), msg_("Cursor out of bounds\n") {}
    void what() const { cout << msg << msg_; }
};

class EmptyListError : public SizeError {
    string msg_;
public:
    EmptyListError() : SizeError(), msg_("List is empty\n") {}
    void what() const { cout << msg << msg_; }
};