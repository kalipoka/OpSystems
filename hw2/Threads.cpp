//
// Created by alexey on 02-Dec-17.
//

#include "Threads.h"

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

