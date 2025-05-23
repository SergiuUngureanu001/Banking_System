#include "Bank.h"
#include <iostream>

using namespace std;

Bank::Bank() {
    cout << "Sistem Bancar Initializat.\n";
    // Adaug niste angajati default care mai tarziu vor putea aproba sau nu un imprumut
    // vectorul employees este declarat in ambele clase pentru a nu folosi mostenirea
    // Update - Am pus employees1 la cel static
    // Din cauza ca nu nu mergea am scos vectorul static din constructor

     if (employees.empty()) {
        cout << "Se initializeaza angajatii default...\n";

        Employee* e1 = new Employee("John Doe", 101, "Manager");
        Employee* e2 = new Employee("Mucea Zinel", 102, "Cashier");
        Employee* e3 = new Employee("Lali Paulica", 103, "Loan Officer");

        employees.push_back(e1);
        employees.push_back(e2);
        employees.push_back(e3);

    }

    this->displayAllEmployees();
}

// Destructor (pentru a curata memoria)
Bank::~Bank() {
    for(Customer *customer : customers) {
        delete customer;
    }
    customers.clear();

    for(Employee *employee : employees) {
        delete employee;
    }
    employees.clear();

    for(Account *account : accounts) {
        delete account;
    }
    accounts.clear();

    cout << "Memoria sistemului bancar a fost curatata.\n";
}

void Bank::addCustomer(Customer *customer) {
    for (Customer* existingCustomer : customers) {
        if (*existingCustomer == *customer) {
            cout << "Clientul cu ID " << customer->getID() << " deja existent.\n";
            return;
        }
    }

    customers.push_back(customer);
    cout << "Clientul " << customer->getName() << " a fost adaugat cu succes.\n";
}

void Bank::removeCustomer(int customerID) {
    vector<Customer*>::iterator it = customers.begin();
    for(auto start = it; start != customers.end(); start++) {
        if((*start)->getID() == customerID) {
            delete *start; // Eliberare memoria
            customers.erase(start);
            cout << "Client sters.\n";
            return;
        }
    }
    cout << "Clientul nu a fost gasit.\n";
}

Customer *Bank::findCustomer(int customerID) {
    for(Customer *customer : customers) {
        if(customer->getID() == customerID) {
            return customer;
        }
    }
    return nullptr;
}

void Bank::addEmployee(Employee *employee) {
    employees.push_back(employee);
}

void Bank::removeEmployee(int employeeID) {
    for(auto start = employees.begin(); start != employees.end(); start++) {
        if((*start)->getID() == employeeID) {
            delete *start; // Elibereaza memoria
            employees.erase(start);
            cout << "Angajatul a fost sters.\n";
            return;
        }
    }
    cout << "Angajatul nu a fost gasit.\n";
}

void Bank::createAccount(Customer* customer, Account* account) {
    for (Account* existingAccount : accounts) {
        if (*account == *existingAccount) {
            cout << "Contul cu Numarul " << account->getAccountNumber() << " deja existent.\n";
            return;
        }
    }

    accounts.push_back(account);
    customer->addAccount(account);

    auto* ptr = dynamic_cast<HybridAccount*>(&*account);

    if (ptr) {
        cout << "Contul hibrid a fost creat cu succes pentru clientul " << customer->getName() << "!\n";
    } else {
        cout << "Cont " << account->getAccountNumber() << " creat pentru " << customer->getName() << ".\n";
    }
}


void Bank::deleteAccount(int accountNumber) {
    for (auto it = accounts.begin(); it != accounts.end(); ++it) {
        if ((*it)->getAccountNumber() == accountNumber) {
            delete *it;
            accounts.erase(it);
            return;
        }
    }
    cout << "Contul nu a putut fi gasit.\n";
}



Account* Bank::findAccount(int accountNumber) {
    for (Account* account : accounts) {
        if (account->getAccountNumber() == accountNumber) {
            return account;
        }
    }
    return nullptr;
}

Loan* Bank::findLoan(int loanID) {
    for (Loan* loan : loans) {
        if (loan->getID() == loanID) {
            return loan;
        }
    }
    return nullptr;
}

