#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

// Function to encrypt or decrypt a password using XOR encryption
string xorEncryptDecrypt(const string& input, const string& key) {
    string output = input;
    for (size_t i = 0; i < input.size(); ++i) {
        output[i] ^= key[i % key.size()]; // XOR each character with the key
    }
    return output;
}

// Add a new user to the manager
void addUser(unordered_map<string, unordered_map<string, string>>& manager) {
    string username;
    cout << "Enter the username to add: ";
    cin >> username;
    if (manager.find(username) == manager.end()) {
        unordered_map<string, string> userPasswords;
        manager[username] = userPasswords;
        cout << "User " << username << " added successfully.\n";
    } else {
        cout << "User " << username << " already exists.\n";
    }
}

// List all users
void listUsers(const unordered_map<string, unordered_map<string, string>>& manager) {
    cout << "Users list:\n";
    for (const auto& user : manager) {
        cout << user.first << endl;
    }
}

// Manage passwords for a specific user
void managePasswords(string username, unordered_map<string, unordered_map<string, string>>& manager) {
    while (true) {
        cout << "Managing passwords for " << username << ":\n";
        cout << "1. Store an encrypted password\n";
        cout << "2. List all sites and passwords\n";
        cout << "3. Retrieve an unencrypted password\n";
        //cout << "4. Delete a site\n";
        cout << "4. Exit\n";
        
        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                string site, password, key;
                cout << "Enter the site: ";
                cin >> site;
                cout << "Enter the password: ";
                cin >> password;
                cout << "Enter the encryption key: ";
                cin >> key;
                string encrypted = xorEncryptDecrypt(password, key);
                manager[username][site] = encrypted;
                cout << "Password for " << site << " encrypted and stored.\n";
                break;
            }
            case 2: {
                cout << "Stored sites and encrypted passwords:\n";
                for (const auto& entry : manager[username]) {
                    cout << "Site: " << entry.first << ", Password: " << entry.second << endl;
                }
                break;
            }
            case 3: {
                string site, key;
                cout << "Enter the site: ";
                cin >> site;
                cout << "Enter the encryption key: ";
                cin >> key;
                if (manager[username].find(site) != manager[username].end()) {
                    string encryptedPassword = manager[username][site];
                    string decryptedPassword = xorEncryptDecrypt(encryptedPassword, key);
                    cout << "Password for " << site << " is: " << decryptedPassword << endl;
                } else {
                    cout << "Site not found.\n";
                }
                break;
            }
            
            case 4:
                return;
            default:
                cout << "Invalid choice, try again.\n";
        }
    }
}

// Main program loop
int main() {
    unordered_map<string, unordered_map<string, string>> manager;
    
    while (true) {
        cout << "Enter an action:\n";
        cout << "1. Add a user\n";
        cout << "2. List all users\n";
        cout << "3. Manage a user's passwords\n";
        cout << "4. Exit\n";
        
        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                addUser(manager);
                break;
            }
            case 2: {
                listUsers(manager);
                break;
            }
            case 3: {
                string username;
                cout << "Enter the username: ";
                cin >> username;
                if (manager.find(username) != manager.end()) {
                    managePasswords(username, manager);
                } else {
                    cout << "Invalid username.\n";
                }
                break;
            }
            case 4:
                cout << "Exiting program.\n";
                return 0;
            default:
                cout << "Invalid choice, try again.\n";
        }
    }
}

