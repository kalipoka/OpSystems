//
// Created by alexey on 02-Dec-17.
//

#include "Threads.h"

//bool CompareFunction (Account Acc1,Account Acc2 ) { return (Acc1.GetAccountNumber() <Acc2.GetAccountNumber()); }

void *thread_atm (void *arguments){

     std::cout << "Entered Creating ATM Thread \n" << std::endl;

    thread_data_atm* temp = static_cast<thread_data_atm *> (arguments);
    string path = string(temp->pathToInstructions);
    ATM workATM(temp->atm_id,temp->DB); // created an operating atm;
    workATM.ReadCommandsFromFile(path);

    std::cout << "Exit ATM1 Thread \n" << std::endl;

    pthread_exit(NULL);
};

// I want to transfer him the database - but maybe some more are needed

void *thread_bank_print(void* args) {

    std::cout << "Entered Print Thread \n" << std::endl;

    BankDB* temp = static_cast<BankDB *>(args) ;

    temp->PrintAccounts();

    std::cout << "Exit Print Thread \n" << std::endl;

    pthread_exit(NULL);
}

void *thread_bank_charge(void* args){

    std::cout << "Entered Fee Charge Thread \n" << std::endl;

    BankDB* temp = static_cast<BankDB *>(args) ;
    temp->ChargeFee();

    std::cout << "Exit Fee Charge Thread \n" << std::endl;


    pthread_exit(NULL);


}