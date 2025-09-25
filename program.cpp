//test test
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
using namespace std;

struct Transaction {
    string type;      
    string store;      
    string category;
    double amount;
    string transactionId;
};

struct User {
    string name;
    double balance;
    int phoneNum;
    vector<Transaction> history;
};

vector<User> users;
User* currentUser = nullptr;
int nextTransactionId = 1000;

/// 🔹 Safe input functions
int getIntInput(string prompt, int min, int max) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= min && value <= max) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cout << "Invalid input. Please enter a number between " << min << " and " << max << "." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

double getDoubleInput(string prompt, double min = 0) {
    double value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= min) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cout << "Invalid input. Please enter a number >= " << min << "." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

/// function prototypes ///
void loginMenu();
void registerUser();
void loginUser();
void logoutUser();
void menuDisplay();
void makePayment();
void topUp();

void loginMenu() {
    int choice;
    do {
        cout << "========== E-Wallet ==========" << endl;
        cout << "1. Register New User" << endl;
        cout << "2. Login Existing User" << endl;
        cout << "0. Exit" << endl;
        choice = getIntInput("Select: ", 0, 2);

        switch (choice) {
            case 1: registerUser(); break;
            case 2: loginUser(); break;
            case 0: cout << "Exiting program..." << endl; break;
        }
        cout << endl;
    } while (choice != 0);
}

void registerUser() {
    User newUser;
    cout << "Enter your name: ";
    cin.ignore();
    getline(cin, newUser.name);

    newUser.phoneNum = getIntInput("Enter phone number: ", 1000, 999999999);

    newUser.balance = getDoubleInput("Enter starting balance (RM): ", 0.0);

    users.push_back(newUser);
    cout << "User registered successfully." << endl;
}

void loginUser() {
    if (users.empty()) {
        cout << "No users registered. Please register first." << endl;
        return;
    }

    int phone = getIntInput("Enter phone number to login: ", 1000, 999999999);

    for (auto &user : users) {
        if (user.phoneNum == phone) {
            currentUser = &user;
            cout << "Welcome, " << currentUser->name << "!" << endl;
            menuDisplay();
            return;
        }
    }
    cout << "User not found. Please register first." << endl;
}

void logoutUser() {
    cout << "Logging out " << currentUser->name << "..." << endl;
    currentUser = nullptr;
}

void menuDisplay() {
    int choice;
    do {
        cout << "--------------------------------" << endl;
        cout << "           E-Wallet             " << endl;
        cout << "User: " << currentUser->name << endl;
        cout << "Balance: RM" << fixed << setprecision(2) << currentUser->balance << endl;
        cout << "--------------------------------" << endl;
        cout << "1. Make Payment" << endl;
        cout << "2. View Balance" << endl;
        cout << "3. Transaction History" << endl;
        cout << "4. Top-Up Balance" << endl;
        cout << "5. Logout" << endl;
        cout << "6. Spending by Category" << endl;
        cout << "0. Exit Program" << endl;

        choice = getIntInput("Select: ", 0, 6);

        switch (choice) {
            case 1: makePayment(); break;
            case 2:
                cout << "Current Balance: RM" << fixed << setprecision(2) 
                     << currentUser->balance << endl;
                break;
            case 3: {
                cout << "===== Transaction History =====" << endl;
                if (currentUser->history.empty()) {
                    cout << "No transactions available." << endl;
                } else {
                    cout << left << setw(10) << "ID"
                         << setw(12) << "Type"
                         << setw(20) << "Store"
                         << setw(12) << "Category"
                         << right << setw(10) << "Amount" << endl;
                    cout << string(64, '-') << endl;

                    for (const auto &t : currentUser->history) {
                        cout << left << setw(10) << t.transactionId
                             << setw(12) << t.type
                             << setw(20) << t.store
                             << setw(12) << t.category
                             << right << setw(10) << fixed << setprecision(2) << t.amount
                             << endl;
                    }
                }
                break;
            }
            case 4: topUp(); break;
            case 5: logoutUser(); return;
            case 6: {
                cout << "===== Spending by Category =====" << endl;
                map<string, double> totals;
                for (const auto &t : currentUser->history) {
                    if (t.type == "Payment") {
                        totals[t.category] += t.amount;
                    }
                }
                if (totals.empty()) {
                    cout << "No spending yet." << endl;
                } else {
                    for (auto &p : totals) {
                        cout << p.first << ": RM" << fixed << setprecision(2) << p.second << endl;
                    }
                }
                break;
            }
            case 0: cout << "Exiting program..." << endl; exit(0);
        }
        cout << endl;
    } while (choice != 0);
}

void makePayment() {
    cout << "===== CHOOSE STORE =====" << endl;
    cout << " 1. McDonald's " << endl;
    cout << " 2. KFC " << endl;
    cout << " 3. Grab " << endl;
    cout << " 4. FamilyMart" << endl;
    cout << " 5. Shopee " << endl;
    cout << " 6. Others " << endl;

    int number = getIntInput("Select store: ", 1, 6);

    string store, category;
    switch (number) {
        case 1: store = "McDonald's"; category = "Food"; break;
        case 2: store = "KFC"; category = "Food"; break;
        case 3: store = "Grab"; category = "Transport"; break;
        case 4: store = "FamilyMart"; category = "Food"; break;
        case 5: store = "Shopee"; category = "Shopping"; break;
        case 6:
            cout << "Enter store name: ";
            getline(cin, store);
            cout << "Enter category (Food/Shopping/Transport/etc.): ";
            getline(cin, category);
            break;
    }

    double amount = getDoubleInput("Enter amount to pay (RM): ", 0.01);

    if (amount > currentUser->balance) {
        cout << "Payment failed. Not enough balance." << endl;
        return;
    }

    currentUser->balance -= amount;

    Transaction newTransaction = {
        "Payment",
        store,
        category,
        amount,
        "TXN" + to_string(nextTransactionId++)
    };
    currentUser->history.push_back(newTransaction);

    cout << "Payment successful. Transaction ID: " << newTransaction.transactionId << endl;
}

void topUp() {
    double amount = getDoubleInput("Enter top-up amount (RM): ", 0.01);

    currentUser->balance += amount;

    Transaction topUpTransaction = {
        "Top-Up",
        "E-Wallet",
        "Top-Up",
        amount,
        "TXN" + to_string(nextTransactionId++)
    };
    currentUser->history.push_back(topUpTransaction);

    cout << "Top-up successful. New balance: RM" 
         << fixed << setprecision(2) << currentUser->balance << endl;
}

int main() {
    loginMenu();
    return 0;
}
