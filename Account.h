#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <vector>

using namespace std;

class Account {
// Am facut protected pentru urmatoarele clase pe care le voi implementa in proiect care vor mosteni
// clasa Account -> SavingsAccount & CheckingAccount
protected:
    double balance; // Balansul contului
    int accountNumber; // Numarul unic al contului
    vector<string> transactions; // Istoricul tranzactilor

public:
    // Constructor si destructor
    Account(double balance, int accountNumber);
    Account(const Account &other);
    virtual ~Account(); // Trebuie implementat destrctorul in clasa copil pt polimorfism

    Account& operator++();
    Account operator++(int);
    Account operator+(const Account &other);
    bool operator==(const Account &other) const;
    bool operator<(const Account &other) const;
    Account& operator=(const Account &other);

    // Tranzactiile de baza
    virtual void deposit(double amount);
    virtual bool withdraw(double amount); // trebuie facut virtual pe viito in clasele care ii vor mosteni
    void transfer(double amount, Account *target);

    // Getters
    virtual double getBalance() const;
    int getAccountNumber() const;

    // Afiseaza Tranzactiile
    void printTransactionHistory() const;
    friend istream& operator>>(istream& in, Account &account);
};
#endif // ACCOUNT_H
