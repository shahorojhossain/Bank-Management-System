#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
using namespace std;

// Store one transaction record
struct Transaction {
    int accountNo;
    string type;
    double amount;
    int relatedAccount;
    string dateTime;
};

// Banking operations
void deposit();
void withdraw();
void transferMoney();

// Statement and history
void showMiniStatement();
void showTransactionHistory();

// Transaction file handling
void saveTransaction(const Transaction& t);

// Utility function
string getCurrentDateTime();

#endif

