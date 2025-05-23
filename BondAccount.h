#ifndef BONDACCOUNT_H
#define BONDACCOUNT_H

#include "InvestmentAccount.h"

class BondAccount : public InvestmentAccount {
private:
    double bondYield;
    double bondTerm;
    double bondsOwned; // Contorizeaza numarul de obligatiuni detinute

public:
    BondAccount(double balance, int accountNumber, double investedAmount, double interestRate, double bondYield, double bondTerm);
    BondAccount(const BondAccount& other);

    ~BondAccount();

    bool buyAsset(double amount) override;   // Cumpararea de obligatiuni
    bool sellAsset(double amount) override;  // Vânzarea de obligatiuni
    void calculateReturn() override;         // Calcularea randamentului obligatiunii
    void displayInvestmentDetails() const override; // Afisarea detaliilor contului de obligatiuni

    BondAccount& operator=(const BondAccount& other);
    friend istream& operator>>(istream& in, BondAccount& account);
    friend ostream& operator<<(ostream& out, const BondAccount& account);

};

#endif // BONDACCOUNT_H

