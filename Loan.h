#ifndef LOAN_H
#define LOAN_H

#include <iostream>

class Customer;

class Loan {
private:
    int loanID; // ID unic pt imprumut
    double amount; // Valoarea principala a imprumutului
    double interestRate; // Rata Dobanzii (%)
    int termMonths; // Termenul imprumutului (in luni)
    double remainingBalance; // Suma ramasa de rambursat
    bool approved; // Statusul imprumutului
    Customer *customer; // Clientul asociat

    static int loanCounter; // Contor static pentru a genera ID-uri unice de imprumut

public:
    // Constructor si destructor
    Loan(double amount, double interestRate, int termMonths, Customer *customer);
    Loan(const Loan &other);
    ~Loan();

    Loan& operator++();
    Loan operator++(int);
    Loan operator+(const Loan &other);
    bool operator==(const Loan &other) const;
    bool operator<(const Loan &other) const;
    Loan& operator=(const Loan &other);

    // Managmentul imprumuturilor
    void approve();
    void makePayment(double amount);
    double calculateInterest() const;
    void approveAndDeposit();

    //Getters
    double getRemainingBalance() const;
    bool isApproved() const;
    double getAmount() const;
    Customer* getCustomer() const;
    int getID() const;
};
#endif // LOAN_H
