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

#include "WriteToLog.h"

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
        std::cout << "Cannot Open File" << std::endl;

    } else {  // opens well

        while(( getline (inFile,line) )){
            if(DEBUG) std::cout << "This is what I will execute" << std::endl;
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
    std::stringstream ss;

    if (tokens.size() == 0) {
        std::cout << "Empty Command" << std::endl;
    }

    // Open Account
    if (tokens[0] == "O") {
        //Create Account - asuming legal input
        Account newAccount = Account(stringToInt(tokens[1]),stringToInt(tokens[2]),stringToInt(tokens[3]));
        // need to open / insert threads here
        _BankDB->AddAccount( newAccount,this->_serialNumber);
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
                if (DEBUG) std::cout << "Error " << this->_serialNumber << ": Your transaction failed – password for account id "<< tokens[1] <<" is incorrect" << std::endl;
                ss << "Error " << this->_serialNumber << ": Your transaction failed – password for account id "<< tokens[1] <<" is incorrect\n";
            }

        }
            // Account number not found
        else
        {
            if (DEBUG)std::cout << "Error " << this->_serialNumber <<": Your transaction failed – account id "<< tokens[1] <<" does not exist" << std::endl;
            ss << "Error " << this->_serialNumber <<": Your transaction failed – account id "<< tokens[1] <<" does not exist\n";
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
                int balance = tempAccount->CheckBalance();
                if (DEBUG) std::cout << this->_serialNumber <<": Account "<< tokens[1] <<" new balance is "<< tempAccount->CheckBalance() << " after " <<  tokens[3] <<" $ was deposited" << std::endl;
                ss << this->_serialNumber <<": Account "<< tokens[1] <<" new balance is "<< tempAccount->CheckBalance() << " after " <<  tokens[3] <<" $ was deposited\n";
                if (DEBUG) std::cout << "Adding Diposit  and printing AFTER" << std::endl;
                if (DEBUG) _BankDB->PrintAccounts();
            } else {
                if (DEBUG)std::cout << "Error " << this->_serialNumber << ": Your transaction failed – password for account id "<< tokens[1] <<" is incorrect" << std::endl;  // wrong password
                ss << "Error " << this->_serialNumber << ": Your transaction failed – password for account id "<< tokens[1] <<" is incorrect\n";
            }
        } else{   // Account not found
            if (DEBUG)std::cout << "Error " << this->_serialNumber <<": Your transaction failed – account id "<< tokens[1] <<" does not exist" << std::endl;
            ss << "Error " << this->_serialNumber <<": Your transaction failed – account id "<< tokens[1] <<" does not exist\n";
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
                    if (DEBUG) std::cout << this->_serialNumber<< ": Account " << tempAccount->GetAccountNumber() << " new balance is "<< tempAccount->CheckBalance() <<" after " << tokens[3] <<" $ was withdrew"  << std::endl;   //succes
                    ss << this->_serialNumber<< ": Account " << tempAccount->GetAccountNumber() << " new balance is "<< tempAccount->CheckBalance() <<" after " << tokens[3] <<" $ was withdrew"  << std::endl;
                    if (DEBUG) std::cout << "Making withdrawal  and printing AFTER" << std::endl;
                    if (DEBUG) _BankDB->PrintAccounts();
                } else{
                    if (DEBUG) std::cout << "Error " << this->_serialNumber <<": Your transaction failed – account id " << tempAccount->GetAccountNumber() <<" balance is lower than " <<  tokens[3] << std::endl;
                    ss << "Error " << this->_serialNumber <<": Your transaction failed – account id " << tempAccount->GetAccountNumber() <<" balance is lower than " <<  tokens[3] <<'\n';
                }

            } else {   // wrong password
                if (DEBUG)std::cout << "Error " << this->_serialNumber << ": Your transaction failed – password for account id "<< tokens[1] <<" is incorrect" << std::endl;
                ss << "Error " << this->_serialNumber << ": Your transaction failed – password for account id "<< tokens[1] <<" is incorrect\n";
            }
        } else{
            if (DEBUG)std::cout << "Error " << this->_serialNumber <<": Your transaction failed – account id "<< tokens[1] <<" does not exist" << std::endl;
            ss << "Error " << this->_serialNumber <<": Your transaction failed – account id "<< tokens[1] <<" does not exist\n";
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
                if (DEBUG)std::cout << this->_serialNumber << ": Account " << tokens[1] << " balance is " << currentBalance <<std::endl;
                ss << this->_serialNumber << ": Account " << tokens[1] << " balance is " << currentBalance <<'\n';
            }

            else { // password incorrect
                if (DEBUG)std::cout << "Error " << this->_serialNumber << ": Your transaction failed – password for account id "<< tokens[1] <<" is incorrect" << std::endl;
                ss << "Error " << this->_serialNumber << ": Your transaction failed – password for account id "<< tokens[1] <<" is incorrect\n";
            }
        }
        else   // Account number not found
        {
            if (DEBUG)std::cout << "Error " << this->_serialNumber <<": Your transaction failed – account id "<< tokens[1] <<" does not exist" << std::endl;
            ss << "Error " << this->_serialNumber <<": Your transaction failed – account id "<< tokens[1] <<" does not exist\n";
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
                    if (DEBUG) std::cout << "Error " << this->_serialNumber <<": Your transaction failed – account id "<< tokens[1] << " balance is lower than "<< tokens[4]<<std::endl;
                    ss << "Error " << this->_serialNumber <<": Your transaction failed – account id "<< tokens[1] << " balance is lower than "<< tokens[4] <<'\n';
                } else{
                    if(DEBUG)  std::cout << "Making Transaction and printing BEFORE" << std::endl;
                    if(DEBUG) _BankDB->PrintAccounts();
                    tempAccount->Withdrawal(stringToInt(tokens[4]));
                    accountToTransasct->Deposit(stringToInt(tokens[4]));
                    if (DEBUG) std::cout <<""<< this->_serialNumber <<": Transfer "  << tokens[4] << " from account " << tokens[1] << " to account " << tokens[3] << " new account balance is " << tempAccount->CheckBalance() << " new target account balance is " << accountToTransasct->CheckBalance() << std::endl;
                    ss << this->_serialNumber <<": Transfer "  << tokens[4] << " from account " << tokens[1] << " to account " << tokens[3] << " new account balance is " << tempAccount->CheckBalance() << " new target account balance is " << accountToTransasct->CheckBalance() <<'\n';
                    if(DEBUG)  std::cout << "Making Transaction and printing AFTER" << std::endl;
                    if(DEBUG) _BankDB->PrintAccounts();
                }
                // need to close thread here??
            }

            else { // password incorrect
                if (DEBUG)std::cout << "Error " << this->_serialNumber << ": Your transaction failed – password for account id "<< tokens[1] <<" is incorrect" << std::endl;
                ss << "Error " << this->_serialNumber << ": Your transaction failed – password for account id "<< tokens[1] <<" is incorrect\n";
            }
        }
        else   // Account number not found
        {
            if (DEBUG)std::cout << "Error " << this->_serialNumber <<": Your transaction failed – account id "<< tokens[1] <<" does not exist" << std::endl;
            ss << "Error " << this->_serialNumber <<": Your transaction failed – account id "<< tokens[1] <<" does not exist\n";
        }
    }
    //write the message to logfile
    logF.WriteLogLine(ss.str());

}
