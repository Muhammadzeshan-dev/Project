#include <iostream>
using namespace std;
class BankAccount {
public:
    string accountHolder;
    string accountNumber;
    double balance;
    BankAccount(string holder, string number, double initialBalance = 0) {
    accountHolder = holder;
    accountNumber = number;
    balance = initialBalance;
    }
	void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposited: $" << amount << ". New Balance: $" << balance << endl;
        } else {
            cout << "Amount should be positive!" << endl;
        }
    }

    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrew: $" << amount << ". New Balance: $" << balance << endl;
        } else {
            cout << "Insufficient balance or invalid amount!" << endl;
        }
    }

    void checkBalance() {
        cout << "Current Balance: $" << balance << endl;
    }
};

int main() {
    string holderName, accountNumber;
    double initialDeposit;
    int choice;
    cout << "Enter account holder name: ";
    getline(cin, holderName);
    cout << "Enter account number: ";
    getline(cin, accountNumber);
    cout << "Enter initial deposit amount: ";
    cin >> initialDeposit;
    BankAccount account(holderName, accountNumber, initialDeposit);
    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Deposit Money\n";
        cout << "2. Withdraw Money\n";
        cout << "3. Check Balance\n";
        cout << "4. Exit\n";
        cout << "Choose an option (1-4): ";
        cin >> choice;
		if (choice == 1) {
            double depositAmount;
            cout << "Enter amount to deposit: ";
            cin >> depositAmount;
            account.deposit(depositAmount);
        } 
        else if (choice == 2) {
            double withdrawAmount;
            cout << "Enter amount to withdraw: ";
            cin >> withdrawAmount;
            account.withdraw(withdrawAmount);
        } 
        else if (choice == 3) {
            account.checkBalance();
        } 
        else if (choice == 4) {
            cout << "Exiting the system. Goodbye!" << endl;
            break;
        } 
        else {
            cout << "Invalid option! Please try again." << endl;
        }
    }

    return 0;
}
