#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

struct Transaction {
    string type;   //type of payment
    string store;
    double amount;
    string TransactionId;

};

struct User {
    string name;
    double balance;
    int phoneNum;
    vector<Transaction> history;
};

User currentUser;
int nextTransactionId = 1000;

///function prototypes///
void menuDisplay();
void makePayment();


void menuDisplay(){
    cout << "--------------------------------" << endl;
    cout << "           E-Wallet             " << endl;
    //add more here
}




void makePayment(){
    cout << "===== CHOOSE STORE =====" << endl;
    cout << " 1. McDonald's " << endl;
    cout << " 2. KFC " << endl;
    cout << " 3. Grab " << endl;
    cout << " 4. FamilyMart" << endl;
    cout << " 5. Shopee " << endl;
    cout << " 6. Others " << endl;

    int number;
    cout << "Select store: ";
    cin >> number;

    string store;
    switch (number)
    {
    case 1:
        store = "McDonald's";
        break;
    case 2:
        store = "KFC";
        break;
    case 3:
        store = "Grab";
        break;
    case 4:
        store = "FamilyMart";
        break;
    case 5:
        store = "Shopee";
        break;
    case 6:
        cout << "Enter store name: ";
        cin.ignore();
        getline(cin, store);
        break;

    default:
        cout << "Invalid choice. Using 'Unknown store'" << endl;
        store = "Unknown store";
    }
}
int main() {

}