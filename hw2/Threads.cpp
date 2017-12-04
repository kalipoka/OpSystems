//
// Created by alexey on 02-Dec-17.
//

#include "Threads.h"

//bool CompareFunction (Account Acc1,Account Acc2 ) { return (Acc1.GetAccountNumber() <Acc2.GetAccountNumber()); }


void *thread_atm (void *arguments){

    if(DEBUG) std::cout << "Entered Creating Thread" << std::endl;

    thread_data_atm *temp = (thread_data_atm *) arguments;
    string path = string(temp->pathToInstructions);

    path = "C:\\Users\\alexey\\Source\\Repos\\OpSystems\\hw2\\in1.txt";  // only debug purpose

    ATM workATM(temp->atm_id,temp->DB); // created an operating atm;

    workATM.ReadCommandsFromFile("C:\\Users\\alexey\\Source\\Repos\\OpSystems\\hw2\\in1.txt");
    //workATM.ReadCommandsFromFile(path);

    pthread_exit(NULL);
};

// I want to transfer him the database - but maybe some more are needed

void *thread_bank_print(void* args) {

    std::cout << "Entered Print Thread" << std::endl;

   BankDB *temp = (BankDB *) args;
/*
    if (temp->_numberOfAccounts > 1)  // sort only if more than 1 element
        temp->_accountsList->sort(CompareFunction);

    //here need to lock
    for (auto i  =temp->_accountsList->begin(); i !=temp->_accountsList->end(); ++i){

        std::cout << i->GetAccountNumber() << "\t" << i->GetPassword() << "\t" << i->CheckBalance()  << "\t" << i->CheckIsVIP()  << std::endl;
    }

    if(DEBUG) std::cout << "Finished Printing with thread" << std::endl;
    //here need to unlock;

*/
    temp->PrintAccounts();
    pthread_exit(NULL);
}
