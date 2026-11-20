#include "account.h"
#include "transaction.h"
#include <iostream>
using namespace std;

// Display the main menu
void mainMenu() {
    int choice;

    do {
        cout << "\n=====================================\n";
        cout << "       BANK MANAGEMENT SYSTEM\n";
        cout << "=====================================\n";
        cout << "1. Account Creation\n";
        cout << "2. Account Information & Balance Check\n";
        cout << "3. Update Account Information\n";
        cout << "4. Deposit\n";
        cout << "5. Withdrawal\n";
        cout << "6. Fund Transfer\n";
        cout << "7. Mini Statement\n";
        cout << "8. Transaction History\n";
        cout << "9. Account Closure\n";
        cout << "10. Admin Records View\n";
        cout << "0. Exit\n";
        cout << "-------------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                createAccount();
                break;

            case 2:
                viewAccount();
                break;

            case 3:
                updateAccount();
                break;

            case 4:
                deposit();
                break;

            case 5:
                withdraw();
                break;

            case 6:
                transferMoney();
                break;

            case 7:
                showMiniStatement();
                break;

            case 8:
                showTransactionHistory();
                break;

            case 9:
                deleteAccount();
                break;

            case 10:
                viewAllAccounts();
                break;

            case 0:
                cout << "\nThank you for using Bank Management System.\n";
                break;

            default:
                cout << "\nInvalid choice. Please try again.\n";
        }

        if (choice != 0) {
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }

    } while (choice != 0);
}

// Program starts from here
int main() {
    // Load saved account data before showing the menu
    loadAccounts();

    // Start the main menu
    mainMenu();

    return 0;
}
