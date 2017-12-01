//
// Created by alexey on 30-Nov-17.
//

#ifndef HW2_CASHIER_H
#define HW2_CASHIER_H

#include <thread>
#include <pthread.h>
#include <string>
#include <vector>
#include "BankDB.h"

#define DEBUG 1

using namespace std;
class BankDB;

class ATM {

public:

    ATM(int serialNumber, BankDB * DB );
    ~ATM();

    void ReadCommandsFromFile(string path);
    void ExecuteCommand(string command);

// need to  add here all the actions - this is just for the structure debug

private:
    int _serialNumber;
    BankDB * _BankDB;
};


// declarations of some usefull function for our implementations

int stringToInt(const string s);
vector<string> tokenize(string line, const char* delim);

#endif //HW2_CASHIER_H
