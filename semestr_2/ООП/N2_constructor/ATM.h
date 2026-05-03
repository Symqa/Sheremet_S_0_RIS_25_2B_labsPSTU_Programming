#ifndef ATM_H
#define ATM_H

class ATM {
    private:
        int identificator;
        double balance;
        double max_withdrawal_amount;
    public:
        ATM();
        ATM(int id, double b, double max_amount);
        ATM(ATM &obj);

        ~ATM();

        void setId(int id);
        void setBalance(int b);
        void setMaxWithdraw(int max_amount);
        int getId() const;
        double getBalance() const;
        double getMaxAmount() const;
        void withdraw(double amount);
        void deposit(double amount);
        void show() const;

};

ATM make_atm();
void print_atm(ATM a);

#endif
