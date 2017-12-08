//
// Created by alexey on 06-Dec-17.
//

#include <pthread.h>
#include <string>
#include <iostream>
#include <fstream>
#include "WriteToLog.h"
#include "Account.h"


WriteToLog::WriteToLog() {

    myLog.open("../log.txt");

    if (pthread_mutex_init(&loglock, NULL)) {
        perror("loglock could not be initialized");
        exit(1);
    }
}

WriteToLog::~WriteToLog() {
    if (pthread_mutex_destroy(&loglock)) {
        perror("loglock could not be destroyed");
        exit(1);
    }
    myLog.close();
}

void WriteToLog::WriteLogLine(string str) {

    if (pthread_mutex_lock(&loglock)) {
        perror("loglock Could not be locked");
        exit(1);
    }

    if (DEBUG) std::cout << "Error " << std::endl;
    myLog << str;

    if (pthread_mutex_unlock(&loglock)) {
        perror("loglock Could not be unlocked");
        exit(1);
    }
};