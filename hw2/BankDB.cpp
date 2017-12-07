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
    //delete _accountsList;
}


bool CompareFunction (Account Acc1,Account Acc2 ) { return (Acc1.GetAccountNumber() <Acc2.GetAccountNumber()); }

int BankDB::GetBankBalance(){
    return _bankBalance;
}

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

void BankDB::PrintAccounts() {

// sorting the list before printing according to the account number

    if (_numberOfAccounts > 1)  // sort only if more than 1 element
        _accountsList->sort(CompareFunction);

    for (auto i  = _accountsList->begin(); i !=_accountsList->end(); ++i){

        std::cout <<"Account " << i->GetAccountNumber() << ": Balance - " << i->CheckBalance() << " $ , Account Password - " << i->GetPassword()  << std::endl;
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

void BankDB::ChargeFee() {
    int low = 2;
    int high = 4;
    int gain = 0;
    std::stringstream ss;

    float fee = low + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(high-low)));

    for (auto i  = _accountsList->begin(); i !=_accountsList->end(); ++i){
        if (!i->CheckIsVIP()) // charge only the non VIP
        {
            gain = i->GiveInterest(fee);
            _bankBalance = _bankBalance + gain;
            ss <<"Bank: commissions of " << fee <<" % were charged, the bank gained " << gain << " $ from account " << i->GetAccountNumber() << std::endl;
            logF.WriteLogLine(ss.str());
        }

    }

}



