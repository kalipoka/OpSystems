//
// Created by alexey on 30-Nov-17.
//
#ifndef HW2_BANK_H
#define HW2_BANK_H

#include <sstream>
#include <iostream>
#include <list>
#include <string>
#include <thread>
#include <algorithm>
#include "Account.h"
#include "ATM.h"
#include "WriteToLog.h"

extern WriteToLog logF;

class BankDB {

public:

    BankDB();
    ~BankDB();

    void AddAccount (Account newAccount, int ATM_num);

    Account* FindAccountByNumber(int accountNumber );

    void ChargeInterest();   //Should be as a thread


    void PrintAccounts();   // also should be as a thread?
    int GetBankBalance();




private:

    int _bankBalance;
    int _numberOfAccounts;
    std::list<Account>* _accountsList;
};

bool CompareFunction (Account Acc1,Account Acc2 );


#endif //HW2_BANK_H
