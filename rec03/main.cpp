//
//  main.cpp
//  rec03
//
//  Created by Elias Attias on 2/14/20.
//  Copyright © 2020 Elias Attias. All rights reserved.
//

//Provided
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

//
// Task 1: The Account struct. Call it AccountS
//
struct AccountS{
    string name;
    int number;
};

void readFile(ifstream& accounts, vector<AccountS>& vectorOfAccountsS){
    if (!accounts){
        cerr << "could not open the file";
        exit(1);
    }
    string aName;
    int aNumber;
    while(accounts >> aName){ //skip whitespace
        accounts >> aNumber;
        AccountS account;
        account.name = aName;
        account.number = aNumber;
        vectorOfAccountsS.push_back(account);
    }
}

void display(vector<AccountS>& vectorOfAccountsS){
    for (size_t i = 0; i < vectorOfAccountsS.size(); i ++){
        cout << vectorOfAccountsS[i].name << "  " << vectorOfAccountsS[i].number << endl;
    }
}

void readFile2(ifstream& accounts, vector<AccountS>& vectorOfAccountsS){
    if (!accounts){
        cerr << "could not open the file";
        exit(1);
    }
    string aName;
    int aNumber;
    while(accounts >> aName){
        accounts >> aNumber;
        AccountS account{aName,aNumber};
        vectorOfAccountsS.push_back(account);
    }
}

void display2(vector<AccountS>& vectorOfAccountsS){
    for (size_t i = 0; i < vectorOfAccountsS.size(); i ++){
        cout << vectorOfAccountsS[i].name << "  " << vectorOfAccountsS[i].number << endl;
    }
}

//
// Task 3
//
// Transaction class definition

//
// Task 3
//
// Transaction class definition
class Transaction{

public:
    Transaction(const string& aAction, int aAmount) : action(aAction), amount(aAmount){}
    
    string getAction() const{
        return action;
    }
    
    int getAmount() const{
        return amount;
    }
private:
    string action;
    int amount;
};

// Account class definition
class Account3{
public:
    Account3(const string& Aname, int Anumber, int Abalance) : name(Aname), number(Anumber), balance(Abalance), vectorOfTransaction(){}
    
    string getName() const{
        return name;
    }
    int getNumber() const{
        return number;
    }
    
    vector<Transaction> getTransactions() const{
        return vectorOfTransaction;
    }
    
    void deposit(int quantity) {
        Transaction transaction("deposit", quantity);
        vectorOfTransaction.push_back(transaction);
        balance += quantity;
    }
    
    void withdraw(int quantity){
        Transaction transaction("withdraw", quantity);
        vectorOfTransaction.push_back(transaction);
        if (quantity > balance){
            cerr << "you have withdrawn money you don't have" << endl;
        }
        else{
            balance -= quantity;
        }
    }
    
    friend ostream& operator << (ostream& os, const Account3& acc){
        os << acc.name << " " << acc.number << endl;
        for (size_t i = 0; i < acc.vectorOfTransaction.size(); i ++){
            os << acc.vectorOfTransaction[i].getAction() << " " << acc.vectorOfTransaction[i].getAmount() << endl;
        }
        return os;
    }
    
private:
    string name;
    int number;
    int balance;
    vector<Transaction> vectorOfTransaction;
};

size_t findAccount(const vector<Account3>& vectorOfAccount3C, int theNumber){
    for (size_t i = 0; i < vectorOfAccount3C.size(); i ++){
        if (vectorOfAccount3C[i].getNumber() == theNumber){
            return i;
        }
    }
    return vectorOfAccount3C.size();
}

void display2d(vector<Account3>& vectorOfAccounts){
    for (const Account3& acc : vectorOfAccounts){
        cout << acc;
    }
}

void readFile2d(ifstream& transactions, vector<Account3>& vectorOfAccounts3C){
    if (!transactions){
        cerr << "could not open the file" << endl;
        exit(1);
    }
    string firstWord;
    string theName;
    int theNumber;
    int quantity;
    while(transactions >> firstWord){
        if (firstWord == "Account"){
            transactions >> theName >> theNumber;
            Account3 account(theName, theNumber, 0);
            vectorOfAccounts3C.push_back(account);
        }
        else if (firstWord == "Deposit"){
            transactions >> theNumber >> quantity;
            size_t location = findAccount(vectorOfAccounts3C,theNumber);
            vectorOfAccounts3C[location].deposit(quantity);
        }
        else if(firstWord == "Withdraw"){
            transactions >> theNumber >> quantity;
            size_t location = findAccount(vectorOfAccounts3C,theNumber);
            vectorOfAccounts3C[location].withdraw(quantity);
        }
    }
}


