#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

struct Transaction {
    string type;   //type of payment
    string store;
    double amount;
    string transactionid;

};

struct User {
    string name;
    double balance;
    int phoneNum;
    vector<Transaction> history;
};


int main(){

}