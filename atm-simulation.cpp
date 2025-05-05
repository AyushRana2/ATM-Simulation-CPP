#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Account {
private:
    int accountNumber;
    string accountHolderName;
    string pin;
    double balance;
    vector<string> miniStatement;

public:
    Account(int accNo, string name, string pinCode, double initialBalance) {
        accountNumber = accNo;
        accountHolderName = name;
        pin = pinCode;
        balance = initialBalance;
        miniStatement.push_back("Account created with balance ₹" + to_string(initialBalance));
    }

    int getAccountNumber() const {
        return accountNumber;
    }

    bool authenticate(string enteredPin) const {
        return pin == enteredPin;
    }

    void checkBalance() const {
        cout << "Current Balance: ₹" << balance << endl;
    }

    void deposit(double amount) {
        if (amount <= 0) {
            cout << "Invalid deposit amount!\n";
            return;
        }
        balance += amount;
        miniStatement.push_back("Deposited ₹" + to_string(amount));
        cout << "Deposited ₹" << amount << " successfully.\n";
    }

    void withdraw(double amount) {
        if (amount <= 0) {
            cout << "Invalid withdrawal amount!\n";
        } else if (amount > balance) {
            cout << "Insufficient balance!\n";
        } else {
            balance -= amount;
            miniStatement.push_back("Withdrawn ₹" + to_string(amount));
            cout << "Withdrawn ₹" << amount << " successfully.\n";
        }
    }

    void showDetails() const {
        cout << "\n--- Account Details ---\n";
        cout << "Account Holder: " << accountHolderName << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "Current Balance: ₹" << balance << endl;
    }

    void showMiniStatement() const {
        cout << "\n--- Mini Statement ---\n";
        for (const string& entry : miniStatement) {
            cout << entry << endl;
        }
    }
};

// Utility to find account
Account* findAccount(vector<Account>& accounts, int accNo) {
    for (auto& acc : accounts) {
        if (acc.getAccountNumber() == accNo) return &acc;
    }
    return nullptr;
}

int main() {
    vector<Account> accounts;

    // Predefined accounts
    accounts.push_back(Account(1111, "Ayush Sharma", "1234", 15000));
    accounts.push_back(Account(2222, "Rahul Verma", "5678", 12000));
    accounts.push_back(Account(3333, "Sneha Kapoor", "0000", 18000));

    cout << "====== Welcome to ATM ======\n";

    int accNo, attempts = 0;
    string pin;
    Account* currentUser = nullptr;

    // Authentication Loop
    while (attempts < 3) {
        cout << "Enter Account Number: ";
        cin >> accNo;
        cout << "Enter 4-digit PIN: ";
        cin >> pin;

        currentUser = findAccount(accounts, accNo);

        if (currentUser != nullptr && currentUser->authenticate(pin)) {
            cout << "Login successful!\n";
            break;
        } else {
            cout << "Invalid account number or PIN. Try again.\n";
            currentUser = nullptr;
            attempts++;
        }
    }

    if (!currentUser) {
        cout << "Too many failed attempts. Exiting...\n";
        return 0;
    }

    // ATM Menu
    int choice;
    do {
        cout << "\n======= ATM Menu =======\n";
        cout << "1. Check Balance\n";
        cout << "2. Deposit\n";
        cout << "3. Withdraw\n";
        cout << "4. Mini Statement\n";
        cout << "5. Show Account Details\n";
        cout << "6. Exit\n";
        cout << "Enter your choice (1-6): ";
        cin >> choice;

        switch (choice) {
            case 1:
                currentUser->checkBalance();
                break;
            case 2: {
                double amount;
                cout << "Enter amount to deposit: ₹";
                cin >> amount;
                currentUser->deposit(amount);
                break;
            }
            case 3: {
                double amount;
                cout << "Enter amount to withdraw: ₹";
                cin >> amount;
                currentUser->withdraw(amount);
                break;
            }
            case 4:
                currentUser->showMiniStatement();
                break;
            case 5:
                currentUser->showDetails();
                break;
            case 6:
                cout << "Thank you for using the ATM. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}
