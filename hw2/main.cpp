#include <iostream>
#include <pthread.h>
#include "BankDB.h"
#include "Threads.h"

#define DEBUG 1

using namespace std;

int main (int argc, char **argv){


    // argv[0] will be the number of ATMs - each ATM will receive one filename
    // we then need to create the threads and initialize all the ATMS with the needed data


    // creating the data set - it will be used and acceced by all the ATMS and by the bnk itself
/*
    BankDB Citi;// = BankDB();

    thread_data_atm atm_args;

    // initialize arguments
    string path ="C:\\Users\\alexey\\Source\\Repos\\OpSystems\\hw2\\in1.txt";

    atm_args.atm_id = 1;
    atm_args.pathToInstructions = path;
    atm_args.DB = &Citi;

    pthread_t my_thread;

    pthread_create(&my_thread,NULL, &thread_atm,(void *) &atm_args );
 */

    // here we try before threads
    // create one atms with access to the data

    BankDB Citi = BankDB();
    ATM tryATM(1, &Citi);
    tryATM.ReadCommandsFromFile("C:\\Users\\alexey\\Source\\Repos\\OpSystems\\hw2\\in1.txt");

    return 0;
}