void Bank::makeLoanPayment(int loanID, double amount) {
    Loan* loan = findLoan(loanID);

    if (!loan) {
        cout << "Error: Loan ID " << loanID << " nu a fost gasit!\n";
        return;
    }

    if (!loan->isApproved()) {
        cout << "Error: Loan ID " << loanID << " nu a fost aprobat inca!\n";
        return;
    }

    loan->makePayment(amount);
}

Employee* Bank::findEmployee(int employeeID) {
    for (Employee* employee : employees) {
        if (employee->getID() == employeeID) {
            return employee;
        }
    }
    return nullptr;
}

void Bank::processTransaction(const Transaction& transaction) {
    Account* sourceAccount = findAccount(transaction.getSourceAccount());
    Account* targetAccount = findAccount(transaction.getTargetAccount());

    if (!sourceAccount || !targetAccount) {
        cout << "Tranzactie esuata: Cont invalid.\n";
        return;
    }

    if (transaction.getType() == "Transfer") {
        if (sourceAccount->withdraw(transaction.getAmount())) {
            targetAccount->deposit(transaction.getAmount());
            cout << "Tranzactie cu succes: $" << transaction.getAmount()
                      << " trasferati de la " << sourceAccount->getAccountNumber()
                      << " la " << targetAccount->getAccountNumber() << ".\n";
        } else {
            cout << "Tranzactie esuata: Fond insuficient.\n";
        }
    }
}

// Aproba o imprumut
void Bank::approveLoan(Loan* loan, Employee* employee) {
    if (employee->canApproveLoans()) {
        loan->approveAndDeposit();
    } else {
        cout << "Aprobarea imprumutului a esuat: Angajat neautorizat.\n";
    }
}

void Bank::addLoan(Loan* loan) {
    loans.push_back(loan);
    cout << "Loan ID " << loan->getID() << " agaugat in sistem.\n";
}

Loan* Bank::findPendingLoan() {
    for (Loan* loan : loans) {
        if (!loan->isApproved()) {
            return loan;
        }
    }
    cout << "Nu exista imprumuturi in asteptare.\n";
    return nullptr;
}

void Bank::displayAllCustomers() const {
    //cout << "Lista Clienti:\n";
    for(const Customer* customer : customers) {
        cout << "- " << customer->getName() << " (ID: " << customer->getID() << ")\n";
    }
}

void Bank::displayAllAccounts() const {
    cout << "Lista Conturi:\n";
    for (const Account* account : accounts) {
        // Perform the dynamic cast to a const HybridAccount* type
        auto ptr = dynamic_cast<const HybridAccount*>(account);
        auto ptr2 = dynamic_cast<const StockAccount*>(account);
        auto ptr3 = dynamic_cast<const BondAccount*>(account);

        if (ptr) {
            ptr->displayAccountDetails();
        } else if (ptr2) {
            //TODO
            cout << "- Numarul Contului de Actiuni: " << ptr2->getAccountNumber()
                 << ", Balance: $" << ptr2->getBalance() << "\n";
        } else if (ptr3) {
            cout << "- Numarul Contului de Obligatiuni: " << ptr3->getAccountNumber()
                 << ", Balance: $" << ptr3->getBalance() << "\n";
        } else {
            cout << "- Numarul Contului: " << account->getAccountNumber()
                 << ", Balance: $" << account->getBalance() << "\n";
        }
    }
}

void Bank::displayAllEmployees() const{
    cout << "Lista Angajati:\n";
    if (employees.empty()) {
        cout << "No employees available!\n";  // Debugging
    } else {
        for (Employee* emp : employees) {
            cout << "- " << emp->getName() << " (ID: " << emp->getID()
                 << ", Functie: " << emp->getRole() << ")\n";
        }
    }
}


// DEBUG
void Bank::displayAllLoans() const {
    if (loans.empty()) {
        cout << "Niciun imprumut momentan.\n";
        return;
    }

    cout << "\n--- Lista imprumuturilor ---\n";
    for (const Loan* loan : loans) {
        cout << "Loan ID: " << loan->getID()
             << ", Suma: $" << loan->getAmount()
             << ", Dobanda: " << loan->calculateInterest() << "%"
             << ", Termen: " << loan->getRemainingBalance() << " luni"
             << ", Status: " << (loan->isApproved() ? "Aprobat" : "In asteptare")
             << ", Client: " << loan->getCustomer()->getName() << " (ID: "
             << loan->getCustomer()->getID() << ")\n";
    }
    cout << "----------------------\n";
}


