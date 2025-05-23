// StockAccount.h
#ifndef STOCKACCOUNT_H
#define STOCKACCOUNT_H

#include "InvestmentAccount.h"

class StockAccount : public InvestmentAccount {
private:
    double stockUnits; // Numarul de unitați de actiuni
    double stockPrice; // Pretul per actiune

public:
    StockAccount(double balance, int accountNumber, double investedAmount, double interestRate, double stockPrice);
    StockAccount(const StockAccount &other);
    ~StockAccount();

    bool buyAsset(double amount) override;    // Cumpararea de actiuni
    bool sellAsset(double amount) override;   // Vânzarea de actiuni
    void calculateReturn() override;          // Calcularea randamentului actiunilor
    void displayInvestmentDetails() const override; // Afisarea detaliilor contului de actiuni

    StockAccount& operator=(const StockAccount &other);
    friend ostream& operator<<(ostream& out, const StockAccount& account);
    friend istream& operator>>(istream& in, StockAccount& account);
};

#endif // STOCKACCOUNT_H

