#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <vector>
#include "Account.h"

class Loan;

class Customer {
private:
    string name; // Numele angajatului
    int customerID; //ID unic pt client
    vector<Account*> accounts; // Conturile clientului
    vector<Loan*> loans; // Imprumuturile clientului

public:
    // Constructor si Desctructor
    Customer() = default;
    Customer(string name, int id);
    Customer(const Customer &other);
    ~Customer();

    Customer& operator++();
    Customer operator++(int);
    bool operator==(const Customer& other) const;
    bool operator<(const Customer& other) const;
    Customer& operator=(const Customer& other);

    friend istream& operator>>(istream &in, Customer &customer);
    // Managmentul contului
    void addAccount(Account *account);
    void removeAccount(int accountNumber);
    void listAccounts() const;
    bool verifyAccount(int accountNumber);

    // Managmentul imprumuturilor
    void applyForLoan(Loan *loan);
    Account* getFirstAccount() const;

    //Afiseaza balanta
    void viewBalance(int accountNumber) const;

    // Getters
    string getName() const;
    int getID() const;
};

#endif // CUSTOMER_H
