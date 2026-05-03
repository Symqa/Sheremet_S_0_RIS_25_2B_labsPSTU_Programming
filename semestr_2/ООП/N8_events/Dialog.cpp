#include "Dialog.h"
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

Dialog::Dialog() : Tree(), EndState(0) {}
Dialog::~Dialog() {}

void Dialog::GetEvent(TEvent& event) {
    string OpInt = "+-szqm";
    string s;
    cout << "> ";
    cin >> s;
    if (s.empty()) {
        event.what = evNothing;
        return;
    }
    char code = s[0];
    if (OpInt.find(code) != string::npos) {
        event.what = evMessage;
        switch (code) {
            case 'm': event.command = cmMake; break;
            case '+': event.command = cmAdd; break;
            case '-': event.command = cmDel; break;
            case 's': event.command = cmShow; break;
            case 'z': event.command = cmGet; break;
            case 'q': event.command = cmQuit; break;
        }
        if (code == 'm' || code == 'z') {
            if (s.length() > 1) {
                string param = s.substr(1, s.length() - 1);
                int A = atoi(param.c_str());
                event.a = A;
            } else {
                event.what = evNothing;
            }
        }
    } else {
        event.what = evNothing;
    }
}

int Dialog::Execute() {
    TEvent event;
    do {
        EndState = 0;
        GetEvent(event);
        HandleEvent(event);
    } while (!Valid());
    return EndState;
}

int Dialog::Valid() {
    return EndState != 0;
}

void Dialog::ClearEvent(TEvent& event) {
    event.what = evNothing;
}

void Dialog::EndExec() {
    EndState = 1;
}

void Dialog::HandleEvent(TEvent& event) {
    if (event.what == evMessage) {
        switch (event.command) {
            case cmMake:
                if (event.a > 0) {
                    if (beg != 0) {
                        for (int i = 0; i < cur; ++i)
                            delete beg[i];
                        delete[] beg;
                    }
                    size = event.a;
                    beg = new Object*[size];
                    cur = 0;
                }
                ClearEvent(event);
                break;
            case cmAdd:
                Add();
                ClearEvent(event);
                break;
            case cmDel:
                Del();
                ClearEvent(event);
                break;
            case cmShow:
                Show();
                ClearEvent(event);
                break;
            case cmQuit:
                EndExec();
                ClearEvent(event);
                break;
            default:
                Tree::HandleEvent(event);
                break;
        }
    }
}