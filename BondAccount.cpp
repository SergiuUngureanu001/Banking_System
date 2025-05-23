#include "BondAccount.h"
#include <iostream>

BondAccount::BondAccount(double balance, int accountNumber, double investedAmount, double interestRate, double bondYield, double bondTerm)
    : InvestmentAccount(balance, accountNumber, investedAmount, interestRate), bondYield(bondYield), bondTerm(bondTerm) {}

BondAccount::BondAccount(const BondAccount& other)
    : InvestmentAccount(other), bondYield(other.bondYield), bondTerm(other.bondTerm), bondsOwned(other.bondsOwned) {}

BondAccount::~BondAccount() {}

bool BondAccount::buyAsset(double amount) {
    double totalCost = amount * bondYield;
    if (totalCost <= getBalance()) {  // Verifica soldul contului
        balance -= totalCost;         // Extrage din soldul contului costul obligatiuniilpr
        investedAmount += totalCost;  // adauga la fondul de investitie
        bondsOwned += amount;
        transactions.push_back("S-au cumparat " + to_string(amount) + " Obligatiuni la $" + to_string(bondYield) + " fiecare.");
        cout << "S-au cumparat " << amount << " obligatiuni pentru $" << totalCost << endl;
        return true;
    } else {
        cout << "Sold insuficient pentru a cumpara obligatiuni.\n";
        return false;
    }
}

bool BondAccount::sellAsset(double amount) {
    if (amount <= bondsOwned) {
        double totalRevenue = amount * bondYield;
        balance += totalRevenue;      // Adauga la soldul contului
        investedAmount -= totalRevenue; // Scade din fondul de investitii
        bondsOwned -= amount;
        transactions.push_back("S-au vandut " + to_string(amount) + " obligatiuni la $" + to_string(bondYield) + " fiecare.");
        cout << "S-au vandut " << amount << " obligatiuni pentru $" << totalRevenue << endl;
        return true;
    } else {
        cout << "Nu sunt suficiente obligatiuni pentru a vinde.\n";
        return false;
    }
}

void BondAccount::calculateReturn() {
    double returnAmount = investedAmount * bondYield - investedAmount;
    cout << "Rentabilitatea totala a investitiei in obligatiuni: $" << returnAmount << endl;
}

void BondAccount::displayInvestmentDetails() const {
    cout << "Detalii cont obligatiuni:\n"
              << "Numar cont: " << getAccountNumber() << "\n"
              << "Sold investit: " << investedAmount << " $.\n"
              << "Randament obligatiuni: " << bondYield << "%.\n"
              << "Termen obligatiuni: " << bondTerm << " ani.\n";
}

BondAccount& BondAccount::operator=(const BondAccount& other) {
    if (this != &other) {
        InvestmentAccount::operator=(other);  // Copiez membrii clasei de baza
        bondYield = other.bondYield;
        bondTerm = other.bondTerm;
        bondsOwned = other.bondsOwned;
    }
    return *this;
}

ostream& operator<<(ostream& out, const BondAccount& account) {
    out << "Cont Obligatiuni Detalii:\n";
    out << "Numar Cont: " << account.getAccountNumber() << "\n";
    out << "Balanta: $" << account.getBalance() << "\n";
    out << "Randament Obligatiuni: " << account.bondYield << "%\n";
    out << "Durata Obligatiuni: " << account.bondTerm << " ani\n";
    out << "Numar Obligatiuni: " << account.bondsOwned << "\n";
    out << "Tranzactii:\n";
    for (const string& transaction : account.transactions) {
        out << "- " << transaction << "\n";
    }
    return out;
}

istream& operator>>(istream& in, BondAccount& account) {
    cout << "Introduceti numarul contului: ";
    in >> account.accountNumber;
    cout << "Introduceti balanta initiala: ";
    in >> account.balance;
    cout << "Introduceti randamentul obligatiunii: ";
    in >> account.bondYield;
    cout << "Introduceti durata obligatiunii (in ani): ";
    in >> account.bondTerm;
    return in;
}


