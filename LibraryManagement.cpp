#include <iostream>
#include <string>
#include <ctime>

using namespace std;

const int MAX_BOOKS = 100;
const int MAX_BORROWERS = 50;
const int MAX_TRANSACTIONS = 200;

class Book {
public:
    string title;
    string author;
    string ISBN;
    bool isAvailable;

    Book() : title(""), author(""), ISBN(""), isAvailable(true) {}

    void setBookDetails(string t, string a, string i) {
        title = t;
        author = a;
        ISBN = i;
        isAvailable = true;
    }
};

class Borrower {
public:
    string name;
    string borrowerID;

    Borrower() : name(""), borrowerID("") {}

    void setBorrowerDetails(string n, string id) {
        name = n;
        borrowerID = id;
    }
};

class Transaction {
public:
    string ISBN;
    string borrowerID;
    time_t checkoutDate;
    bool isReturned;

    Transaction() : ISBN(""), borrowerID(""), checkoutDate(0), isReturned(false) {}

    void setTransactionDetails(string isbn, string id) {
        ISBN = isbn;
        borrowerID = id;
        time(&checkoutDate);
        isReturned = false;
    }
};

class Library {
private:
    Book books[MAX_BOOKS];
    Borrower borrowers[MAX_BORROWERS];
    Transaction transactions[MAX_TRANSACTIONS];
    int bookCount;
    int borrowerCount;
    int transactionCount;

public:
    Library() : bookCount(0), borrowerCount(0), transactionCount(0) {}

    void addBook(string title, string author, string ISBN) {
        if (bookCount < MAX_BOOKS) {
            books[bookCount].setBookDetails(title, author, ISBN);
            bookCount++;
        } else {
            cout << "Library is full, cannot add more books." << endl;
        }
    }

    void addBorrower(string name, string borrowerID) {
        if (borrowerCount < MAX_BORROWERS) {
            borrowers[borrowerCount].setBorrowerDetails(name, borrowerID);
            borrowerCount++;
        } else {
            cout << "Borrower list is full, cannot add more borrowers." << endl;
        }
    }

    void searchBook(string query) {
        for (int i = 0; i < bookCount; i++) {
            if (books[i].title == query || books[i].author == query || books[i].ISBN == query) {
                cout << "Book Found: " << books[i].title << " by " << books[i].author << " (ISBN: " << books[i].ISBN << ")" << endl;
                return;
            }
        }
        cout << "Book not found." << endl;
    }

    void checkoutBook(string ISBN, string borrowerID) {
        for (int i = 0; i < bookCount; i++) {
            if (books[i].ISBN == ISBN) {
                if (books[i].isAvailable) {
                    books[i].isAvailable = false;
                    if (transactionCount < MAX_TRANSACTIONS) {
                        transactions[transactionCount].setTransactionDetails(ISBN, borrowerID);
                        transactionCount++;
                        cout << "Book checked out successfully." << endl;
                    } else {
                        cout << "Transaction log is full, cannot checkout more books." << endl;
                    }
                } else {
                    cout << "Book is currently unavailable." << endl;
                }
                return;
            }
        }
        cout << "Book not found." << endl;
    }

    void returnBook(string ISBN) {
        for (int i = 0; i < bookCount; i++) {
            if (books[i].ISBN == ISBN) {
                books[i].isAvailable = true;
                for (int j = 0; j < transactionCount; j++) {
                    if (transactions[j].ISBN == ISBN && !transactions[j].isReturned) {
                        transactions[j].isReturned = true;
                        cout << "Book returned successfully." << endl;
                        return;
                    }
                }
            }
        }
        cout << "Book not found." << endl;
    }

    void calculateFine(string borrowerID, int maxDays) {
        for (int i = 0; i < transactionCount; i++) {
            if (transactions[i].borrowerID == borrowerID && !transactions[i].isReturned) {
                time_t now;
                time(&now);
                int daysOverdue = (now - transactions[i].checkoutDate) / (60 * 60 * 24) - maxDays;
                if (daysOverdue > 0) {
                    cout << "Fine for borrower " << borrowerID << " is $" << daysOverdue << endl;
                } else {
                    cout << "No fine for borrower " << borrowerID << endl;
                }
                return;
            }
        }
        cout << "No active transactions found for borrower " << borrowerID << endl;
    }
};

int main() {
    Library library;
    int choice;
    string title, author, ISBN, borrowerID, name;
    int maxDays;

    do {
        cout << "\nLibrary Management System\n";
        cout << "1. Add Book\n";
        cout << "2. Add Borrower\n";
        cout << "3. Search Book\n";
        cout << "4. Checkout Book\n";
        cout << "5. Return Book\n";
        cout << "6. Calculate Fine\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter book title: ";
                cin.ignore();
                getline(cin, title);
                cout << "Enter book author: ";
                getline(cin, author);
                cout << "Enter book ISBN: ";
                getline(cin, ISBN);
                library.addBook(title, author, ISBN);
                break;

            case 2:
                cout << "Enter borrower name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter borrower ID: ";
                getline(cin, borrowerID);
                library.addBorrower(name, borrowerID);
                break;

            case 3:
                cout << "Enter book title, author, or ISBN to search: ";
                cin.ignore();
                getline(cin, title);
                library.searchBook(title);
                break;

            case 4:
                cout << "Enter book ISBN: ";
                cin.ignore();
                getline(cin, ISBN);
                cout << "Enter borrower ID: ";
                getline(cin, borrowerID);
                library.checkoutBook(ISBN, borrowerID);
                break;

            case 5:
                cout << "Enter book ISBN: ";
                cin.ignore();
                getline(cin, ISBN);
                library.returnBook(ISBN);
                break;

            case 6:
                cout << "Enter borrower ID: ";
                cin.ignore();
                getline(cin, borrowerID);
                cout << "Enter maximum days allowed for borrowing: ";
                cin >> maxDays;
                library.calculateFine(borrowerID, maxDays);
                break;

            case 7:
                cout << "Exiting the system. Goodbye!" << endl;
                break;

            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
    } while (choice != 7);

    return 0;
}