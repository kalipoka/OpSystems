//
// Created by alexey on 30-Nov-17.
//
#ifndef HW2_ACCOUNT_H
#define HW2_ACCOUNT_H
#include <thread>

class Account {

public:
    Account(int accountNumber,int password,int balance);
    ~Account();

    int GetAccountNumber();
    int CheckBalance();
    bool CheckIsVIP ();
    bool ComparePassword(int passwordToCheck);

    void BecomeVip();

private:
    int _accountNumber;
    int _password;
    int _balance;
    bool _isVIP;

};


#endif //HW2_ACCOUNT_H
