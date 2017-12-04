//
// Created by alexey on 02-Dec-17.
//

#include "Threads.h"

//bool CompareFunction (Account Acc1,Account Acc2 ) { return (Acc1.GetAccountNumber() <Acc2.GetAccountNumber()); }

void *thread_atm (void *arguments){

    if(DEBUG) std::cout << "Entered Creating Thread" << std::endl;

    thread_data_atm* temp = static_cast<thread_data_atm *> (arguments);
    string path = string(temp->pathToInstructions);
    ATM workATM(temp->atm_id,temp->DB); // created an operating atm;
    workATM.ReadCommandsFromFile(path);
    pthread_exit(NULL);
};

// I want to transfer him the database - but maybe some more are needed

void *thread_bank_print(void* args) {

   if(DEBUG) std::cout << "Entered Print Thread" << std::endl;

    BankDB* temp = static_cast<BankDB *>(args) ;
    printf("\033[2J");
    printf("\033[1;1H");
    cout << "Current Bank Status" << endl;
    temp->PrintAccounts();
    cout << "The Bank has " << temp->GetBankBalance() << " $" << endl;
    pthread_exit(NULL);
}