//
// Task 4
//
// Transaction class definition with embedded Account class
//class Account3{
//    class Transaction{
//
//    public:
//        Transaction(const string& aAction, int aAmount) : action(aAction), amount(aAmount){}
//
//        string getAction() const{
//            return action;
//        }
//
//        int getAmount() const{
//            return amount;
//        }
//    private:
//        string action;
//        int amount;
//    };
//
//public:
//    Account3(const string& Aname, int Anumber, int Abalance) : name(Aname), number(Anumber), balance(Abalance), vectorOfTransaction(){}
//
//    string getName() const{
//        return name;
//    }
//    int getNumber() const{
//        return number;
//    }
//
//    vector<Transaction> getTransactions() const{
//        return vectorOfTransaction;
//    }
//
//    void deposit(int quantity) {
//        Transaction transaction("deposit", quantity);
//        vectorOfTransaction.push_back(transaction);
//        balance += quantity;
//    }
//
//    void withdraw(int quantity){
//        Transaction transaction("withdraw", quantity);
//        vectorOfTransaction.push_back(transaction);
//        if (quantity > balance){
//            cerr << "you have withdrawn money you don't have" << endl;
//        }
//        else{
//            balance -= quantity;
//        }
//    }
//
//    friend ostream& operator << (ostream& os, const Account3& acc){
//        os << acc.name << " " << acc.number << endl;
//        for (size_t i = 0; i < acc.vectorOfTransaction.size(); i ++){
//            os << acc.vectorOfTransaction[i].getAction() << " " << acc.vectorOfTransaction[i].getAmount() << endl;
//        }
//        return os;
//    }
//
//private:
//    string name;
//    int number;
//    int balance;
//    vector<Transaction> vectorOfTransaction;
//};
//
//size_t findAccount(const vector<Account3>& vectorOfAccount3C, int theNumber){
//    for (size_t i = 0; i < vectorOfAccount3C.size(); i ++){
//        if (vectorOfAccount3C[i].getNumber() == theNumber){
//            return i;
//        }
//    }
//    return vectorOfAccount3C.size();
//}
//
//void display2d(vector<Account3>& vectorOfAccounts){
//    for (const Account3& acc : vectorOfAccounts){
//        cout << acc;
//    }
//}
//
//void readFile2d(ifstream& transactions, vector<Account3>& vectorOfAccounts3C){
//    if (!transactions){
//        cerr << "could not open the file" << endl;
//        exit(1);
//    }
//    string firstWord;
//    string theName;
//    int theNumber;
//    int quantity;
//    while(transactions >> firstWord){
//        if (firstWord == "Account"){
//            transactions >> theName >> theNumber;
//            Account3 account(theName, theNumber, 0);
//            vectorOfAccounts3C.push_back(account);
//        }
//        else if (firstWord == "Deposit"){
//            transactions >> theNumber >> quantity;
//            size_t location = findAccount(vectorOfAccounts3C,theNumber);
//            vectorOfAccounts3C[location].deposit(quantity);
//        }
//        else if(firstWord == "Withdraw"){
//            transactions >> theNumber >> quantity;
//            size_t location = findAccount(vectorOfAccounts3C,theNumber);
//            vectorOfAccounts3C[location].withdraw(quantity);
//        }
//    }
//}


//
// Task 2: The Account class. Call it AccountC
//
class AccountC{
public:
    AccountC(const string& Aname, int Anumber) : name(Aname), number(Anumber){}

//    string getName() const{
//        return name;
//    }
//    int getNumber() const{
//        return number;
//    }
    
// 2.2: AccountC output operator, reimplemented as a friend.
     friend ostream& operator << (ostream& os, const AccountC& acc);
private:
    string name;
    int number;
};

