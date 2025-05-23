#include "CheckingAccount.h"
#include <iostream>
#include <string>

using namespace std;

CheckingAccount::CheckingAccount(double balance, int accountNumber, double overdraftLimit)
    : Account(balance, accountNumber), overdraftLimit(overdraftLimit) {}

CheckingAccount::CheckingAccount(const CheckingAccount &other) : Account(other), overdraftLimit(other.overdraftLimit) {}

CheckingAccount::~CheckingAccount() {
    cout << "Contul curent ( de checking) cu numarul " << accountNumber << " a fost distrus.\n";
}

bool CheckingAccount::withdraw(double amount) {
    if (amount <= balance + overdraftLimit) {  // Permite retragerea chiar dacă soldul este negativ, atata timp cat se afla in limita de descoperit de cont
        balance -= amount;
        CheckingBalance -= amount;
        transactions.push_back("S-au retras: $" + to_string(amount));
        cout << "Retrage $" << amount << " din Contul de Checking " << accountNumber << ".\n";
        return true;
    } else {
        cout << "Fonduri insuficiente pentru retragere, inclusiv descoperit de cont.\n";
        return false;
    }
}

void CheckingAccount::deposit(double amount) {
    if (amount > 0) {
        balance += amount;
        CheckingBalance += amount;
        transactions.push_back("Depus: $" + to_string(amount));
        cout << "Depus $" << amount << " in contul de Checking " << accountNumber << ".\n";
    } else {
        cout << "Suma depusa trebuie sa fie pozitiva.\n";
    }
}

void CheckingAccount::displayAccountDetails() const {
    cout << "   -Numarul Contului de Checking: " << accountNumber << "\n"
         << "   -Balance: $" << CheckingBalance << "\n"
         << "   -Limita de descoperire de cont: $" << overdraftLimit << "\n"
         << "   -Tranzactii: \n";
    for (const string& transaction : transactions) {
        cout << "- " << transaction << "\n";
    }
}

double CheckingAccount::getBalance() const {
    return CheckingBalance;
}

istream& operator>>(istream& in, CheckingAccount &caccount) {
    cout << "Introduceti Numarul Contului: ";
    in >> caccount.accountNumber;
    cout << "Introduceti Balanta initiala: ";
    in >> caccount.CheckingBalance;
    cout << "Introduceti limita de descoperire de cont: ";
    in >> caccount.overdraftLimit;
}

ostream& operator<<(ostream& out, const CheckingAccount& caccount) {
    out << "Numarul Contului: " << caccount.accountNumber << "\n";
    out << "Balance: $" << caccount.CheckingBalance << "\n";
    out << "Limita de descoperire de cont: $" << caccount.overdraftLimit << "\n";
    out << "Tranzactii: \n";
    for (const string& transaction : caccount.transactions) {
        out << "- " << transaction << "\n";
    }
    return out;
}

CheckingAccount& CheckingAccount::operator++() {
    CheckingBalance++;
    return *this;
}

CheckingAccount CheckingAccount::operator++(int) {
    CheckingAccount current = *this;
    CheckingBalance++;
    return current;
}

CheckingAccount CheckingAccount::operator+(const CheckingAccount &object) {
    return CheckingAccount(CheckingBalance + object.CheckingBalance, accountNumber + object.accountNumber, overdraftLimit + object.overdraftLimit);
}

CheckingAccount& CheckingAccount::operator=(const CheckingAccount &object) {
    if(this != &object) {
        Account::operator=(object);
        this->overdraftLimit = object.overdraftLimit;
    }
    return *this;
}
