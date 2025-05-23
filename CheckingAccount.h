#ifndef CHECKINGACCOUNT_H
#define CHECKINGACCOUNT_H

#include "Account.h"

class CheckingAccount : virtual public Account {
protected:
    double overdraftLimit; // limita de bani pe care o mai poti folosi cand ai ramas pe 0 numita si "descoperit de cont"
    double CheckingBalance; // balanta contului hibrid (cel mare) se imparte in 2, cel de chechink, respectiv de economii

public:
    CheckingAccount(double balance, int accountNumber, double overdraftLimit = 500.0);
    CheckingAccount(const CheckingAccount &other);

    ~CheckingAccount();

    double getBalance() const;

    bool withdraw(double amount) override; // mai intai se incearca extragerea din contul de acesta

    void deposit(double amount) override;

    void displayAccountDetails() const;

    CheckingAccount& operator++();
    CheckingAccount operator++(int);
    CheckingAccount operator+(const CheckingAccount &object);
    CheckingAccount& operator=(const CheckingAccount &object);

    friend istream& operator>>(istream& in, CheckingAccount &caccount);

    friend ostream& operator<<(ostream& out, const CheckingAccount& caccount);
};

#endif // CHECKINGACCOUNT_H

