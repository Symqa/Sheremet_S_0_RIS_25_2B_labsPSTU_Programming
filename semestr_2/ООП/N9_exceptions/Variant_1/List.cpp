#include "List.h"
using namespace std;

List::List() : head(nullptr), sz(0), current(-1) {}

List::List(int n, int* arr) : head(nullptr), sz(0), current(-1) {
    if (n > MAX_SIZE) throw 1;
    if (n < 0) throw 1;
    for (int i = n - 1; i >= 0; --i) {
        head = new Node(arr ? arr[i] : 0, head);
        ++sz;
    }
    if (sz > 0) current = 0;
}

List::List(const List& l) : head(nullptr), sz(0), current(l.current) {
    Node** p = &head;
    for (Node* cur = l.head; cur; cur = cur->next) {
        *p = new Node(cur->data);
        p = &((*p)->next);
        ++sz;
    }
}

List::~List() {
    while (head) {
        Node* t = head;
        head = head->next;
        delete t;
    }
}

List& List::operator=(const List& l) {
    if (this == &l) return *this;
    while (head) {
        Node* t = head;
        head = head->next;
        delete t;
    }
    head = nullptr;
    sz = 0;
    Node** p = &head;
    for (Node* cur = l.head; cur; cur = cur->next) {
        *p = new Node(cur->data);
        p = &((*p)->next);
        ++sz;
    }
    current = l.current;
    return *this;
}

List::Node* List::getNode(int i) const {
    if (i < 0 || i >= sz) return nullptr;
    Node* cur = head;
    for (int k = 0; k < i; ++k)
        cur = cur->next;
    return cur;
}

int& List::operator[](int i) {
    if (i < 0) throw 2;
    if (i >= sz) throw 3;
    return getNode(i)->data;
}

int List::operator()() const {
    return sz;
}

List List::operator*(int factor) const {
    List res(*this);
    for (Node* cur = res.head; cur; cur = cur->next)
        cur->data *= factor;
    return res;
}

int& List::operator-(int n) {
    if (sz == 0) throw 4;
    int newCur = current - n;
    if (newCur < 0 || newCur >= sz) throw 5;
    current = newCur;
    return getNode(current)->data;
}

ostream& operator<<(ostream& out, const List& l) {
    if (l.sz == 0)
        out << "Empty";
    else
        for (List::Node* cur = l.head; cur; cur = cur->next)
            out << cur->data << " ";
    out << endl;
    return out;
}

istream& operator>>(istream& in, List& l) {
    while (l.head) {
        List::Node* t = l.head;
        l.head = l.head->next;
        delete t;
    }
    l.sz = 0;
    l.current = -1;

    cout << "Enter number of elements: ";
    int n;
    in >> n;
    if (n > MAX_SIZE) throw 1;
    cout << "Enter " << n << " elements:\n";
    List::Node** p = &l.head;
    for (int i = 0; i < n; ++i) {
        int val;
        cout << ">";
        in >> val;
        *p = new List::Node(val);
        p = &((*p)->next);
        ++l.sz;
    }
    if (l.sz > 0) l.current = 0;
    return in;
}