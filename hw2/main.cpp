#include <iostream>
#include "Account.h"
#include "BankDB.h"

#include <vector>
#include <string>
#include <sstream>
#include <fstream>

#define DEBUG 1

using namespace std;

int main (int argc, char **argv){

    BankDB Citi = BankDB();

    ATM tryATM(1, &Citi);

    tryATM.ReadCommandsFromFile("C:\\Users\\alexey\\Source\\Repos\\OpSystems\\hw2\\in1.txt");

    return 0;
}
