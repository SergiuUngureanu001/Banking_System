#include "Employee.h"
#include "Loan.h"
#include "Customer.h"

// vector<Employee*> Employee::employees1;

// Constructor: Initializeaza detaliile angajatului
Employee::Employee(string name, int id, string role)
    : name(name), employeeID(id), role(role) {}

Employee::Employee(const Employee &other) {
    this->employeeID = other.employeeID;
    this->name = other.name;
    this->role = other.role;
}

// Destructor
Employee::~Employee() {
    cout << "Angajat " << name << " (ID: " << employeeID << ") sters.\n";
}

Employee& Employee::operator++() {
    ++employeeID;
    return *this;
}

Employee Employee::operator++(int) {
    Employee current = *this;
    employeeID++;
    return current;
}

Employee Employee::operator+(const Employee &other) {
    Employee emp = *this < other ? other : *this;
    return Employee(name + "&" + other.name, employeeID + other.employeeID, emp.role);
}

bool Employee::operator==(const Employee &other) const {
    return this->employeeID == other.employeeID;
}

bool Employee::operator<(const Employee &other) const {
    if(role != other.role)
        return role < other.role;
    return employeeID < other.employeeID;
}

Employee& Employee::operator=(const Employee &other) {
    if (this != &other) {
        this->employeeID = other.employeeID;
        this->name = other.name;
        this->role = other.role;
    }
}

/*
void Employee::addEmployee(Employee* employee) {
    Employee::employees1.push_back(employee);
}

vector<Employee*>& Employee::getEmployees() {
    return Employee::employees1;
}

void Employee::displayAllEmployees() {
    cout << "Lista Angajati:\n";
    if (Employee::employees1.empty()) {
        cout << "Niciun angajat disponibil!\n";  // Debugg
    } else {
        for (Employee* emp : Employee::employees1) {
            cout << "- " << emp->getName() << " (ID: " << emp->getID()
                 << ", Functie: " << emp->getRole() << ")\n";
        }
    }
}
*/

// Aproba un imprumut
void Employee::approveLoan(Loan* loan) {
    if(!loan->isApproved()) {
        loan->approve();
        cout << "Angajat " << name << " aproba Loan ID " << loan->getAmount() << " pentru clientul "
                  << loan->getCustomer()->getName() << ".\n";
    } else {
        cout << "Imprumutul a fost deja aprobat.\n";
    }
}

// NU aproba un imprumut
void Employee::rejectLoan(Loan* loan) {
    if(!loan->isApproved()) {
        cout << "Angajatul " << name << " A respins cererea de imprumut de $"
                  << loan->getAmount() << " de la Clientul "
                  << loan->getCustomer()->getName() << ".\n";
    } else {
        cout << "Imprumutul este deja aprobat, nu poate fi respins.\n";
    }
}

bool Employee::canApproveLoans() const {
    return role == "Manager" || role == "Loan Officer";  // Doar Managerii si Loan Officerii pot aproba
}

// Afiseaza detalile angajatului
void Employee::displayDetails() const {
    cout << "Employee ID: " << employeeID << "\n"
              << "Name: " << name << "\n"
              << "Role: " << role << "\n";
}

// Obtine ID-ul angajatului
int Employee::getID() const {
    return employeeID;
}

// Obtine numele angajatului
string Employee::getName() const {
    return name;
}

// Obtine rolul angajatului
string Employee::getRole() const {
    return role;
}

istream& operator>>(istream& in, Employee& employee) {
    cout << "Introduceti numele angajatului: ";
    in >> ws;
    getline(in, employee.name);

    cout << "Introduceti ID angajat: ";
    in >> employee.employeeID;

    string roles[] = {"Manager", "Cashier", "Loan Officer"};
    employee.role = roles[rand() % 3]; // Assign random role

    return in;
}

