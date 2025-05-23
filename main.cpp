#include <iostream>
#include <cstdlib> // pentru a adauga angajati
#include <ctime> // cu o funtie(rol) random care pot aproba sau nu un imprumut
#include "Bank.h"

using namespace std;

// instanta pe care se construieste tot progeamul

Bank bank;

void displayMenu() {
    cout << "\n--- Rothschild & Co Banking ---\n";
    cout << "1. Adauga Client\n";
    cout << "2. Afiseaza Clienti\n";
    cout << "3. Creeaza Cont pentru Client\n";
    cout << "4. Afiseaza Conturi\n";
    cout << "5. Depunere Bani\n";
    cout << "6. Retragere Bani\n";
    cout << "7. Transfer Bani\n";
    cout << "8. Creare Imprumut\n";
    cout << "9. Aprobare Imprumut\n";
    cout << "10. Stergere Cont\n";
    cout << "11. Plata Imprumut\n";
    cout << "12. Istoric Tranzactii\n";
    cout << "13. Adauga Angajati\n";
    cout << "14. Creeaza Cont Custom pentru Client\n";
    cout << "15. Creeaza Cont pentru Investitii\n";
    cout << "16. Cumpara sau Vinde Active\n";
    cout << "17. Iesire\n";
    cout << "Alege o optiune: ";
}

