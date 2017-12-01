#include <iostream>
#include "Account.h"
#include "BankDB.h"

#include <vector>
#include <string>
#include <sstream>
#include <fstream>

#define DEBUG 1

using namespace std;

/*
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


int main() {


    std::cout << "Hello, World!, Welcome To the BANK BANG BANG" << std::endl;

    static BankDB Citi = BankDB();

    const char* delims = " \t\n";
    vector<string> tokens;
    string line;

   // freopen("in1.txt", "r", stdin);

    std::ifstream inFile ("C:\\Users\\alexey\\Source\\Repos\\OpSystems\\hw2\\in1.txt",std::ifstream::in);

if (inFile.is_open())
{
    std::cout << "Good Opened" << std::endl;
}

    int mone = 0;
   // while (!cin.eof()) {
      while(( getline (inFile,line) )){
       // getline(cin, line);
       if(DEBUG) std::cout << line << std::endl;
        tokens = tokenize(line, delims);
        mone++;
        if (tokens.size() == 0) {
            continue;
        }
          // Open Account
        if (tokens[0] == "O") {
            //Create Account - asuming legal input
            Account newAccount = Account(stringToInt(tokens[1]),stringToInt(tokens[2]),stringToInt(tokens[3]));
            // need to open / insert threads here
            Citi.AddAccount( newAccount);
            // need to close thread here
            if(DEBUG)  std::cout << "Adding account and printing" << std::endl;
            if(DEBUG) Citi.PrintAccounts();
        }

        // Make an Account a VIP
        if (tokens[0] == "L"){
            Account* tempAccount = Citi.FindAccountByNumber(stringToInt(tokens[1]));
            if (tempAccount!= NULL)  // found such an account
            {
                if (tempAccount->ComparePassword(stringToInt(tokens[2])))
                {
                    if(DEBUG)  std::cout << "Adding account and printing BEFORE" << std::endl;
                    if(DEBUG) Citi.PrintAccounts();
                    // need to open / insert threads here
                    tempAccount->BecomeVip();
                    // need to close thread here
                    if(DEBUG)  std::cout << "Adding account and printing AFTER" << std::endl;
                    if(DEBUG) Citi.PrintAccounts();
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
            Account *tempAccount = Citi.FindAccountByNumber(stringToInt(tokens[1]));
            if (tempAccount != NULL)  // found such an account
            {
                if (tempAccount->ComparePassword(stringToInt(tokens[2])))  // correct password
                {
                    if (DEBUG) std::cout << "Adding Diposit  and printing BEFORE" << std::endl;
                    if (DEBUG) Citi.PrintAccounts();
                    tempAccount->Deposit(stringToInt(tokens[3]));
                    std::cout << "<ATM ID>: Account <id> new balance is <bal> after <amount> $ was deposited"
                              << std::endl;   //succes
                    if (DEBUG) std::cout << "Adding Diposit  and printing AFTER" << std::endl;
                    if (DEBUG) Citi.PrintAccounts();
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
            Account *tempAccount = Citi.FindAccountByNumber(stringToInt(tokens[1]));
            if (tempAccount != NULL)  // found such an account
            {
                if (tempAccount->ComparePassword(stringToInt(tokens[2])))  // correct password
                {
                    if (DEBUG) std::cout << "Making withdrawal  and printing BEFORE" << std::endl;
                    if (DEBUG) Citi.PrintAccounts();

                    if(!tempAccount->Withdrawal(stringToInt(tokens[3]))) // if return value is 0 - we succeded
                    {
                        std::cout << "<ATM ID>: Account <id> new balance is <bal> after <amount> $ was withdrew"  << std::endl;   //succes
                        if (DEBUG) std::cout << "Making withdrawal  and printing AFTER" << std::endl;
                        if (DEBUG) Citi.PrintAccounts();
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
            Account* tempAccount = Citi.FindAccountByNumber(stringToInt(tokens[1]));
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

            Account* tempAccount = Citi.FindAccountByNumber(stringToInt(tokens[1]));
            Account* accountToTransasct = Citi.FindAccountByNumber(stringToInt(tokens[3]));  //looking for the new account to transact

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
                        Citi.PrintAccounts();
                        tempAccount->Withdrawal(stringToInt(tokens[4]));
                        accountToTransasct->Deposit(stringToInt(tokens[4]));
                        std::cout << "<ATM ID>: Transfer <amount> from account <account> to account <target_account> new account\n"
                                "balance is <account_bal> new target account balance is <target_bal>" << std::endl;
                        if(DEBUG)  std::cout << "Making Transaction and printing AFTER" << std::endl;
                        Citi.PrintAccounts();
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

    inFile.close();
    return 0;
}

*/

int main (int argc, char **argv){

    BankDB Citi = BankDB();

    ATM tryATM(1, &Citi);

    tryATM.ReadCommandsFromFile("C:\\Users\\alexey\\Source\\Repos\\OpSystems\\hw2\\in1.txt");

    return 0;
}
