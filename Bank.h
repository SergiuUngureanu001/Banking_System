#ifndef BANK_H
#define BANK_H

#include <iostream>
#include <vector>
#include "Customer.h"
#include "Employee.h"
#include "Account.h"
#include "Transaction.h"
#include "Loan.h"
#include "HybridAccount.h"
#include "StockAccount.h"
#include "BondAccount.h"

class Bank {
private:
    vector<Customer*> customers;
    vector<Employee*> employees;
    vector<Account*> accounts;
    vector<Loan*> loans;

public:
    // Nu este nevoie de alt tip de constructor deoarece are rolul de a initializa tot sistemul
    // care e construit pe baza instantei sale
    Bank();
    ~Bank();

    void addCustomer(Customer *customer);
    void removeCustomer(int customerID);
    Customer *findCustomer(int customerID);

    void addEmployee(Employee *employee);
    void removeEmployee(int employeeID);

    void createAccount(Customer *customer, Account *account);
    void deleteAccount(int accountNumber);
    Account *findAccount(int accountNumber);

    Loan* findLoan(int loanID);
    Employee* findEmployee(int employeeID);

    void processTransaction(const Transaction &transaction);

    void approveLoan(Loan *loan, Employee *employee);
    void addLoan(Loan* loan);
    Loan* findPendingLoan();

    void makeLoanPayment(int loanID, double amount);

    void displayAllCustomers() const;
    void displayAllAccounts() const;
    void displayAllEmployees() const;
    void displayAllLoans() const;

};

#endif // BANK_H


