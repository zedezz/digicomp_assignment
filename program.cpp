#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

struct Transaction {
    string type;   // e.g., "Payment" or "Top-Up"
    string store;  // store or "Top-Up"
    double amount;
    string transactionId;
};

struct User {
    string name;
    double balance;
    int phoneNum;
    vector<Transaction> history;
};

vector<User> users;        // all registered users
User* currentUser = nullptr; // pointer to the active user
int nextTransactionId = 1000;

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
        cout << "Select: ";
        cin >> choice;

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                loginUser();
                break;
            case 0:
                cout << "Exiting program..." << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
        cout << endl;
    } while (choice != 0);
}

void registerUser() {
    User newUser;
    cout << "Enter your name: ";
    cin.ignore();
    getline(cin, newUser.name);

    cout << "Enter phone number: ";
    cin >> newUser.phoneNum;

    cout << "Enter starting balance (RM): ";
    cin >> newUser.balance;

    users.push_back(newUser);
    cout << "User registered successfully." << endl;
}

void loginUser() {
    if (users.empty()) {
        cout << "No users registered. Please register first." << endl;
        return;
    }

    int phone;
    cout << "Enter phone number to login: ";
    cin >> phone;

    for (auto &user : users) {
        if (user.phoneNum == phone) {
            currentUser = &user;
            cout << "Welcome, " << currentUser->name << "!" << endl;
            menuDisplay(); // go to wallet menu
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
        cout << "Balance: RM" << fixed << setprecision(2) 
             << currentUser->balance << endl;
        cout << "--------------------------------" << endl;
        cout << "1. Make Payment" << endl;
        cout << "2. View Balance" << endl;
        cout << "3. Transaction History" << endl;
        cout << "4. Top-Up Balance" << endl;
        cout << "5. Logout" << endl;
        cout << "0. Exit Program" << endl;
        cout << "Select: ";
        cin >> choice;

        switch (choice) {
            case 1:
                makePayment();
                break;
            case 2:
                cout << "Current Balance: RM" << fixed << setprecision(2) 
                     << currentUser->balance << endl;
                break;
            case 3:
                cout << "===== Transaction History =====" << endl;

                if (currentUser->history.empty()) {
                    cout << "No transactions available." << endl;
                } else {
                    // Table header
                    cout << left << setw(10) << "ID"
                         << setw(12) << "Type"
                         << setw(20) << "Store"
                         << right << setw(10) << "Amount" << endl;
                    cout << string(52, '-') << endl;

                    // Transactions
                    for (const auto &t : currentUser->history) {
                        cout << left << setw(10) << t.transactionId
                             << setw(12) << t.type
                             << setw(20) << t.store
                             << right << setw(10) << fixed << setprecision(2) << t.amount
                             << endl;
                    }
                }
                break;
            case 4:
                topUp();
                break;
            case 5:
                logoutUser();
                return; // back to login menu
            case 0:
                cout << "Exiting program..." << endl;
                exit(0);
            default:
                cout << "Invalid choice!" << endl;
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

    int number;
    cout << "Select store: ";
    cin >> number;

    string store;
    switch (number) {
        case 1: store = "McDonald's"; break;
        case 2: store = "KFC"; break;
        case 3: store = "Grab"; break;
        case 4: store = "FamilyMart"; break;
        case 5: store = "Shopee"; break;
        case 6:
            cout << "Enter store name: ";
            cin.ignore();
            getline(cin, store);
            break;
        default:
            cout << "Invalid choice. Using 'Unknown store'" << endl;
            store = "Unknown store";
    }

    double amount;
    cout << "Enter amount to pay: RM";
    cin >> amount;

    if (amount > currentUser->balance) {
        cout << "Payment failed. Not enough balance." << endl;
        return;
    }

    // Deduct balance
    currentUser->balance -= amount;

    // Create transaction
    Transaction newTransaction = {"Payment", store, amount, "TXN" + to_string(nextTransactionId++)};
    currentUser->history.push_back(newTransaction);

    cout << "Payment successful. Transaction ID: " << newTransaction.transactionId << endl;
}

void topUp() {
    double amount;
    cout << "Enter top-up amount (RM): ";
    cin >> amount;

    if (amount <= 0) {
        cout << "Invalid amount. Please enter more than 0." << endl;
        return;
    }

    currentUser->balance += amount;

    // Create transaction record
    Transaction topUpTransaction = {"Top-Up", "E-Wallet", amount, "TXN" + to_string(nextTransactionId++)};
    currentUser->history.push_back(topUpTransaction);

    cout << "Top-up successful. New balance: RM" 
         << fixed << setprecision(2) << currentUser->balance << endl;
}

int main() {
    loginMenu();
    return 0;
}
