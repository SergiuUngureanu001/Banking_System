#include "Customer.h"
#include "Loan.h"
#include <iostream>

using namespace std;

// Constructor
Customer::Customer(string name, int customerID) {
    this->name = name;
    this->customerID = customerID;
}

Customer::Customer(const Customer &other) {
    this->name = other.name;
    this->customerID = other.customerID;
    for (Account* acc : other.accounts) {
        this->accounts.push_back(new Account(*acc));
    }
    for (Loan* loan : other.loans) {
        this->loans.push_back(new Loan(*loan));
    }
}

istream& operator>>(istream& in, Customer& customer) {
    cout << "Introduceti numele clientului: ";
    in >> ws;
    getline(in, customer.name);

    cout << "Introduceti ID client: ";
    in >> customer.customerID;

    return in;
}
// Destructor(curata tot heap-ul)
Customer::~Customer() {
    for(Account *account : accounts) {
        delete account;
    }
    accounts.clear();

    for(Loan *loan : loans) {
        delete loan;
    }
    loans.clear();

    cout << "Clientul " << name << " (ID: " << customerID << ") sters.\n";
}

// Operator ++ (prefix)
Customer& Customer::operator++() {
    ++customerID;
    return *this;
}

// Operator ++ (postfix)
Customer Customer::operator++(int) {
    Customer current = *this;
    customerID++;
    return current;
}

// Operator ==
bool Customer::operator==(const Customer& other) const {
    return this->customerID == other.customerID;
}

// Operator <
bool Customer::operator<(const Customer& other) const {
    return this->customerID < other.customerID;
}

Account* Customer::getFirstAccount() const {
    if (!accounts.empty()) {
        return accounts[0];
    }
    return nullptr;
}

bool Customer::verifyAccount(int accountNumber) {
    for(const Account *account : accounts) {
        if(account->getAccountNumber() == accountNumber) {
            return true;
        }
    }
    return false;
}


// Adaug un cont unui client
void Customer::addAccount(Account *account) {
    accounts.push_back(account);
}

// Sterge un cont dupa numarul contului
void Customer::removeAccount(int accountNumber) {
    for(auto start = accounts.begin(); start != accounts.end(); start++) {
        if((*start)->getAccountNumber() == accountNumber) {
            delete *start; //
            accounts.erase(start);
            cout << "Contul " << accountNumber << " sters.\n";
            return;
        }
    }
    cout << "Contul " << accountNumber << " nu a fost gasit.\n";
}

// Debug
void Customer::listAccounts() const {
    cout << "Conturile pentru " << name << "(ID: " << customerID << "):\n";
    for(const Account *account : accounts) {
        cout << "- Numar Cont: " << account->getAccountNumber()
             << ", Balance: $" << account-> getBalance() << "\n";
    }
}

// Afiseaza balanta unui cont specific
void Customer::viewBalance(int accountNumber) const {
    for(const Account *account : accounts) {
        if(account->getAccountNumber() == accountNumber) {
            cout << "Cont " << accountNumber << "Balance: $" << account->getBalance() << "\n";
        }
    }
    cout << "Contul " << accountNumber << " nu a putut fi gasit.\n";
}

// Returneaza numele clientului
string Customer:: getName() const {
    return name;
}

int Customer::getID() const {
    return customerID;
}

Customer& Customer::operator=(const Customer &other) {
    if (this != &other) {
        this->customerID = other.customerID;
        this->name = other.name;
        this->accounts = other.accounts;
        this->loans = other.loans;
    }
    return *this;
}
