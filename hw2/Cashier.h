//
// Created by alexey on 30-Nov-17.
//

#ifndef HW2_CASHIER_H
#define HW2_CASHIER_H
#include <thread>

class Cashier {

public:

    Cashier(int serialNumber);
    ~Cashier();

// need to  add here all the actions - this is just for the structure debug

private:
    int _serialNumber;
};

#endif //HW2_CASHIER_H
