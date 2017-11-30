//
// Created by alexey on 30-Nov-17.
//

#include <iostream>
#include "Account.h"

using std::cout;

/*************************************
* Constructor of the Account
*
**************************************/
Account::Account(int accountNumber, int password, int balance) {

    _accountNumber = accountNumber;
    _password = password;
    _balance = balance;

}

Account::~Account() {
    // nothing to destroy or free
}

int Account::GetAccountNumber() {
    return _accountNumber;
}

int Account::CheckBalance() {
    return _balance;
}

bool Account::ComparePassword(int passwordToCheck) {

    return (_password == passwordToCheck);
}


bool Account::CheckIsVIP() {
    return _isVIP;

}

void Account::BecomeVip() {
    _isVIP = true;
}

