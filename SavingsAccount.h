#ifndef SAVINGSACCOUNT_H
#define SAVINGSACCOUNT_H

#include "Account.h"

class SavingsAccount : virtual public Account {
protected:
    double SavingsBalance;
public:
    SavingsAccount(double balance, int accountNumber);
    SavingsAccount(const SavingsAccount &other);

    ~SavingsAccount();

    void applyInterest(double interestRate);

    void deposit(double amount) override;

    void displayAccountDetails() const;

    double getBalance() const;

    SavingsAccount& operator=(const SavingsAccount &other);

    friend istream& operator>>(istream &in, SavingsAccount &other);
    friend ostream& operator<<(ostream &out, const SavingsAccount &other);
};

#endif // SAVINGSACCOUNT_H

