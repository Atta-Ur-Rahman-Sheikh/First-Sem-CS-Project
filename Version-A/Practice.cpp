#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <ctime>
#include <map>

using namespace std;

class Transaction {
public:
    string description;
    float amount;
    string category;
    string date;

    Transaction(const string& desc, float amt, const string& cat) 
        : description(desc), amount(amt), category(cat) {
            // Get current date and time
            time_t now = time(0);
            char* dt = ctime(&now);
            date = string(dt).substr(0, 24);  // Trim newline from ctime
    }
};

class FinanceManager {
private:
    vector<Transaction> transactions;
    const string fileName = "transactions.txt";

    // Load transactions from file
    void loadTransactions() {
        ifstream file(fileName);
        if (file.is_open()) {
            string desc, cat, date;
            float amt;
            while (getline(file, desc)) {
                file >> amt;
                file.ignore(); // Ignore newline after amount
                getline(file, cat);
                getline(file, date);

                transactions.push_back(Transaction(desc, amt, cat));
            }
            file.close();
        }
    }

    // Save transactions to file
    void saveTransactions() {
        ofstream file(fileName);
        if (file.is_open()) {
            for (const auto& txn : transactions) {
                file << txn.description << endl;
                file << txn.amount << endl;
                file << txn.category << endl;
                file << txn.date << endl;
            }
            file.close();
        }
    }

public:
    FinanceManager() {
        loadTransactions();  // Load transactions on startup
    }

    // Add transaction
    void addTransaction(const string& desc, float amt, const string& category) {
        transactions.push_back(Transaction(desc, amt, category));
        saveTransactions();
    }

    // Display all transactions
    void displayTransactions() const {
        if (transactions.empty()) {
            cout << "No transactions found." << endl;
            return;
        }

        cout << "\nTransactions:\n";
        cout << left << setw(20) << "Description" 
             << setw(10) << "Amount" 
             << setw(15) << "Category" 
             << "Date" << endl;

        for (const auto& txn : transactions) {
            cout << left << setw(20) << txn.description
                 << setw(10) << fixed << setprecision(2) << txn.amount
                 << setw(15) << txn.category
                 << txn.date << endl;
        }
    }

    // View balance
    void viewBalance() const {
        float balance = 0.0;
        for (const auto& txn : transactions) {
            balance += txn.amount;
        }

        cout << "\nCurrent Balance: " << fixed << setprecision(2) << balance << endl;
    }

    // Generate report by category
    void generateCategoryReport() const {
        if (transactions.empty()) {
            cout << "No transactions to report." << endl;
            return;
        }

        cout << "\nCategory-wise Summary:\n";
        map<string, float> categorySummary;

        for (const auto& txn : transactions) {
            categorySummary[txn.category] += txn.amount;
        }

        cout << left << setw(15) << "Category" << "Total Amount" << endl;
        for (const auto& entry : categorySummary) {
            cout << left << setw(15) << entry.first 
                << fixed << setprecision(2) << entry.second << endl;
        }
    }

    // Delete transaction by description
    void deleteTransaction(const string& desc) {
        auto it = remove_if(transactions.begin(), transactions.end(), [&desc](const Transaction& txn) {
            return txn.description == desc;
        });

        if (it != transactions.end()) {
            transactions.erase(it, transactions.end());
            saveTransactions();
            cout << "Transaction deleted." << endl;
        } else {
            cout << "Transaction not found." << endl;
        }
    }
};

void displayMenu() {
    cout << "\nPersonal Finance Manager Menu:\n";
    cout << "1. Add Transaction\n";
    cout << "2. Display Transactions\n";
    cout << "3. View Balance\n";
    cout << "4. Generate Category Report\n";
    cout << "5. Delete Transaction\n";
    cout << "6. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    FinanceManager fm;
    int choice;
    string description, category;
    float amount;

    while (true) {
        displayMenu();
        cin >> choice;

        cin.ignore();  // To ignore newline after choice

        switch (choice) {
            case 1:
                cout << "Enter description: ";
                getline(cin, description);
                cout << "Enter amount: ";
                cin >> amount;
                cin.ignore();  // Ignore newline after amount
                cout << "Enter category: ";
                getline(cin, category);
                fm.addTransaction(description, amount, category);
                break;

            case 2:
                fm.displayTransactions();
                break;

            case 3:
                fm.viewBalance();
                break;

            case 4:
                fm.generateCategoryReport();
                break;

            case 5:
                cout << "Enter description of transaction to delete: ";
                getline(cin, description);
                fm.deleteTransaction(description);
                break;

            case 6:
                cout << "Exiting program." << endl;
                return 0;

            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
