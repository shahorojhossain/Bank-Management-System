#include "account.h"
#include "transaction.h"
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

const string ADMIN_PASSWORD = "shahoroj";

// Store all accounts in memory
vector<Account> accounts;

// Find an account using its account number
int findAccountIndex(int accountNo) {
    for (int i = 0; i < (int)accounts.size(); i++) {
        if (accounts[i].accountNo == accountNo)
            return i;
    }
    return -1;
}

// Check whether an account exists
bool accountExists(int accountNo) {
    return findAccountIndex(accountNo) != -1;
}

// Generate a new account number
int getNextAccountNo() {
    int maxNo = 1000;

    for (const Account& acc : accounts) {
        if (acc.accountNo > maxNo)
            maxNo = acc.accountNo;
    }

    return maxNo + 1;
}

// Create a new bank account
void createAccount() {
    Account acc;
    acc.accountNo = getNextAccountNo();

    cout << "\n===== ACCOUNT CREATION =====\n";
    cout << "Account Number: " << acc.accountNo << "\n";

    cin.ignore();

    cout << "Enter Name: ";
    getline(cin, acc.name);

    cout << "Enter Phone: ";
    getline(cin, acc.phone);

    cout << "Enter Address: ";
    getline(cin, acc.address);

    cout << "Set 4-digit PIN: ";
    getline(cin, acc.pin);

    cout << "Initial Deposit: ";
    cin >> acc.balance;

    if (acc.balance < 0) {
        cout << "Invalid amount.\n";
        return;
    }

    accounts.push_back(acc);
    saveAccounts();

    // Save the initial deposit in transaction history
    if (acc.balance > 0) {
        Transaction t;
        t.accountNo = acc.accountNo;
        t.type = "Initial Deposit";
        t.amount = acc.balance;
        t.relatedAccount = 0;
        t.dateTime = getCurrentDateTime();
        saveTransaction(t);
    }

    cout << "\nAccount created successfully.\n";
}

// Read and display one account
void viewAccount() {
    int no;

    cout << "\nEnter Account Number: ";
    cin >> no;

    int index = findAccountIndex(no);

    if (index == -1) {
        cout << "Account not found.\n";
        return;
    }

    Account acc = accounts[index];

    cout << "\n===== ACCOUNT INFORMATION =====\n";
    cout << "Account Number : " << acc.accountNo << "\n";
    cout << "Name           : " << acc.name << "\n";
    cout << "Phone          : " << acc.phone << "\n";
    cout << "Address        : " << acc.address << "\n";
    cout << fixed << setprecision(2);
    cout << "Balance        : " << acc.balance << "\n";
}

// Update account information
void updateAccount() {
    int no;

    cout << "\nEnter Account Number: ";
    cin >> no;

    int index = findAccountIndex(no);

    if (index == -1) {
        cout << "Account not found.\n";
        return;
    }

    cin.ignore();

int choice;

cout << "\nWhat do you want to update?\n";
cout << "1. Name\n";
cout << "2. Phone\n";
cout << "3. Address\n";
cout << "4. PIN\n";
cout << "Enter your choice: ";
cin >> choice;

cin.ignore();

if (choice == 1)
{
    cout << "Enter New Name: ";
    getline(cin, accounts[index].name);
}
else if (choice == 2)
{
    cout << "Enter New Phone: ";
    getline(cin, accounts[index].phone);
}
else if (choice == 3)
{
    cout << "Enter New Address: ";
    getline(cin, accounts[index].address);
}
else if (choice == 4)
{
    cout << "Enter New PIN: ";
    getline(cin, accounts[index].pin);
}
else
{
    cout << "Invalid choice.\n";
}

saveAccounts();

cout << "\nAccount information updated successfully.\n";
}

// Delete or close an account
void deleteAccount() {
    int no;

    cout << "\nEnter Account Number to close: ";
    cin >> no;

    int index = findAccountIndex(no);

    if (index == -1) {
        cout << "Account not found.\n";
        return;
    }

    // Account can only be closed when balance is zero
    if (accounts[index].balance != 0) {
        cout << "Account cannot be closed because balance is not zero.\n";
        cout << "Current Balance: " << accounts[index].balance << "\n";
        return;
    }

    accounts.erase(accounts.begin() + index);
    saveAccounts();

    cout << "\nAccount closed successfully.\n";
}

// Display all account records
void viewAllAccounts() {
    string password;

    cout << "\nEnter Admin Password: ";
    cin >> password;

    if (password != ADMIN_PASSWORD) {
        cout << "Wrong password! Access denied.\n";
        return;
    }

    if (accounts.empty()) {
        cout << "\nNo account records found.\n";
        return;
    }

    cout << "\n================ ALL ACCOUNT RECORDS ================\n";
    cout << left << setw(12) << "Account"
         << setw(22) << "Name"
         << setw(16) << "Phone"
         << setw(15) << "Balance" << "\n";

    cout << "------------------------------------------------------\n";

    for (const Account& acc : accounts) {
        cout << left << setw(12) << acc.accountNo
             << setw(22) << acc.name.substr(0, 20)
             << setw(16) << acc.phone
             << fixed << setprecision(2)
             << setw(15) << acc.balance << "\n";
    }
}

// Load account records from accounts.txt
void loadAccounts() {
    accounts.clear();

    ifstream file("accounts.txt");
    Account acc;

    while (file >> acc.accountNo) {
        file.ignore();

        getline(file, acc.name);
        getline(file, acc.phone);
        getline(file, acc.address);
        getline(file, acc.pin);

        file >> acc.balance;
        file.ignore();

        accounts.push_back(acc);
    }

    file.close();
}

// Save all account records to accounts.txt
void saveAccounts() {
    ofstream file("accounts.txt");

    for (const Account& acc : accounts) {
        file << acc.accountNo << "\n";
        file << acc.name << "\n";
        file << acc.phone << "\n";
        file << acc.address << "\n";
        file << acc.pin << "\n";
        file << acc.balance << "\n";
    }

    file.close();
}

