#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class Book {
public:
    string name;
    int quantity;

    // Default constructor
    Book() : name(""), quantity(0) {}

    // Parameterized constructor
    Book(string name, int quantity) : name(name), quantity(quantity) {}
};

class Librarian {
private:
    unordered_map<string, Book> books;
    vector<pair<string, pair<string, int>>> issuedBooks; // {username, {bookName, quantity}}

public:
    void addBook(const string& name, int quantity) {
        if (books.find(name) != books.end()) {
            books[name].quantity += quantity;
        } else {
            books[name] = Book(name, quantity);
        }
        cout << "Book added successfully!" << endl;
    }

    void checkBookQuantity() {
        cout << "Available Books:" << endl;
        for (const auto& pair : books) {
            cout << "Book: " << pair.second.name << ", Quantity: " << pair.second.quantity << endl;
        }
        cout << "Out of Stock Books:" << endl;
        for (const auto& pair : books) {
            if (pair.second.quantity == 0) {
                cout << "Book: " << pair.second.name << " is out of stock." << endl;
            }
        }
    }

    void checkIssuedBooks() {
        cout << "Issued Books:" << endl;
        for (const auto& entry : issuedBooks) {
            cout << ":User  " << entry.first << ", Book: " << entry.second.first << ", Quantity: " << entry.second.second << endl;
        }
    }

    void issueBook(const string& username, const string& bookName, int quantity) {
        if (books.find(bookName) != books.end() && books[bookName].quantity >= quantity) {
            books[bookName].quantity -= quantity;
            issuedBooks.push_back({username, {bookName, quantity}});
            cout << "Book issued successfully!" << endl;
        } else {
            cout << "Book not available or insufficient quantity!" << endl;
        }
    }
};

class User {
private:
    Librarian& librarian;

public:
    User(Librarian& lib) : librarian(lib) {}

    void issueBook(const string& username, const string& bookName, int quantity) {
        librarian.issueBook(username, bookName, quantity);
    }

    void checkAvailableBooks() {
        cout << "Available Books:" << endl;
        librarian.checkBookQuantity();
    }
};

int main() {
    Librarian librarian;
    User user(librarian);
    string username, password;
    int choice;

    while (true) {
        cout << "1. Librarian Login\n2. User Login\n3. Exit\nChoose an option: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter Librarian Username: ";
            cin >> username;
            cout << "Enter Password: ";
            cin >> password; // In a real application, you would check this against a secure store

            while (true) {
                cout << "1. Add Book\n2. Check Book Quantity\n3. Check Issued Books\n4. Logout\nChoose an option: ";
                cin >> choice;

                if (choice == 1) {
                    string bookName;
                    int quantity;
                    cout << "Enter Book Name: ";
                    cin >> bookName;
                    cout << "Enter Quantity: ";
                    cin >> quantity;
                    librarian.addBook(bookName, quantity);
                } else if (choice == 2) {
                    librarian.checkBookQuantity();
                } else if (choice == 3) {
                    librarian.checkIssuedBooks();
                } else if (choice == 4) {
                    break;
                } else {
                    cout << "Invalid option!" << endl;
                }
            }
        } else if (choice == 2) {
            cout << "Enter User Username: ";
            cin >> username;
            cout << "Enter Password: ";
            cin >> password; // In a real application, you would check this against a secure store

            while (true) {
                cout << "1. Issue Book\n2. Check Available Books\n3. Logout\nChoose an option: ";
                cin >> choice;

                if (choice == 1) {
                    string bookName;
                    int quantity;
                    cout << "Enter Book Name: ";
                    cin >> bookName;
                    cout << "Enter Quantity: ";
                    cin >> quantity;
                    user.issueBook(username, bookName, quantity);
                } else if (choice == 2) {
                    user.checkAvailableBooks();
                } else if (choice == 3) {
                    break; // Logout
                } else {
                    cout << "Invalid option!" << endl;
                }
            }
        } else if (choice == 3) {
            cout << "Exiting the system. Goodbye!" << endl;
            break; // Exit the program
        } else {
            cout << "Invalid option! Please try again." << endl;
        }
    }

    return 0;
}
