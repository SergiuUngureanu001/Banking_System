/// CLASA ABSTRACTA
#ifndef INVESTMENTACCOUNT_H
#define INVESTMENTACCOUNT_H

#include "Account.h"

class InvestmentAccount : public Account {
protected:
    double investedAmount; // Suma investita
    double interestRate;   // Rata dobanzii pentru investitii
public:
    InvestmentAccount(double balance, int accountNumber, double investedAmount, double interestRate);
    InvestmentAccount(const InvestmentAccount &other);
    virtual ~InvestmentAccount();

    // Functii virtuale pure care vor fi implementate in clasele derivate
    virtual bool buyAsset(double amount) = 0;
    virtual bool sellAsset(double amount) = 0;
    virtual void calculateReturn() = 0;

    virtual void displayInvestmentDetails() const = 0;

    InvestmentAccount& operator=(const InvestmentAccount &other);
    friend ostream& operator<<(ostream& out, const InvestmentAccount& account);
    friend istream& operator>>(istream& in, InvestmentAccount& account);
};

#endif // INVESTMENTACCOUNT_H

