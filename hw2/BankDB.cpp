//
// Created by alexey on 30-Nov-17.
//


#include <unistd.h>
#include "BankDB.h"

BankDB::BankDB() {

    _isOpen = true;
    _bankBalance = 0;
    _numberOfAccounts = 0;
    _accountsList = new std::list<Account>;
    if (pthread_mutex_init(&bankDBLock,NULL)){
        perror("BankDB Lock init fail");
        exit(1);
    }
}

BankDB::~BankDB() {

    //delete _accountsList;
    if (pthread_mutex_destroy(&bankDBLock)){
        perror("BankDB Lock destroy fail");
        exit(1);
    }
}


bool CompareFunction (Account Acc1,Account Acc2 ) { return (Acc1.GetAccountNumber() <Acc2.GetAccountNumber()); }

int BankDB::GetBankBalance(){
    return _bankBalance;
}

/*
  if (pthread_mutex_lock(&bankDBLock)) {
        perror("Lock Failed");
        exit(1);

            if (pthread_mutex_unlock(&bankDBLock)) {
        perror("Unlock Failed");
        exit(1);
    }
    }
 */

void BankDB::AddAccount(Account newAccount, int ATM_num) {
    std::stringstream ss;



    Account* temp = this->FindAccountByNumber(newAccount.GetAccountNumber());
    if (temp == NULL) // we do not have acconts like this
    {
        _accountsList->push_front(newAccount);
        _numberOfAccounts++;
        if (DEBUG) std::cout << ATM_num << ": New account id is "<< newAccount.GetAccountNumber()<<" with password "<< newAccount.GetPassword()<< " and initial balance "<< newAccount.CheckBalance() << std::endl;

        ss << ATM_num << ": New account id is "<< newAccount.GetAccountNumber()<<" with password "<< newAccount.GetPassword()<< " and initial balance "<< newAccount.CheckBalance()<<'\n';
        logF.WriteLogLine(ss.str());
    } else{
        if (DEBUG) std::cout << "Error " << ATM_num << ": Your transaction failed – account with the same id exists"<< std::endl;
        ss << "Error " << ATM_num << ": Your transaction failed – account with the same id exists\n";
        logF.WriteLogLine(ss.str());
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

void BankDB::PrintAccounts() {

// sorting the list before printing according to the account number

 while(_isOpen)
 {
    usleep(500000);
     printf("\033[2J");
     printf("\033[1;1H");
     cout << "Current Bank Status" << endl;
     if (_numberOfAccounts > 1)  // sort only if more than 1 element
         _accountsList->sort(CompareFunction);

     for (auto i  = _accountsList->begin(); i !=_accountsList->end(); ++i){

         std::cout <<"Account " << i->GetAccountNumber() << ": Balance - " << i->CheckBalance() << " $ , Account Password - " << i->GetPassword()  << std::endl;
     }
     cout << "The Bank has " << _bankBalance << " $" << endl;
 }

}


void BankDB::ChargeFee() {

    while (_isOpen)
    {
        usleep(3000000);
        int fee = 2 + rand() % 3;
        int gain = 0;
        //std::stringstream ss_fee;
        std::cout << "Entered Bank Charge Fee" << std::endl;

        for (auto i  = _accountsList->begin(); i !=_accountsList->end(); ++i){
            std::stringstream ss_fee;

            if (!i->CheckIsVIP()) // charge only the non VIP
            {
                gain = i->GiveInterest(fee);
                _bankBalance = _bankBalance + gain;
                ss_fee <<"Bank: commissions of " << fee <<" % were charged, the bank gained " << gain << " $ from account " << i->GetAccountNumber() << std::endl;
                logF.WriteLogLine(ss_fee.str());
            }
        }
    }

    std::cout << "Exit Bank Charge Fee" << std::endl;

}

void BankDB::close() {
    _isOpen = false;
}

