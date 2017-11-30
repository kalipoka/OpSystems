#include <iostream>
#include "Account.h"
#include "Bank.h"

#include <vector>
#include <string>
#include <sstream>

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


int main() {


    //debuuga
    Account Yosi = Account(0001, 8888, 40 );
    Account Bolt = Account(0003, 7777,700 );

    Bank Citi = Bank(3);
    std::cout << "Hello, World!, Welcome To the BANK BANG BANG" << std::endl;
    // delete debuga till here


    const char* delims = " \t\n";
    vector<string> tokens;
    string line;

    int mone = 0;
    while (!cin.eof()) {

        getline(cin, line);
        tokens = tokenize(line, delims);
        mone++;
        if (tokens.size() == 0) {
            continue;
        }

        if (tokens[0] == "O") {
            Account newAccount = Account(stringToInt(tokens[1]),stringToInt(tokens[2]),stringToInt(tokens[3]));
            Citi.AddAccount( newAccount);
            if(DEBUG)  std::cout << "Adding account and printing" << std::endl;
            if(DEBUG) Citi.PrintAccounts();
            continue;
        }
    }


    /*
    Citi.AddAccount(Yosi);
    Citi.AddAccount(Bolt);
    std::cout << "Printing Accounts Numbers:" << std::endl;
    Citi.PrintAccounts();
*/
    return 0;
}


