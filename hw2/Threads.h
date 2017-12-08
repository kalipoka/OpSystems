//
// Created by alexey on 02-Dec-17.
//

#ifndef HW2_THREADS_H
#define HW2_THREADS_H

#include "BankDB.h"

struct thread_data_atm {

    int atm_id;
    BankDB *DB;
    string pathToInstructions;

};

void *thread_atm (void *arguments);  //

void *thread_bank_print(void* args); // thread for the printing of the bank

void *thread_bank_charge(void* args);  // thread for the commision charge of the bank

//

#endif //HW2_THREADS_H