int main() {
    srand(time(0));
    int optiune;
    do {
        displayMenu();
        cin >> optiune;
        cin.ignore();

        switch(optiune) {
            case 1: {
                Customer *customer = new Customer();
                cin >> *customer;
                bank.addCustomer(customer);
                break;
            }

            case 2:
                bank.displayAllCustomers();
                break;

            case 3: {
                int idClient;
                cout << "Introduceti ID client: ";
                cin >> idClient;
                Customer* client = bank.findCustomer(idClient);
                if(client) {
                    Account *account = new Account(0, 0);
                    cin >> *account;
                    bank.createAccount(client, account);
                } else {
                    cout << "Clientul nu exista! Anulare crearea contului.\n";
                }
                break;
            }

            case 4:
                bank.displayAllAccounts();
                break;

            case 5: {
                int numarCont;
                double suma;
                cout << "Introduceti numarul contului: ";
                cin >> numarCont;
                cout << "Introduceti suma de depus: ";
                cin >> suma;
                Account* cont = bank.findAccount(numarCont);
                if (cont) {
                    cont->deposit(suma);
                    cout << "Depunere reusita!\n";
                } else {
                    cout << "Cont inexistent!\n";
                }
                break;
            }

            case 6: {
                int numarCont;
                double suma;
                cout << "Introduceti numarul contului: ";
                cin >> numarCont;
                cout << "Introduceti suma de retras: ";
                cin >> suma;
                Account* cont = bank.findAccount(numarCont);
                if (cont && cont->withdraw(suma)) {
                    cout << "Retragere reusita!\n";
                } else {
                    cout << "Fonduri insuficiente sau cont inexistent!\n";
                }
                break;
            }

            case 7: {
                int sursa, destinatie;
                double suma;
                cout << "Introduceti numarul contului sursa: ";
                cin >> sursa;
                cout << "Introduceti numarul contului destinatie: ";
                cin >> destinatie;
                cout << "Introduceti suma: ";
                cin >> suma;

                Account* contSursa = bank.findAccount(sursa);
                Account* contDest = bank.findAccount(destinatie);
                if (contSursa && contDest && contSursa->withdraw(suma)) {
                    contDest->deposit(suma);
                    cout << "Transfer reusit!\n";

                    Transaction* newTransaction = new Transaction(suma, "Transfer", sursa, destinatie);
                    newTransaction->printTransaction();
                } else {
                    cout << "Eroare la transfer!\n";
                }
                break;
            }

            case 8: {
                int idClient;
                double amount, interestRate;
                int termMonths;

                cout << "Introduceti ID client: ";
                cin >> idClient;
                cout << "Introduceti suma imprumutata: ";
                cin >> amount;
                cout << "Introduceti rata dobanzii (%): ";
                cin >> interestRate;
                cout << "Introduceti durata in luni: ";
                cin >> termMonths;

                Customer* client = bank.findCustomer(idClient);
                if (client) {
                    Loan* newLoan = new Loan(amount, interestRate, termMonths, client);
                    bank.addLoan(newLoan);
                    cout << "Imprumut creat cu succes! Loan ID: " << newLoan->getID() << "\n";
                } else {
                    cout << "Eroare: Clientul nu exista!\n";
                }
                break;
            }

            case 9: {
                cout << "Lista imprumuturi:\n";
                bank.displayAllLoans();
                bank.displayAllEmployees();
                int loanID, empID;
                cout << "Introduceti ID angajat care aproba: ";
                cin >> empID;

                Loan* loan = bank.findPendingLoan();
                Employee* emp = bank.findEmployee(empID);
                if (loan && emp && emp->canApproveLoans()) {
                    bank.approveLoan(loan, emp);
                    cout << "Imprumut aprobat! Loan ID: " << loan->getID() << "\n";
                } else {
                    cout << "Eroare: Angajatul nu poate aproba imprumutul sau ID invalid!\n";
                }
                break;
            }

            case 10: {
                int numarCont;
                cout << "Introduceti numarul contului de sters: ";
                cin >> numarCont;
                bank.deleteAccount(numarCont);
                break;
            }

            case 11: {
                int loanID;
                double amount;
                cout << "Introduceti ID-ul imprumutului: ";
                cin >> loanID;
                cout << "Introduceti suma de plata: ";
                cin >> amount;

                bank.makeLoanPayment(loanID, amount);
                break;
            }

            case 12: {
                Transaction::displayTransactionHistory();
                // Mai simplu decat sa folosesc operatorul de afisare <<
                break;
            }

            case 13: {
                Employee *newEmp = new Employee("", 0, "");
                cin >> *newEmp;
                bank.addEmployee(newEmp);
                cout << "Angajat adaugat cu succes! " << newEmp->getName() << " (ID: "
                     << newEmp->getID() << ", Rol: " << newEmp->getRole() << ")\n";

                bank.displayAllEmployees();
                break;
            }

            case 14: {
                int idClient;
                cout << "Introduceti ID client: ";
                cin >> idClient;

                Customer* client = bank.findCustomer(idClient);
                if (client) {

                HybridAccount* hybridAccount = new HybridAccount(0.00, 0, 0.00);
                cin >> *hybridAccount;

                bank.createAccount(client, hybridAccount);

            } else {
                cout << "Clientul nu exista! Anulare crearea contului.\n";
            }
                break;
            }

            case 15: {
                int idClient;
                cout << "Introduceti ID-ul clientului: ";
                cin >> idClient;

                Customer* client = bank.findCustomer(idClient);
                if(client) {
                    int accountType;
                    cout << "Alege tipul de cont de investitii:\n";
                    cout << "1. Cont actiuni\n";
                    cout << "2. Cont obligatiuni\n";
                    cout << "Alege tipul de cont: ";
                    cin >> accountType;

                    double balance, interestRate;
                    int accountNumber;

                    cout << "Introduceti numarul contului: ";
                    cin >> accountNumber;

                    cout << "Introduceti balanta initiala: ";
                    cin >> balance;

                    cout << "Introduceti rata dobanzii: ";
                    cin >> interestRate;

                    InvestmentAccount* investmentAccount = nullptr;

                    if (accountType == 1) {
                        int pricePerStock;
                        cout << "Introduceti pretul per actiune: ";
                        cin >> pricePerStock;
                        investmentAccount = new StockAccount(balance, accountNumber, 0.0, interestRate, pricePerStock);
                        cout << "Contul de actiuni a fost creat cu succes.\n";
                    } else if (accountType == 2) {
                        int pricePerBond;
                        cout << "Introduceti pretul per obligatiune: ";
                        cin >> pricePerBond;
                        investmentAccount = new BondAccount(balance, accountNumber, 0.0, interestRate, 5.0, pricePerBond);
                        cout << "Contul de obligatiuni a fost creat cu succes.\n";
                    } else {
                        cout << "Optiune invalida!\n";
                        break;
                    }

                    bank.createAccount(client, investmentAccount);

                } else {
                    cout << "Clientul nu exista!\n";
                }
                break;
            }

            case 16: {
                int idClient, accountNumber;
                cout << "Introduceti ID-ul clientului: ";
                cin >> idClient;
                cout << "Introduceti Numarul Contului: ";
                cin >> accountNumber;

                Customer* client = bank.findCustomer(idClient);
                if(client && client->verifyAccount(accountNumber)) {
                    int accountType;
                    cout << "Alege tipul de cont de investitii:\n";
                    cout << "1. Cont actiuni\n";
                    cout << "2. Cont obligatiuni\n";
                    cout << "Alege tipul de cont: ";
                    cin >> accountType;

                    double amount;
                    bool result = false;

                    if (accountType == 1) {
                        StockAccount* stockAccount = dynamic_cast<StockAccount*>(bank.findAccount(accountNumber));
                        if (stockAccount) {
                            stockAccount->displayInvestmentDetails();
                            cout << "Introduceti suma de actiuni de cumparat: ";
                            cin >> amount;
                            result = stockAccount->buyAsset(amount);
                            if (result) {
                                cout << "Cumparare actiuni reusita!\n";
                            } else {
                                cout << "Eroare la cumpararea actiunilor!\n";
                            }
                        } else {
                            cout << "Numar Cont introdus invalid.\n";
                            continue;
                        }
                    } else if (accountType == 2) {
                        BondAccount* bondAccount = dynamic_cast<BondAccount*>(bank.findAccount(accountNumber));
                        if (bondAccount) {
                            bondAccount->displayInvestmentDetails();
                            cout << "Introduceti suma de obligatiuni de cumparat: ";
                            cin >> amount;
                            result = bondAccount->buyAsset(amount);
                            if (result) {
                                cout << "Cumparare obligatiuni reusita!\n";
                            } else {
                                cout << "Eroare la cumpararea obligatiunilor!\n";
                            }
                        } else {
                            cout << "Numar Cont introdus invalid.\n";
                            continue;
                        }
                    } else {
                        cout << "Optiune invalida!\n";
                        break;
                    }

                    cout << "Vreti sa vindeti active? (1 pentru da, 0 pentru nu): ";
                    int sellOption;
                    cin >> sellOption;

                    if (sellOption == 1) {
                        if (accountType == 1) {
                            StockAccount* stockAccount = dynamic_cast<StockAccount*>(bank.findAccount(accountNumber));
                            if (stockAccount) {
                                cout << "Introduceti suma de actiuni de vandut: ";
                                cin >> amount;
                                result = stockAccount->sellAsset(amount);
                                if (result) {
                                    cout << "Vanzare actiuni reusita!\n";
                                } else {
                                    cout << "Eroare la vanzarea actiunilor!\n";
                                }
                            } else {
                                cout << "Numar Cont introdus invalid.\n";
                                continue;
                            }
                        } else if (accountType == 2) {
                            BondAccount* bondAccount = dynamic_cast<BondAccount*>(bank.findAccount(accountNumber));
                            if (bondAccount) {
                                cout << "Introduceti suma de obligatiuni de vandut: ";
                                cin >> amount;
                                result = bondAccount->sellAsset(amount);
                                if (result) {
                                    cout << "Vanzare obligatiuni reusita!\n";
                                } else {
                                    cout << "Eroare la vanzarea obligatiunilor!\n";
                                }
                            } else {
                                cout << "Numar Cont introdus invalid.\n";
                                continue;
                            }
                        }
                    }
                } else {
                    cout << "Date cont introduse gresit!\n";
                }
                break;
            }

            case 17:
                cout << "Iesire din sistemul bancar...\n";
                break;

            default:
                cout << "Optiune invalida! Incercati din nou.\n";
        }

    } while (optiune != 17);

    return 0;
}

