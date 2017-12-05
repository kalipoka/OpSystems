//
// Created by alexey on 06-Dec-17.
//
#ifndef HW2_WRITETOLOG_H
#define HW2_WRITETOLOG_H

#include <iostream>
#include <fstream>
#include <pthread.h>
#include <string>

using namespace std;
using std::ofstream;
using std::string;

class WriteToLog {
public:

    WriteToLog();
    ~WriteToLog();

    void WriteLogLine(string str);  // writes a line to the log file


private:
    pthread_mutex_t loglock;
    ofstream myLog;
};


#endif //HW2_WRITETOLOG_H