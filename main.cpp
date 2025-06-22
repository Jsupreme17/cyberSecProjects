#include <iostream>
#include <fstream>
using namespace std;

// ---- FUNCTION DEFINITIONS ----
void registerUser() {
    string username, password;
    cout << "Enter a new username: ";
    cin >> username;
    cout << "Enter a new password: ";
    cin >> password;

    ofstream file("usersInfo.txt", ios::app);
    if (file.is_open()) {
        file << username << " " << password << endl;
        file.close();
        cout << "Registration successful.\n";
    } else {
        cout << "Error: Unable to open file.\n";
    }
}

bool loginUser() {
    string username, password;
    cout << "Login Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    ifstream file("usersInfo.txt");
    string storedUsername, storedPassword;
    bool loginSuccess = false;

    while (file >> storedUsername >> storedPassword) {
        if (username == storedUsername && password == storedPassword) {
            loginSuccess = true;
            break;
        }
    }

    file.close();

    if (loginSuccess) {
        cout << "Login successful!\n";
    } else {
        cout << "Login failed, invalid username or password.\n";
    }

    return loginSuccess;
}

// ---- MAIN PROGRAM ----
int main() {
    int num;

    while (true) {
        cout << "\nWelcome! Are you an existing user or would you like to register?\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> num;

        switch (num) {
            case 1:
                registerUser();
                break;

            case 2:
                if (loginUser()) {
                    int choice;
                    do {
                        cout << "\n--- Log In Menu ---\n";
                        cout << "1. View Welcome Message\n";
                        cout << "2. Logout\n";
                        cout << "Enter your choice: ";
                        cin >> choice;

                        switch (choice) {
                            case 1:
                                cout << "Welcome! You are now logged in.\n";
                                break;
                            case 2:
                                cout << "Logging out...\n";
                                break;
                            default:
                                cout << "Invalid option. Try again.\n";
                        }
                    } while (choice != 2);
                }
                break;

            case 3:
                cout << "Goodbye!\n";
                return 0;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
