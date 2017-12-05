cmake_minimum_required(VERSION 3.8)
project(hw2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Account.h Account.cpp BankDB.h BankDB.cpp ATM.h ATM.cpp Threads.h Threads.cpp WriteToLog.h WriteToLog.cpp)
add_executable(hw2 ${SOURCE_FILES})