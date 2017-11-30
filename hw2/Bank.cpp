//
// Created by alexey on 30-Nov-17.
//


#include "Bank.h"

Bank::Bank(int numberOfATMs) {

    _numberOfCashiers = numberOfATMs;
    _bankBalance = 0;

    _accountsList = new std::list<Account>;
    _cashiersList = new std::list<Cashier>;

}

Bank::~Bank() {
    delete _accountsList;
    delete _cashiersList;
}


void Bank::AddAccount(Account newAccount) {

    _accountsList->push_front(newAccount);
}

void Bank::PrintAccounts() {

    for (auto i  = _accountsList->begin(); i !=_accountsList->end(); ++i){
        std::cout << i->GetAccountNumber() << std::endl;
    }

}
