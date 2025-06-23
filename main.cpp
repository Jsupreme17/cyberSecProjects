#include <iostream>
#include <fstream> // file opening
#include <cstdio> // for remove() and rename()

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

bool loginUser(string& currentUser) {
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
            currentUser = username;
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

void changePassword(const string& username) {
    string storedUsername, storedPassword, newPassword;
    ifstream file("usersInfo.txt");
    ofstream temp("temporary.txt");

    if (!file || !temp) {
        cout << "Error opening file.\n";
        return;
    }

    while (file >> storedUsername >> storedPassword) {
        if (storedUsername == username) {
            cout << "Enter new password: ";
            cin >> newPassword;
            temp << storedUsername << " " << newPassword << endl;
        } else {
            temp << storedUsername << " " << storedPassword << endl;
        }
    }

    file.close();
    temp.close();

    remove("usersInfo.txt");
    rename("temporary.txt", "usersInfo.txt");

    cout << "Password changed successfully.\n";
}

void deleteAccount(const string& username) {
    string storedUsername, storedPassword;
    ifstream file("usersInfo.txt");
    ofstream temp("temporary.txt");

    if (!file || !temp) {
        cout << "Error opening file.\n";
        return;
    }

    while (file >> storedUsername >> storedPassword) {
        if (storedUsername != username) {
            temp << storedUsername << " " << storedPassword << endl;
        }
    }

    file.close();
    temp.close();

    remove("usersInfo.txt");
    rename("temporary.txt", "usersInfo.txt");

    cout << "Account deleted successfully.\n";
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

            case 2: {
                string currentUser;
                if (loginUser(currentUser)) {
                    int choice;
                    bool loggedIn = true;

                    while (loggedIn) {
                        cout << "\n--- Logged In Menu ---\n";
                        cout << "1. View Welcome Message\n";
                        cout << "2. Change Password\n";
                        cout << "3. Delete Account\n";
                        cout << "4. Logout\n";
                        cout << "Enter your choice: ";
                        cin >> choice;

                        switch (choice) {
                            case 1:
                                cout << "Welcome! You are now logged in.\n";
                                break;
                            case 2:
                                changePassword(currentUser);
                                break;
                            case 3:
                                deleteAccount(currentUser);
                                loggedIn = false; // auto logout
                                break;
                            case 4:
                                cout << "Logging out...\n";
                                loggedIn = false;
                                break;
                            default:
                                cout << "Invalid option. Try again.\n";
                        }
                    }
                }
                break;
            }

            case 3:
                cout << "Goodbye!\n";
                return 0;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}

