#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <vector>
using namespace std;

// Store basic information of a bank account
struct Account {
    int accountNo;
    string name;
    string phone;
    string address;
    string pin;
    double balance;
};

extern vector<Account> accounts;

// Account CRUD functions
void createAccount();
void viewAccount();
void updateAccount();
void deleteAccount();
void viewAllAccounts();

// Account helper functions
int findAccountIndex(int accountNo);
bool accountExists(int accountNo);
int getNextAccountNo();

// File handling for accounts
void loadAccounts();
void saveAccounts();

#endif