void readFile2a(ifstream& accounts, vector<AccountC>& vectorOfAccountsC){
    if (!accounts){
        cerr << "could not open the file" << endl;
        exit(1);
    }
    string aName;
    int aNumber;
    while(accounts >> aName){
        accounts >> aNumber;
        AccountC account(aName,aNumber);
        vectorOfAccountsC.push_back(account);
    }
}

// 2.b: AccountC output operator, not a friend.
ostream& operator <<(ostream& os, const AccountC& accC){
//    os << accC.getName() << " " << accC.getNumber() << endl;
    os << accC.name << " " << accC.number << endl;
    return os;
}

void display2a(vector<AccountC>& vectorOfAccountsC){
    for (AccountC& acc : vectorOfAccountsC){
        cout << acc;
    }
}

void readFile2b(ifstream& accounts, vector<AccountC>& vectorOfAccountsC){
    if (!accounts){
        cerr << "could not open the file" << endl;
        exit(1);
    }
    string aName;
    int aNumber;
    while(accounts >> aName){
        accounts >> aNumber;
        vectorOfAccountsC.push_back(AccountC(aName, aNumber));
    }
}

void readFile2c(ifstream& accounts, vector<AccountC>& vectorOfAccountsC){
    if (!accounts){
        cerr << "could not open the file" << endl;
        exit(1);
    }
    string aName;
    int aNumber;
    while(accounts >> aName){
        accounts >> aNumber;
        vectorOfAccountsC.emplace_back(aName, aNumber);
    }
}

int main(){
    //
    // Task 1: account as struct
    //
    //      1a. Fill vector of account structs from file

    cout << "Task1a:\n";
    cout << "Filling vector of struct objects, define a local struct instance "
         << " and set fields explicitly:\n";
    ifstream accounts("accounts.txt");
    vector<AccountS> vectorOfAccountsS;
    readFile(accounts, vectorOfAccountsS);
    accounts.close();
    display(vectorOfAccountsS);
    vectorOfAccountsS.clear();

    //      1b
    cout << "Task1b:\n";
    cout << "Filling vector of struct objects, using {} initialization:\n";
    accounts.open("accounts.txt");
    readFile2(accounts, vectorOfAccountsS);
    accounts.close();
    display2(vectorOfAccountsS);
    vectorOfAccountsS.clear();
    //==================================
    //
    // Task 2: account as class
    //
    //      2a
    cout << "==============\n";
    cout << "\nTask2a:";
    cout << "\nFilling vector of class objects, using local class object:\n";
    
    accounts.open("accounts.txt");
    vector<AccountC> vectorOfAccountsC;
    readFile2a(accounts, vectorOfAccountsC);
    accounts.close();

    cout << "---\n";
    cout << "\nTask2b:\n";
    cout << "output using output operator with getters\n";
//    This is in comments
//    display2a(vectorOfAccountsC);
    
    cout << "\nTask2c:\n";
    cout << "output using output operator as friend without getters\n";
    
    display2a(vectorOfAccountsC);
    vectorOfAccountsC.clear();
    accounts.close();
    
    cout << "\nTask2d:\n";
    cout << "Filling vector of class objects, using temporary class object:\n";
    
    accounts.open("accounts.txt");
    readFile2b(accounts, vectorOfAccountsC);
    display2a(vectorOfAccountsC);
    vectorOfAccountsC.clear();
    accounts.close();
    
    cout << "\nTask2e:\n";
    cout << "\nFilling vector of class objects, using emplace_back:\n";
    
    accounts.open("accounts.txt");
    readFile2c(accounts, vectorOfAccountsC);
    display2a(vectorOfAccountsC);
    vectorOfAccountsC.clear();
    accounts.close();
    
    // Task 3
    cout << "==============\n";
    cout << "\nTask 3:\n\nAccounts and Transaction:\n";
    
    ifstream transactions("transaction.txt");
    transactions.open("transaction.txt");
    vector<Account3> vectorOfAccounts3C;
    readFile2d(transactions, vectorOfAccounts3C);
    display2d(vectorOfAccounts3C);
    
    // Task 4
    cout << "==============\n";
    cout << "\nTask 4:\n\nAccounts and Transaction:\n"
         << "Account class is nested inside Transaction class.\n";

}

