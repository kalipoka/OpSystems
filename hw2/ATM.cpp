//
// Created by alexey on 30-Nov-17.
//

#include "ATM.h"
#include <iostream>
#include "Account.h"
#include "BankDB.h"

#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#define DEBUG 1

using namespace std;

int stringToInt(const string s) {
    istringstream istr(s);
    int i = 0;
    istr >> i;
    return i;
}

vector<string> tokenize(string line, const char* delim) {
    unsigned int i, j;
    vector<string> tokens;
    while (!line.empty()) {
        i = line.find_first_not_of(delim);
        j = line.find_first_of(delim, i+1);
        tokens.push_back(line.substr(i, j-i));
        if (j > line.size()-1)
            line = "";
        else
            line = line.substr(j+1,line.size()-j-1);
    }
    return tokens;
}



ATM::ATM(int serialNumber, BankDB *DB) {

    _serialNumber = serialNumber;
    _BankDB = DB;
}

ATM::~ATM() {

}

void ATM::ReadCommandsFromFile(string path) {
    if (DEBUG) std::cout << "Got Into Read Commands From File" << std::endl;
    string line;
    //std::ifstream inFile (path,std::ifstream::in);
    ifstream inFile(path.c_str());

    if (!inFile.is_open())
    {
        std::cout << "Cannot Open File Opened" << std::endl;

    } else {  // opens well

        while(( getline (inFile,line) )){
            std::cout << "This is what I will execute" << std::endl;
            if(DEBUG)  std::cout << line << std::endl;
            this->ExecuteCommand(line);
        }
    }
    inFile.close();
}

