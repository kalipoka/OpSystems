//
// Created by alexey on 30-Nov-17.
//
#ifndef HW2_BANK_H
#define HW2_BANK_H

//#include <threads.h>
//#include "threads.h"

#include <iostream>
#include <list>
#include <string>
#include <thread>
#include "Account.h"
#include "Cashier.h"

class Bank {

public:
    Bank(int numberOfATMs);
    ~Bank();

    void AddAccount (Account newAccount);
    void ChargeInterest();

    void PrintAccounts();


private:

    int _bankBalance;
    int _numberOfCashiers;

    std::list<Account>* _accountsList;
    std::list<Cashier>* _cashiersList;
};








#endif //HW2_BANK_H
