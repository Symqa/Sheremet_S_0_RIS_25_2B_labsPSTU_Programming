#include "ATM.h"
#include <iostream>
#include <cstdlib>
using namespace std;


ATM::ATM() {
    setId(rand()%100+1);
    setBalance(rand()%100);
    setMaxWithdraw(rand()%100+1);
}

ATM::ATM(int id, double b, double max_amount) {
    setId(id);
    setBalance(b);
    setMaxWithdraw(max_amount);
}

ATM::ATM(ATM &obj) {
    setId(obj.getId());
    setBalance(obj.getBalance());
    setMaxWithdraw(obj.getMaxAmount());
}

ATM::~ATM() {
    cout << endl << "Объект с идентификатором " << this->getId() << " удалён" << endl;
}

void ATM::setId(int id) {
    if (id > 0) {
        this->identificator = id;
    } else {
        cout << "Ошибка: идентификатор должен быть > 0" << endl;
    }
    
}

void ATM::setBalance(int b) {
    if (b >= 0) {
        this->balance = b;
    } else {
        cout << "Ошибка: баланс должен быть >= 0" << endl;
    }
}

void ATM::setMaxWithdraw(int max_amount) {
    if (max_amount > 0) {
        this->max_withdrawal_amount = max_amount;
    } else {
        cout << "Ошибка: максимальная сумма снятия должна быть > 0" << endl;
    }
}

int ATM::getId() const {
    return this->identificator;
}

double ATM::getBalance() const {
    return this->balance;
}

double ATM::getMaxAmount() const {
    return this->max_withdrawal_amount;
}

void ATM::withdraw(double amount) {
    int balance = this->getBalance();
    if (amount > 0 && balance - amount >= 0 && amount <= this->getMaxAmount()) {
        setBalance(balance-amount);
        cout << "Списание: -" << amount << " | Остаток на счёте: " << this->getBalance();
    } else {
        cout << "Ошибка: невозможно выполнить операцию списания." << endl;
    }
}

void ATM::deposit(double amount) {
    int balance = this->getBalance();
    if (amount > 0) {
        setBalance(balance + amount);
        cout << "Пополнение: +" << amount << " | Остаток на счёте: " << this->getBalance();
    } else {
        cout << "Ошибка: невозможно выполнить операцию пополнения, сумма пополнения должна быть больше 0" << endl;
    }
}

void ATM::show() const {
    cout << "==========Банкомат============" << endl;
    cout << "Идентификатор: " << this->getId() << endl;
    cout << "Баланс: " << this->getBalance() << endl;
    cout << "Максимальная сумма списания: " << this->getMaxAmount() << endl;
}

ATM make_atm() {
    int id;
    double balance;
    double max_withdraw;
    cout << "Введите идентификатор банкомата: ";
    do {
        cin >> id;
    } while (id <= 0);
    cout << "Введите остаток денег в банкомате: ";
    do {
        cin >> balance;
    } while (balance < 0);
    cout << "Введите максимальную сумму снятия: ";
    do {
        cin >> max_withdraw;
    } while (max_withdraw <= 0);
    ATM atm(id, balance, max_withdraw);
    return atm;
}

void print_atm(ATM a) {
    a.show();
}