void ATM::ExecuteCommand(string command) {

    if (DEBUG) std::cout << "Got Into Execute Commands" << std::endl;

    const char* delims = " \t\n";
    vector<string> tokens;
    string line;
    tokens = tokenize(command, delims);


    if (tokens.size() == 0) {
        std::cout << "Empty Command" << std::endl;
    }

    // Open Account
    if (tokens[0] == "O") {
        //Create Account - asuming legal input
        Account newAccount = Account(stringToInt(tokens[1]),stringToInt(tokens[2]),stringToInt(tokens[3]));
        // need to open / insert threads here
        _BankDB->AddAccount( newAccount);
        // need to close thread here
        if(DEBUG)  std::cout << "Adding account and printing" << std::endl;
        if(DEBUG) _BankDB->PrintAccounts();
    }

    // Make an Account a VIP
    if (tokens[0] == "L"){
        Account* tempAccount = _BankDB->FindAccountByNumber(stringToInt(tokens[1]));
        if (tempAccount!= NULL)  // found such an account
        {
            if (tempAccount->ComparePassword(stringToInt(tokens[2])))
            {
                if(DEBUG)  std::cout << "Adding account and printing BEFORE" << std::endl;
                if(DEBUG) _BankDB->PrintAccounts();
                // need to open / insert threads here
                tempAccount->BecomeVip();
                // need to close thread here
                if(DEBUG)  std::cout << "Adding account and printing AFTER" << std::endl;
                if(DEBUG) _BankDB->PrintAccounts();
            }
                // password incorrect
            else {
                std::cout << "Error <ATM ID>: Your transaction failed – password for account id <id> is incorrect" << std::endl;
            }

        }
            // Account number not found
        else
        {
            std::cout << "Error <ATM ID>: Your transaction failed – account id <id> does not exist" << std::endl;
        }
    }

    // Make A Deposit to ourselves
    if (tokens[0] == "D") {
        Account *tempAccount = _BankDB->FindAccountByNumber(stringToInt(tokens[1]));
        if (tempAccount != NULL)  // found such an account
        {
            if (tempAccount->ComparePassword(stringToInt(tokens[2])))  // correct password
            {
                if (DEBUG) std::cout << "Adding Diposit  and printing BEFORE" << std::endl;
                if (DEBUG) _BankDB->PrintAccounts();
                tempAccount->Deposit(stringToInt(tokens[3]));
                std::cout << "<ATM ID>: Account <id> new balance is <bal> after <amount> $ was deposited"
                          << std::endl;   //succes
                if (DEBUG) std::cout << "Adding Diposit  and printing AFTER" << std::endl;
                if (DEBUG) _BankDB->PrintAccounts();
            } else {
                std::cout << "Error <ATM ID>: Your transaction failed – password for account id <id> is incorrect"
                          << std::endl;  // wrong password
            }
        } else{   // Account not found
            std::cout << "Error <ATM ID>: Your transaction failed – account id <id> does not exist" << std::endl;
        }
    }

    // Make A withdrawal to ourselves
    if (tokens[0] == "W") {
        Account *tempAccount =_BankDB->FindAccountByNumber(stringToInt(tokens[1]));
        if (tempAccount != NULL)  // found such an account
        {
            if (tempAccount->ComparePassword(stringToInt(tokens[2])))  // correct password
            {
                if (DEBUG) std::cout << "Making withdrawal  and printing BEFORE" << std::endl;
                if (DEBUG) _BankDB->PrintAccounts();

                if(!tempAccount->Withdrawal(stringToInt(tokens[3]))) // if return value is 0 - we succeded
                {
                    std::cout << "<ATM ID>: Account <id> new balance is <bal> after <amount> $ was withdrew"  << std::endl;   //succes
                    if (DEBUG) std::cout << "Making withdrawal  and printing AFTER" << std::endl;
                    if (DEBUG) _BankDB->PrintAccounts();
                } else{
                    std::cout << "Error <ATM ID>: Your transaction failed – account id <id> balance is lower than <amount>"<< std::endl;
                }

            } else {   // wrong password
                std::cout << "Error <ATM ID>: Your transaction failed – password for account id <id> is incorrect"
                          << std::endl;  // wrong password
            }
        } else{
            std::cout << "Error <ATM ID>: Your transaction failed – account id <id> does not exist" << std::endl;
        }
    }

    // Check the Balance
    if (tokens[0] == "B"){
        Account* tempAccount = _BankDB->FindAccountByNumber(stringToInt(tokens[1]));
        if (tempAccount!= NULL)  // found such an account
        {
            if (tempAccount->ComparePassword(stringToInt(tokens[2])))  // password correct
            {
                if(DEBUG)  std::cout << "Checking Balance and printing BEFORE" << std::endl;
                // need to open / insert threads here
                int currentBalance = tempAccount->CheckBalance();
                // need to close thread here
                std::cout << "<ATM ID>" << "Account " << tokens[1] << "balace is" << currentBalance <<std::endl;
            }

            else { // password incorrect
                std::cout << "Error <ATM ID>: Your transaction failed – password for account id <id> is incorrect" << std::endl;
            }
        }
        else   // Account number not found
        {
            std::cout << "Error <ATM ID>: Your transaction failed – account id <id> does not exist" << std::endl;
        }
    }

    //Conduct a Transaction
    if (tokens[0] == "T"){

        Account* tempAccount = _BankDB->FindAccountByNumber(stringToInt(tokens[1]));
        Account* accountToTransasct = _BankDB->FindAccountByNumber(stringToInt(tokens[3]));  //looking for the new account to transact

        if (tempAccount!= NULL && accountToTransasct!=NULL )  // found such an account
        {
            if (tempAccount->ComparePassword(stringToInt(tokens[2])))  // password correct
            {
                if(DEBUG)  std::cout << "Preparing to Make Transaction" << std::endl;
                // need to open / insert threads here
                if (tempAccount->CheckBalance() < stringToInt(tokens[4]) )
                {
                    std::cout << "Error <ATM ID>: Your transaction failed – account id <id> balance is lower than <amount>" <<std::endl;
                } else{
                    if(DEBUG)  std::cout << "Making Transaction and printing BEFORE" << std::endl;
                    _BankDB->PrintAccounts();
                    tempAccount->Withdrawal(stringToInt(tokens[4]));
                    accountToTransasct->Deposit(stringToInt(tokens[4]));
                    std::cout << "<ATM ID>: Transfer <amount> from account <account> to account <target_account> new account\n"
                            "balance is <account_bal> new target account balance is <target_bal>" << std::endl;
                    if(DEBUG)  std::cout << "Making Transaction and printing AFTER" << std::endl;
                    _BankDB->PrintAccounts();
                }
                // need to close thread here??
            }

            else { // password incorrect
                std::cout << "Error <ATM ID>: Your transaction failed – password for account id <id> is incorrect" << std::endl;
            }
        }
        else   // Account number not found
        {
            std::cout << "Error <ATM ID>: Your transaction failed – account id <id> does not exist" << std::endl;
        }
    }

}