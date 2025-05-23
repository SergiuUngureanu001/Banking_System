#include "StockAccount.h"
#include <iostream>

StockAccount::StockAccount(double balance, int accountNumber, double investedAmount, double interestRate, double stockPrice)
    : InvestmentAccount(balance, accountNumber, investedAmount, interestRate), stockPrice(stockPrice), stockUnits(0) {}

StockAccount::StockAccount(const StockAccount &other)
    : InvestmentAccount(other), stockPrice(other.stockPrice), stockUnits(other.stockUnits) {}

StockAccount::~StockAccount() {}

bool StockAccount::buyAsset(double amount) {
    double totalCost = amount * stockPrice;
    if (totalCost <= getBalance()) {  // Verifica soldul contului
        balance -= totalCost;         // Scade costul actiunilor din sold
        investedAmount += totalCost;  // Adauga la soldul de investitii
        stockUnits += amount;
        transactions.push_back("S-au cumparat " + to_string(amount) + " actiuni la $" + to_string(stockPrice) + " fiecare.");
        cout << "S-au cumparat " << amount << " actiuni pentru $" << totalCost << endl;
        return true;
    } else {
        cout << "Sold insuficient pentru a cumpara actiuni.\n";
        return false;
    }
}

bool StockAccount::sellAsset(double amount) {
    if (amount <= stockUnits) {
        double totalRevenue = amount * stockPrice;
        balance += totalRevenue;      // Adauga la soldul contului
        investedAmount -= totalRevenue; // Extrage din fondul de investitii
        stockUnits -= amount;
        transactions.push_back("S-au vandut " + to_string(amount) + " actiuni la $" + to_string(stockPrice) + " fiecare.");
        cout << "S-au vandut " << amount << " actiuni pentru $" << totalRevenue << endl;
        return true;
    } else {
        cout << "Nu sunt suficiente stocuri pentru a vinde.\n";
        return false;
    }
}

void StockAccount::calculateReturn() {
    double returnAmount = stockUnits * stockPrice - investedAmount;
    cout << "Rentabilitatea totala a investitiei in stoc: $" << returnAmount << endl;
}

void StockAccount::displayInvestmentDetails() const {
    cout << "Detalii cont actiuni:\n"
              << "Numar cont: " << getAccountNumber() << "\n"
              << "Sold investit: " << investedAmount << " $.\n"
              << "Numar unitati de actiuni: " << stockUnits << "\n"
              << "Pret per unitate: " << stockPrice << " $.\n";
}

StockAccount& StockAccount::operator=(const StockAccount &other) {
    if (this != &other) {
        InvestmentAccount::operator=(other);
        stockPrice = other.stockPrice;
        stockUnits = other.stockUnits;
    }
    return *this;
}

ostream& operator<<(ostream& out, const StockAccount& account) {
    out << "Detalii cont de actiuni:\n";
    out << "Numarul Contului: " << account.getAccountNumber() << "\n";
    out << "Balance: $" << account.getBalance() << "\n";
    out << "Numarul actiunilor: " << account.stockUnits << "\n";
    out << "Pretul actiunii: $" << account.stockPrice << "\n";
    out << "Tranzactii:\n";
    for (const string& transaction : account.transactions) {
        out << "- " << transaction << "\n";
    }
    return out;
}

istream& operator>>(istream& in, StockAccount& account) {
    cout << "Enter Account Number: ";
    in >> account.accountNumber;
    cout << "Enter Balance: ";
    in >> account.balance;
    cout << "Enter Stock Price: ";
    in >> account.stockPrice;
    cout << "Enter Number of Stocks: ";
    in >> account.stockUnits;
    return in;
}
