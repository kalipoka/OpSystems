//
// Created by alexey on 30-Nov-17.
//

#ifndef HW2_CASHIER_H
#define HW2_CASHIER_H


#include <thread>
#include <pthread.h>
#include <string>

#define DEBUG 1

using namespace std;

class ATM {

public:

    ATM(int serialNumber);
    ~ATM();

    void MakeCommand(string path);

// need to  add here all the actions - this is just for the structure debug

private:
    int _serialNumber;
};

#endif //HW2_CASHIER_H
