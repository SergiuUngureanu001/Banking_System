#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <iostream>
#include "Account.h"

class Transaction {
private:
    static int transactionCounter;
    static vector<Transaction*> transactionHistory;
    int transactionID;
    double amount;
    string transactionType;
    int sourceAccountNumber;
    int targetAccountNumber;
    string timestamp;

public:
    Transaction(double amount, string type, int sourceAccount, int targetAccount = -1);
    Transaction(const Transaction &other);
    ~Transaction();

    Transaction& operator++();
    Transaction operator++(int);
    Transaction operator+(const Transaction &other);
    bool operator==(const Transaction &other) const;
    bool operator<(const Transaction &other) const;
    Transaction& operator=(const Transaction &other);

    void execute();
    void printTransaction() const;

    int getSourceAccount() const;
    int getTargetAccount() const;
    int getTransactionID() const;
    double getAmount() const;
    string getType() const;
    string getCurrentTime() const;
    static void displayTransactionHistory();
    static void addTransaction(Transaction *transaction);
    friend ostream& operator<<(ostream &out, Transaction &transaction);
};

#endif // TRANSACTION_H
