//
// Created by alexey on 30-Nov-17.
//
#ifndef HW2_BANK_H
#define HW2_BANK_H


#include <iostream>
#include <list>
#include <string>
#include <thread>
#include <algorithm>
#include "Account.h"
#include "ATM.h"

#define DEBUG 1

class BankDB {

public:

    BankDB(int numberOfATMs);
    ~BankDB();

    void AddAccount (Account newAccount);

    Account* FindAccountByNumber(int accountNumber );

    void ChargeInterest();   //Should be as a thread

    void PrintAccounts();   // also should be as a thread?


private:

    int _bankBalance;
    int _numberOfATMs;
    int _numberOfAccounts;

    std::list<Account>* _accountsList;
    std::list<ATM>* _cashiersList;
};


#endif //HW2_BANK_H
