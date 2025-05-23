#include "Transaction.h"
#include "Bank.h"
#include <iostream>
#include <ctime>

// Folosesc instanta banca definita intr-un alt file
extern Bank bank;

// Initializeaza contorul tranzactiilor
int Transaction::transactionCounter = 1000;
vector<Transaction*> Transaction::transactionHistory;

// Obtine timpul la care s-a efectuat trazanctia
string Transaction::getCurrentTime() const {
    // sintaxa stupida
    time_t now = time(0);
    char buffer[80];
    struct tm timeinfo;

    localtime_r(&now, &timeinfo);

    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeinfo);
    return string(buffer);
}

// Initializeaza detaliile tranzactiei
Transaction::Transaction(double amount, string type, int sourceAccount, int targetAccount)
    : amount(amount), transactionType(type), sourceAccountNumber(sourceAccount), targetAccountNumber(targetAccount) {
    this->transactionID = transactionCounter++;
    this->timestamp = getCurrentTime();

    Transaction::addTransaction(this);
}

Transaction::Transaction(const Transaction &other) {
    this->transactionID = other.transactionID;
    this->amount = other.amount;
    this->transactionType = other.transactionType;
    this->sourceAccountNumber = other.sourceAccountNumber;
    this->targetAccountNumber = other.targetAccountNumber;
    this->timestamp = other.timestamp;
}

Transaction& Transaction::operator=(const Transaction &other) {
    if (this != &other) {
        this->transactionID = other.transactionID;
        this->amount = other.amount;
        this->transactionType = other.transactionType;
        this->sourceAccountNumber = other.sourceAccountNumber;
        this->targetAccountNumber = other.targetAccountNumber;
        this->timestamp = other.timestamp;
    }
    return *this;
}

// Destructor
Transaction::~Transaction() {
    cout << "Transaction ID " << transactionID << " logged.\n";
}

void Transaction::addTransaction(Transaction *transaction) {
    transactionHistory.push_back(transaction);
}

Transaction& Transaction::operator++() {
    ++transactionID;
    return *this;
}

Transaction Transaction::operator++(int) {
    Transaction current = *this;
    transactionID++;
    return current;
}

Transaction Transaction::operator+(const Transaction &other) {
    double combinedAmount = this->amount + other.amount;
    Transaction newTransaction(combinedAmount, this->transactionType, this->sourceAccountNumber, this->targetAccountNumber);
    return newTransaction;
}

bool Transaction::operator==(const Transaction &other) const {
    return this->transactionID == other.transactionID;
}

bool Transaction::operator<(const Transaction &other) const {
    return this->amount < other.amount;
}

// Executa tranzactia
void Transaction::execute() {
    Account* sourceAccount = bank.findAccount(sourceAccountNumber);
    Account* targetAccount = bank.findAccount(targetAccountNumber);

    if (!sourceAccount) {
        cout << "Tranzactia a esuat: Contul sursa invalid.\n";
        return;
    }

    if (transactionType == "Deposit") {
        sourceAccount->deposit(amount);
        cout << "Transaction ID " << transactionID << ": Depus $" << amount
                  << " in Contul " << sourceAccount->getAccountNumber() << ".\n";
    }
    else if (transactionType == "Withdrawal") {
        if (sourceAccount->withdraw(amount)) {
            cout << "Transaction ID " << transactionID << ": S-a retras $" << amount
                      << " din Contul " << sourceAccount->getAccountNumber() << ".\n";
        } else {
            cout << "Transaction ID " << transactionID << " esuat: Sold insuficient.\n";
        }
    }
    else if (transactionType == "Transfer") {
        if (!targetAccount) {
            cout << "Tranzactia a esuat: Contul destinatar invalid.\n";
            return;
        }
        if (sourceAccount->withdraw(amount)) {
            targetAccount->deposit(amount);
            cout << "Transaction ID " << transactionID << ": Transferat $" << amount
                      << " din Contul " << sourceAccount->getAccountNumber()
                      << " in Contul " << targetAccount->getAccountNumber() << ".\n";
        } else {
            cout << "Transaction ID " << transactionID << " esuat: Sold insuficient.\n";
        }
    }
}

// Afiseaza detaliile tranzactiei
void Transaction::printTransaction() const {
    cout << "Transaction ID: " << transactionID << "\n"
              << "Type: " << transactionType << "\n"
              << "Suma: $" << amount << "\n"
              << "Data: " << timestamp << "\n";

    if (sourceAccountNumber != -1) {
        cout << "Contul Sursa: " << sourceAccountNumber << "\n";
    }
    if (targetAccountNumber != -1) {
        cout << "Contul Destinatie: " << targetAccountNumber << "\n";
    }

    cout << "----------------------\n";
}

void Transaction::displayTransactionHistory() {
    cout << "\n--- Istoricul Tranzactiilor ---\n";
    if (transactionHistory.empty()) {
        cout << "Nu a fost inregistrata nicio tranzactie.\n";
    } else {
        for (const auto& val : transactionHistory) {
            val->printTransaction();
        }
    }
    cout << "----------------------------\n";
}


// Obtine numarul Contului Sursa
int Transaction::getSourceAccount() const {
    return sourceAccountNumber;
}

// Obtine numarul contului destinatie
int Transaction::getTargetAccount() const {
    return targetAccountNumber;
}

int Transaction::getTransactionID() const {
    return transactionID;
}
// Obtine valoarea tranzactiei
double Transaction::getAmount() const {
    return amount;
}

// Obtine tipul tranzactiei
string Transaction::getType() const {
    return transactionType;
}

ostream& operator<<(ostream &out, const Transaction &transaction) {
    out << "ID Tranzactie: " << transaction.getTransactionID() << "\n"
        << "Suma: $" << transaction.getAmount() << "\n"
        << "Tip: " << transaction.getType() << "\n"
        << "Cont Sursa: " << transaction.getSourceAccount() << "\n"
        << "Cont Destinatie: " << transaction.getSourceAccount() << "\n"
        << "Data: " << transaction.getCurrentTime() << "\n";
    return out;
}
