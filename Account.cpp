#include "Account.h"
#include <vector>

// Constructor pt initializarea balantei si a numarului unic de cont
Account::Account(double balance, int accountNumber) {
    this->balance = balance;
    this->accountNumber = accountNumber;
}

Account::Account(const Account &other) {
    this->balance = other.balance;
    this->accountNumber = other.accountNumber;
    this->transactions = other.transactions;
}

// Destructor virtual
Account::~Account() {
    cout << "Contul " << accountNumber << " inchis.\n";
}


// Operator ++ (prefix)
Account& Account::operator++() {
    ++accountNumber;
    return *this;
}

// Operator ++ (postfix)
Account Account::operator++(int) {
    Account current = *this;
    accountNumber++;
    return current;
}

// Operator +
Account Account::operator+(const Account& other) {
    transactions.insert(transactions.end(), other.transactions.begin(), other.transactions.end());
    return Account(balance + other.balance, accountNumber + other.accountNumber);
}

bool Account::operator==(const Account &other) const {
    return this->accountNumber == other.accountNumber;
}

bool Account::operator<(const Account& other) const {
    return this->accountNumber < other.accountNumber;
}

// Depoziteaza bani in cont
void Account::deposit(double amount) {
    if(amount > 0) {
        balance += amount;
        transactions.push_back("Depus $" + to_string(amount));
        cout << "Depus $" << amount << " in Contul " << accountNumber << ".\n";
    } else {
        cout << "Suma depozitului trebuie sa fie pozitiva.\n";
    }
}

// Retrage bani din cont
bool Account::withdraw(double amount) {
    if(amount > 0 && amount <= balance) {
        balance -= amount;
        transactions.push_back("S-a retras $" + to_string(amount));
        cout << "S-a retras $" << amount << " din Contul " << accountNumber << ".\n";
        return true;
    } else {
        cout << "Sold insuficient sau suma invalida.\n";
        return false;
    }
}

// Transfera banii intre conturi
void Account::transfer(double amount, Account *target) {
    if(withdraw(amount)) {
        target->deposit(amount);
        transactions.push_back("Transferat $" + to_string(amount) + "in Contul " + to_string(target->getAccountNumber()));
        cout << "Transferred $" << amount << " in Contul " << target->getAccountNumber() << ".\n";
    }
}

// Obtine balanta contului
double Account::getBalance() const {
    return balance;
}

// Obtine numarul contului
int Account::getAccountNumber() const {
    return accountNumber;
}

// Afiseaza istoricul tranzactilor
void Account::printTransactionHistory() const {
    cout << "Istoricul tranzactiilor din cont " << accountNumber << ":\n";
    for(const string &transaction : transactions) {
        cout << "- " << transaction << "\n";
    }
}

istream& operator>>(istream &in, Account &account) {
    cout << "Introduceti numarul contului: ";
    in >> account.accountNumber;
    cout << "Introduceti balanta initiala: ";
    in >> account.balance;
    return in;
}

Account& Account::operator=(const Account &other) {
    this->balance = other.balance;
    this->accountNumber = other.accountNumber;
    this->transactions = other.transactions;
}
