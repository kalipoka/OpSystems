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
    _isVIP = false;  // be default accounts created not VIP

}

Account::~Account() {
    // nothing to destroy or free
}

int Account::GetAccountNumber() {
    return _accountNumber;
}

int Account::GetPassword() {
    return _password;
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

void Account::Deposit(int dipositAmmount) {

    _balance = _balance + dipositAmmount;
}

int Account::Withdrawal(int withdrawalAmmount) {

    if (withdrawalAmmount > _balance)
        return 1;
    else
    {
        _balance = _balance - withdrawalAmmount;
        return 0;  // withdrawal succesfull
    }

}