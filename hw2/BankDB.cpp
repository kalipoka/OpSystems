//
// Created by alexey on 30-Nov-17.
//


#include "BankDB.h"

BankDB::BankDB() {

    _bankBalance = 0;
    _numberOfAccounts = 0;

    _accountsList = new std::list<Account>;


}

BankDB::~BankDB() {
    delete _accountsList;
}


bool CompareFunction (Account Acc1,Account Acc2 ) { return (Acc1.GetAccountNumber() <Acc2.GetAccountNumber()); }


void BankDB::AddAccount(Account newAccount) {

    _accountsList->push_front(newAccount);
    _numberOfAccounts++;
}

void BankDB::PrintAccounts() {

 //   std::list<Account>* TempAccList = _accountsList;

// sorting the list before printing according to the account number

    if (_numberOfAccounts > 1)  // sort only if more than 1 element
        _accountsList->sort(CompareFunction);

    //std::sort(TempAccList->begin(),TempAccList->end(),CompareFunction);
    /*
    for (auto i  = TempAccList->begin(); i !=TempAccList->end(); ++i){

        std::cout << i->GetAccountNumber() << "\t" << i->GetPassword() << "\t" << i->CheckBalance()  << "\t" << i->CheckIsVIP()  << std::endl;
    } */

    for (auto i  = _accountsList->begin(); i !=_accountsList->end(); ++i){

        std::cout << i->GetAccountNumber() << "\t" << i->GetPassword() << "\t" << i->CheckBalance()  << "\t" << i->CheckIsVIP()  << std::endl;
    }

}

Account* BankDB::FindAccountByNumber(int accountNumber ){

    for (auto i  = _accountsList->begin(); i !=_accountsList->end(); ++i){
         if  (i->GetAccountNumber() == accountNumber)
             return &*i;
    }
    if (DEBUG) std::cout << "Account not found in the list" << std::endl;
    return NULL; // if account not found

}




