#include "SavingsAccount.h"
#include <iostream>
#include <string>

using namespace std;

SavingsAccount::SavingsAccount(double balance, int accountNumber)
    : Account(balance, accountNumber) {}

SavingsAccount::SavingsAccount(const SavingsAccount &other) : Account(other), SavingsBalance(other.SavingsBalance) {}


SavingsAccount::~SavingsAccount() {
    cout << "Contul curent ( de economii ) cu numarul " << accountNumber << " a fost distrus.\n";
}

void SavingsAccount::applyInterest(double interestRate) {
    double interest = (balance * interestRate) / 100.0;  // Calculeaza dobanda pe baza soldului si a ratei dobanzii
    balance += interest;
    transactions.push_back("Dobanda aplicata: " + to_string(interestRate) + "%");
    cout << "Dobanda de " << interestRate << "% aplicata la Contul de Economii " << accountNumber << ".\n";
}

void SavingsAccount::deposit(double amount) {
    if (amount > 0) {
        balance += amount;
        SavingsBalance += amount;
        transactions.push_back("Depus la economii: $" + to_string(amount));
        cout << "Depus $" << amount << " in Contul de Economii " << accountNumber << ".\n";
    } else {
        cout << "Suma depusa trebuie sa fie pozitiva.\n";
    }
}

void SavingsAccount::displayAccountDetails() const {
    cout << "   -Numarul contului de economii: " << accountNumber << "\n"
         << "   -Balance: $" << balance << "\n"
         << "   -Tranzactii: \n";
    for (const string& transaction : transactions) {
        cout << "- " << transaction << "\n";
    }
}

double SavingsAccount::getBalance() const {
    return SavingsBalance;
}

SavingsAccount& SavingsAccount::operator=(const SavingsAccount &other) {
    if (this != &other) {
            Account::operator=(other);
            this->SavingsBalance = other.SavingsBalance;
    }
    return *this;
}

istream& operator>>(istream& in, SavingsAccount& other) {
    cout << "Introduceti numarul contului: ";
    in >> other.accountNumber;

    cout << "Introduceti balanta initiala: ";
    in >> other.balance;

    cout << "Introduceti balanta de economii: ";
    in >> other.SavingsBalance;

    return in;
}

ostream& operator<<(ostream &out, const SavingsAccount &other) {
    cout << "Numarul contului: ";
    out << other.accountNumber << "\n";

    cout << "Balanta: ";
    out << other.balance << "$\n";

    cout << "Balanta de Economii: ";
    out << other.SavingsBalance << "$\n";

    return out;
}

