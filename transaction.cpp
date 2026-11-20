#include "transaction.h"
#include "account.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
using namespace std;

// Get current date and time
string getCurrentDateTime() {
    time_t now = time(0);
    tm* localTime = localtime(&now);

    char buffer[30];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localTime);

    return string(buffer);
}

// Save one transaction in transactions.txt
void saveTransaction(const Transaction& t) {
    ofstream file("transactions.txt", ios::app);

    file << t.accountNo << "|"
         << t.type << "|"
         << t.amount << "|"
         << t.relatedAccount << "|"
         << t.dateTime << "\n";

    file.close();
}

// Deposit money into an account
void deposit() {
    int no;
    double amount;

    cout << "\nEnter Account Number: ";
    cin >> no;

    int index = findAccountIndex(no);

    if (index == -1) {
        cout << "Account not found.\n";
        return;
    }

    cout << "Enter Deposit Amount: ";
    cin >> amount;

    if (amount <= 0) {
        cout << "Invalid amount.\n";
        return;
    }

    accounts[index].balance += amount;
    saveAccounts();

    Transaction t;
    t.accountNo = no;
    t.type = "Deposit";
    t.amount = amount;
    t.relatedAccount = 0;
    t.dateTime = getCurrentDateTime();
    saveTransaction(t);

    cout << "\nDeposit successful.\n";
    cout << "New Balance: " << fixed << setprecision(2)
         << accounts[index].balance << "\n";
}

// Withdraw money from an account
void withdraw() {
    int no;
    double amount;

    cout << "\nEnter Account Number: ";
    cin >> no;

    int index = findAccountIndex(no);

    if (index == -1) {
        cout << "Account not found.\n";
        return;
    }

    cout << "Enter Withdrawal Amount: ";
    cin >> amount;

    if (amount <= 0) {
        cout << "Invalid amount.\n";
        return;
    }

    if (amount > accounts[index].balance) {
        cout << "Insufficient balance.\n";
        return;
    }

    accounts[index].balance -= amount;
    saveAccounts();

    Transaction t;
    t.accountNo = no;
    t.type = "Withdrawal";
    t.amount = amount;
    t.relatedAccount = 0;
    t.dateTime = getCurrentDateTime();
    saveTransaction(t);

    cout << "\nWithdrawal successful.\n";
    cout << "New Balance: " << fixed << setprecision(2)
         << accounts[index].balance << "\n";
}

// Transfer money between two accounts
void transferMoney() {
    int from, to;
    double amount;

    cout << "\nEnter Sender Account: ";
    cin >> from;

    cout << "Enter Receiver Account: ";
    cin >> to;

    if (from == to) {
        cout << "Sender and receiver cannot be the same.\n";
        return;
    }

    int sender = findAccountIndex(from);
    int receiver = findAccountIndex(to);

    if (sender == -1 || receiver == -1) {
        cout << "One or both accounts not found.\n";
        return;
    }

    cout << "Enter Transfer Amount: ";
    cin >> amount;

    if (amount <= 0) {
        cout << "Invalid amount.\n";
        return;
    }

    if (amount > accounts[sender].balance) {
        cout << "Insufficient balance.\n";
        return;
    }

    accounts[sender].balance -= amount;
    accounts[receiver].balance += amount;
    saveAccounts();

    // Record the sender transaction
    Transaction sent;
    sent.accountNo = from;
    sent.type = "Transfer Sent";
    sent.amount = amount;
    sent.relatedAccount = to;
    sent.dateTime = getCurrentDateTime();
    saveTransaction(sent);

    // Record the receiver transaction
    Transaction received;
    received.accountNo = to;
    received.type = "Transfer Received";
    received.amount = amount;
    received.relatedAccount = from;
    received.dateTime = getCurrentDateTime();
    saveTransaction(received);

    cout << "\nFund transfer successful.\n";
}

// Display the latest five transactions
void showMiniStatement() {
    int no;

    cout << "\nEnter Account Number: ";
    cin >> no;

    if (!accountExists(no)) {
        cout << "Account not found.\n";
        return;
    }

    ifstream file("transactions.txt");
    string line;
    int count = 0;

    cout << "\n========== MINI STATEMENT ==========\n";

    while (getline(file, line)) {
        size_t p1 = line.find('|');
        size_t p2 = line.find('|', p1 + 1);
        size_t p3 = line.find('|', p2 + 1);
        size_t p4 = line.find('|', p3 + 1);

        if (p1 == string::npos || p4 == string::npos)
            continue;

        int accountNo = stoi(line.substr(0, p1));

        if (accountNo == no) {
            cout << line.substr(p1 + 1, p2 - p1 - 1)
                 << " | Amount: " << line.substr(p2 + 1, p3 - p2 - 1)
                 << " | " << line.substr(p4 + 1) << "\n";

            count++;

            if (count == 5)
                break;
        }
    }

    if (count == 0)
        cout << "No transaction found.\n";

    file.close();
}

// Display complete transaction history
void showTransactionHistory() {
    int no;

    cout << "\nEnter Account Number: ";
    cin >> no;

    if (!accountExists(no)) {
        cout << "Account not found.\n";
        return;
    }

    ifstream file("transactions.txt");
    string line;
    bool found = false;

    cout << "\n========== TRANSACTION HISTORY ==========\n";

    while (getline(file, line)) {
        size_t p1 = line.find('|');
        size_t p2 = line.find('|', p1 + 1);
        size_t p3 = line.find('|', p2 + 1);
        size_t p4 = line.find('|', p3 + 1);

        if (p1 == string::npos || p4 == string::npos)
            continue;

        int accountNo = stoi(line.substr(0, p1));

        if (accountNo == no) {
            found = true;

            cout << "Type: " << line.substr(p1 + 1, p2 - p1 - 1)
                 << " | Amount: " << line.substr(p2 + 1, p3 - p2 - 1)
                 << " | Related Account: " << line.substr(p3 + 1, p4 - p3 - 1)
                 << " | Date: " << line.substr(p4 + 1) << "\n";
        }
    }

    if (!found)
        cout << "No transaction found.\n";

    file.close();
}

