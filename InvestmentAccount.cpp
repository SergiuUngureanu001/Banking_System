#include "InvestmentAccount.h"

InvestmentAccount::InvestmentAccount(double balance, int accountNumber, double investedAmount, double interestRate)
    : Account(balance, accountNumber), investedAmount(investedAmount), interestRate(interestRate) {}

InvestmentAccount::InvestmentAccount(const InvestmentAccount &other)
        : Account(other), investedAmount(other.investedAmount), interestRate(other.interestRate) {}

InvestmentAccount::~InvestmentAccount() {}

InvestmentAccount& InvestmentAccount::operator=(const InvestmentAccount &other) {
        if (this != &other) {
            Account::operator=(other);
            investedAmount = other.investedAmount;
            interestRate = other.interestRate;
        }
        return *this;
}

ostream& operator<<(ostream& out, const InvestmentAccount& account) {
        out << "Cont de Investitii - Numarul Contului: " << account.getAccountNumber() << "\n";
        out << "Balanta: $" << account.getBalance() << "\n";
        out << "Suma Investita: $" << account.investedAmount << "\n";
        out << "Rata Dobanzii: " << account.interestRate << "%\n";
        return out;

}

istream& operator>>(istream& in, InvestmentAccount& account) {
        cout << "Introduceti numarul contului: ";
        in >> account.accountNumber;
        cout << "Introduceti balanta initiala: ";
        in >> account.balance;
        cout << "Introduceti suma investita: ";
        in >> account.investedAmount;
        cout << "Introduceti rata dobanzii: ";
        in >> account.interestRate;
        return in;
}
