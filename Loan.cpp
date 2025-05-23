#include "Loan.h"
#include "Customer.h"

using namespace std;

// Initializarea contorului static
int Loan::loanCounter = 1000;

// Constructor: Initializarea detalilor imprumutului
Loan::Loan(double amount, double interestRate, int termMonths, Customer *customer)
      : amount(amount), interestRate(interestRate), termMonths(termMonths), customer(customer) {
    this->remainingBalance = amount;
    this->approved = false;
    this->loanID = loanCounter++;
}

Loan::Loan(const Loan &other) {
    this->loanID = other.loanID;
    this->amount = other.amount;
    this->interestRate = other.interestRate;
    this->termMonths = other.termMonths;
    this->remainingBalance = other.remainingBalance;
    this->approved = other.approved;
    this->customer = other.customer;
}

// Destructor
Loan::~Loan() {
    cout << "Loan ID " << loanID << " closed.\n";
}

Loan& Loan::operator++() {
    loanID++;
    return *this;

}

Loan Loan::operator++(int) {
    Loan current = *this;
    ++loanID;
    return current;
}

Loan Loan::operator+(const Loan &other) {
    return Loan(amount + other.amount, interestRate + other.interestRate, termMonths + other.termMonths, customer);
}

bool Loan::operator==(const Loan &other) const {
    return this->loanID == other.loanID;
}

bool Loan::operator<(const Loan &other) const {
    return this->loanID < other.loanID;
}

int Loan::getID() const {
    return loanID;
}
// Aprobarea imprumutului
void Loan::approve() {
    this->approved = true;
    cout << "Loan ID " << loanID << " aprobat pentru " << customer->getName() << ".\n";
}


// Efectuaeza o plata
void Loan::makePayment(double amount) {
    if (!approved) {
        cout << "Loan ID " << loanID << " nu este aprobat. Nu se pot face plati.\n";
        return;
    }

    if (amount > 0 && amount <= remainingBalance) {
        remainingBalance -= amount;
        cout << "Plata de $" << amount << " facuta pentru Loan ID " << loanID
                  << ". Valoarea ramasa de platit: $" << remainingBalance << ".\n";
        Account *account = customer->getFirstAccount();
        account->withdraw(amount);
    } else {
        cout << "Suma de plata invalida.\n";
    }
}

void Loan::approveAndDeposit() {
    if (!approved) {
        approved = true;
        cout << "Loan ID " << loanID << " aprobat pentru " << customer->getName() << ".\n";

        // Obtineti primul cont bancar al clientului
        Account* account = customer->getFirstAccount();
        if (account) {
            cout << "Inainte de Depunere: Soldul contului = $" << account->getBalance() << "\n";
            account->deposit(amount);
            cout << "Dupa depunere: Soldul contului = $" << account->getBalance() << "\n";
            cout << "Valoarea imprumutului $" << amount << " depusa in contul "
                 << account->getAccountNumber() << ".\n";
        } else {
            cout << "Warning: Nu a fost gasit niciun cont pentru acest client. Suma imprumutului nu a fost depusa!\n";
        }
    } else {
        cout << "Imprumutul a fost deja aprobat.\n";
    }
}

Loan& Loan::operator=(const Loan &other) {
    if (this != &other) {
        this->loanID = other.loanID;
        this->amount = other.amount;
        this->interestRate = other.interestRate;
        this->termMonths = other.termMonths;
        this->remainingBalance = other.remainingBalance;
        this->approved = other.approved;
        this->customer = other.customer;
    }
}


// Calculati dobanda in funcție de valoarea si termenul imprumutului
double Loan::calculateInterest() const {
    return (amount * (interestRate / 100) * (termMonths / 12.0));
}

// Obtine balanta ramasa
double Loan::getRemainingBalance() const {
    return remainingBalance;
}

// Verifica daca imprumutul este valid
bool Loan::isApproved() const {
    return approved;
}

// Obtine valoarea imprumutului
double Loan::getAmount() const {
    return amount;
}

// Clientul care a facut imprumutul
Customer* Loan::getCustomer() const {
    return customer;
}
