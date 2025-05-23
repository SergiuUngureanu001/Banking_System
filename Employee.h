#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <iostream>
#include <vector>
#include "Loan.h"

using namespace std;

class Employee {
private:
    int employeeID;       // codul unic de angajat
    string name;     // numele angajatului
    string role;     // rolul angajatului
    // static vector<Employee*> employees1; (Am renuntat la el)

public:
    // Constructor & Destructor
    Employee(string name, int id, string role);
    Employee(const Employee &other);
    ~Employee();

    // static void addEmployee(Employee* employee);
    // static void displayAllEmployees();

    /// static vector<Employee*>& getEmployees(); // Getter pt clasa Bank

    Employee& operator++();
    Employee operator++(int);
    Employee operator+(const Employee &other);
    bool operator==(const Employee &other) const;
    bool operator<(const Employee &other) const;
    Employee& operator=(const Employee &other);

    void approveLoan(Loan* loan);
    void rejectLoan(Loan* loan);

    bool canApproveLoans() const;

    void displayDetails() const;

    // Getters
    int getID() const;
    string getName() const;
    string getRole() const;

    friend istream& operator>>(istream& in, Employee& employee);
};

#endif // EMPLOYEE_H

