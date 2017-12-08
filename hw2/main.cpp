#include <iostream>
#include <pthread.h>
#include "BankDB.h"
#include "Threads.h"
#include "WriteToLog.h"

using namespace std;

WriteToLog logF;

int main (int argc, char **argv){

    // argv[0] will be the number of ATMs - each ATM will receive one filename
    // we then need to create the threads and initialize all the ATMS with the needed data


    // This is the version without concurrency
/*
    BankDB Citi;// = BankDB();
    ATM tryATM(1, &Citi);
    tryATM.ReadCommandsFromFile("../in1.txt");
    Citi.PrintAccounts();
    Citi.ChargeFee();
    Citi.PrintAccounts();
    Citi.ChargeFee();
    Citi.PrintAccounts();
    */

    // Locking and threads version


       BankDB Citi;

       thread_data_atm atm_args;

       // initialize arguments
       string path ="../in1.txt";
       atm_args.atm_id = 1;
       atm_args.pathToInstructions = path;
       atm_args.DB = &Citi;

     pthread_t my_thread; // ATM thread
    pthread_create(&my_thread,NULL, &thread_atm,(void *) &atm_args );

    // Here we make a printing thread - works (without locking yet)

    pthread_t print_status;
    pthread_create(&print_status,NULL, &thread_bank_print,(void *) &Citi );   // need to add the periodic waiting and printing

    // Here we make a Fee Charging thread - works (without locking yet)
    pthread_t charge;
    pthread_create(&charge, NULL, &thread_bank_charge,(void *) &Citi);

    // wait for the threads
    if (pthread_join(my_thread,NULL)){
        perror("Join  Working ATM thread Fail");
        exit(1);
    }



    Citi.close(); // need to make a little more complicated - this will happen when all the ATM finish working

    if (pthread_join(print_status,NULL)){
        perror("Join Printing Fail");
        exit(1);
    }

    if (pthread_join(charge, NULL)){
        perror("Join Charging Fee Fail");
        exit(1);
    }

    return 0;
}
