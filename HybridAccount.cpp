#include "HybridAccount.h"
#include <iostream>
#include <string>

using namespace std;

HybridAccount::HybridAccount(double balance, int accountNumber, double overdraftLimit)
    :   Account(balance, accountNumber), CheckingAccount(balance, accountNumber, overdraftLimit), SavingsAccount(balance, accountNumber) {}

HybridAccount::HybridAccount(const HybridAccount &other) : Account(other), CheckingAccount(other), SavingsAccount(other) {}

HybridAccount::~HybridAccount() {
    cout << "Contul Hibrid cu numarul " << accountNumber << " a fost distrus.\n";
}

void HybridAccount::deposit(double amount) {
    if (amount > 0) {
        double procent;
        cout << "Cat la suta din suma doresti sa fie depusa in contul de Economii?\n";
        cin >> procent;
        double can = amount / 100 * procent;
        CheckingAccount::deposit(amount - can);
        SavingsAccount::deposit(can);
    } else {
        cout << "Suma depusa trebuie sa fie pozitiva.\n";
    }
}

bool HybridAccount::withdraw(double amount) {
    if (CheckingAccount::withdraw(amount)) {
        return true;
    } else if (SavingsAccount::withdraw(amount)) {
        return true;
    } else {
        cout << "Retragere esuata: sold insuficient atat in ​​conturile curente, cat si in conturile de economii.\n";
        return false;
    }
}

double HybridAccount::getBalance() const {
    return Account::getBalance();
}

// Se aplica doband la soldul din contul de economii (mostenit din SavingsAccount)
void HybridAccount::applyInterest(double interestRate) {
    SavingsAccount::applyInterest(interestRate);  // Aplica dobanda la contul de Economii
}

void HybridAccount::displayAccountDetails() const {
    cout << "- Numarul Contului Hibrid: " << getAccountNumber() << " - Balance: $" << getBalance() << "\n"
         << "   - Balance (Checking): $" << CheckingAccount::getBalance() << "\n"
         << "   - Balance (Economii): $" << SavingsAccount::getBalance() << "\n";
}

HybridAccount& HybridAccount::operator=(const HybridAccount &other) {
    if (this != &other) {
        Account::operator=(other);
        CheckingAccount::operator=(other);
        SavingsAccount::operator=(other);
    }
    return *this;
}

istream& operator>>(istream &in, HybridAccount &haccount) {
    cout << "Introduceti numarul contului: ";
    in >> haccount.accountNumber;
    cout << "Introduceti balanta initiala: ";
    in >> haccount.balance;

    // initial balanta contului hibrid se imparte in mod egal
    haccount.CheckingBalance = haccount.balance / 2;
    haccount.SavingsBalance = haccount.balance / 2;

    cout << "Introduceti limita de descoperire pentru contul curent: ";
    in >> haccount.overdraftLimit;

    return in;
}

ostream& operator<<(ostream& out, const HybridAccount& haccount) {
    out << "Detaliile contului hibrid:\n";
    out << "Numarul Contului: " << haccount.getAccountNumber() << "\n";
    out << "Total Balance (Checking + Savings): $" << haccount.getBalance() << "\n";
    out << "Checking Account Balance: $" << haccount.CheckingAccount::getBalance() << "\n";
    out << "Savings Account Balance: $" << haccount.SavingsAccount::getBalance() << "\n";
    out << "Checking Account Overdraft Limit: $" << haccount.overdraftLimit << "\n";
    out << "Tranzactii:\n";

    // Afiseaza toate tranzactiile Contului de Checking
    for (const string& transaction : haccount.transactions) {
        out << "   - " << transaction << "\n";
    }

    return out;
}


