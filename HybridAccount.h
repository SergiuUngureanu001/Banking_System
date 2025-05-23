#ifndef HYBRIDACCOUNT_H
#define HYBRIDACCOUNT_H

#include "CheckingAccount.h"
#include "SavingsAccount.h"

class HybridAccount : public CheckingAccount, public SavingsAccount {
public:
    HybridAccount(double balance, int accountNumber, double overdraftLimit = 500.0);
    HybridAccount(const HybridAccount &other);

    ~HybridAccount();

    void deposit(double amount) override;

    bool withdraw(double amount) override;

    void applyInterest(double interestRate);

    void displayAccountDetails() const;

    double getBalance() const;

    HybridAccount& operator=(const HybridAccount &other);
    friend istream& operator>>(istream &in, HybridAccount &other);
    friend ostream& operator<<(ostream &out, const HybridAccount &other);
};

#endif // HYBRIDACCOUNT_H

