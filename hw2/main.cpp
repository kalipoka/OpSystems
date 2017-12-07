#include <iostream>
#include <pthread.h>
#include "BankDB.h"
#include "Threads.h"
#include "WriteToLog.h"

//*****************564zfdhfgjjklzdlgnkDLnk
using namespace std;

WriteToLog logF;

int main (int argc, char **argv){

    // argv[0] will be the number of ATMs - each ATM will receive one filename
    // we then need to create the threads and initialize all the ATMS with the needed data




    // This is the version without concurrency
    BankDB Citi;// = BankDB();
    ATM tryATM(1, &Citi);
    tryATM.ReadCommandsFromFile("D:\\semesters\\Winter_2018\\046209\\HW2_withGIT\\OpSystems\\hw2\\in1.txt");
    Citi.PrintAccounts();
    Citi.ChargeFee();

/*
       BankDB Citi;

       thread_data_atm atm_args;

       // initialize arguments
       string path ="C:\\Users\\alexey\\Source\\Repos\\OpSystems\\hw2\\in1.txt";

       atm_args.atm_id = 1;
       atm_args.pathToInstructions = path;
       atm_args.DB = &Citi;

     pthread_t my_thread;
       pthread_create(&my_thread,NULL, &thread_atm,(void *) &atm_args );


    // here we make a printing thread - works (without locking yet)

    pthread_t print_status;
    pthread_create(&print_status,NULL, &thread_bank_print,(void *) &Citi );   // need to add the periodic waiting and printing



    // wait for the threads
    if (pthread_join(my_thread,NULL)){
        perror("Join  Working ATM thread Fail");
        exit(1);
    }

    if (pthread_join(print_status,NULL)){
        perror("Join Printing Fail");
        exit(1);
    }
*/
    return 0;
}
