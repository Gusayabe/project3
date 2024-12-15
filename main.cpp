/*
    Created By Gustavo Ayala Berdecia 840-22-2830
               Juan Rodriguez
    Project 3 - Password Manager
    CCOM4005-ME5/M10-24-I


*/

#include <iostream>
#include <unordered_map>
#include <string>

/*
    Password Manager implements a password manager system that allows users to securely store and manage passwords 
    using XOR encryption. It utilizes a nested unordered_map to store user data, where each username maps to 
    another map of website-password pairs. The logic follows a menu-driven approach, offering functionalities 
    like adding and deleting users, managing passwords, and encrypting or decrypting passwords for various websites. 
    The xorEncryptDecrypt function uses XOR to either encrypt or decrypt passwords based on a provided key, 
    making it a symmetric encryption method. The program continuously loops, providing a user-friendly interface 
    for interaction, and performs actions based on user input. Passwords are stored in an encrypted form, and 
    the user can retrieve them by decrypting them with the correct key. The code ensures that the system remains 
    interactive and flexible, allowing for the management of multiple users and their passwords in a secure manner.
*/

using namespace std;

 /*
    xorEncryptDecrypt performs XOR encryption or decryption on a given string using a provided key. 
    Each character in the input string is XORed with a corresponding character from the key, 
    cycling through the key as needed. This ensures that the same function 
    can both encrypt and decrypt since XORing twice with the 
    same key reverses the operation.
*/
string xorEncryptDecrypt(const string& input, const string& key) {
    string output = input;
    // Loop through each character of the input string
    for (size_t i = 0; i < input.size(); ++i) {
        // XOR each character with a corresponding character from the key (repeated cyclically)
        output[i] ^= key[i % key.size()];
    }
    return output; // Return the transformed string
}

/*
    DeleteUser removes a user and all their stored data from the password manager. 
    It first checks if the provided username exists in the manager map and deletes 
    the entry if found. If the username doesn't exist, it notifies the 
    user that the account was not found.
*/
void deleteUser(unordered_map<string, unordered_map<string, string>>& manager) {
    string username;
    cout << "Enter the username to delete: ";
    cin >> username;
    // Check if the user exists in the manager
    if (manager.find(username) != manager.end()) {
        manager.erase(username); // Remove the user and their associated data
        cout << "User " << username << " deleted successfully.\n";
    } else {
        cout << "User " << username << " does not exist.\n"; // Inform if the user doesn't exist
    }
}

/*
    addUser adds a new user to the password manager. It checks if the username already exists; 
    if not, it initializes an empty map for storing the user's passwords. If the username 
    is already present, it informs the user that the account already exists.
*/
void addUser(unordered_map<string, unordered_map<string, string>>& manager) {
    string username;
    cout << "Enter the username to add: ";
    cin >> username;
    // Check if the user already exists
    if (manager.find(username) == manager.end()) {
        unordered_map<string, string> userPasswords; // Create an empty password map for the new user
        manager[username] = userPasswords; // Add the new user
        cout << "User " << username << " added successfully.\n";
    } else {
        cout << "User " << username << " already exists.\n"; // Inform if the user already exists
    }
}

/*
    listUsers lists all usernames currently stored in the password manager. It iterates 
    through the keys in the manager map and prints each username. This allows 
    the user to see all existing accounts in the system.
*/
void listUsers(const unordered_map<string, unordered_map<string, string>>& manager) {
    cout << "Users list:\n";
    // Iterate through all users and print their usernames
    for (const auto& user : manager) {
        cout << user.first << endl;
    }
}

/*
    managePasswords manages passwords for a specific user, offering multiple options such as storing, retrieving, or deleting passwords. 
    It provides a menu-driven interface for operations like encrypting and storing a password, listing all saved passwords, 
    decrypting a password for a specific site, or removing a site's password. The function loops until the user chooses 
    to exit, ensuring continuous access to password management features.
*/
void managePasswords(string username, unordered_map<string, unordered_map<string, string>>& manager) {
    while (true) {
        // Display options for managing passwords
        cout << "Managing passwords for " << username << ":\n";
        cout << "1. Store an encrypted password\n";
        cout << "2. List all sites and passwords\n";
        cout << "3. Retrieve an unencrypted password\n";
        cout << "4. Delete a site\n";
        cout << "5. Exit\n";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                // Store a new encrypted password
                string site, password, key;
                cout << "Enter the site: ";
                cin >> site;
                cout << "Enter the password: ";
                cin >> password;
                cout << "Enter the encryption key: ";
                cin >> key;
                // Encrypt the password using the XOR encryption function
                string encrypted = xorEncryptDecrypt(password, key);
                manager[username][site] = encrypted; // Store the encrypted password
                cout << "Password for " << site << " encrypted and stored.\n";
                break;
            }
            case 2: {
                // List all stored sites and encrypted passwords for the user
                cout << "Stored sites and encrypted passwords:\n";
                for (const auto& entry : manager[username]) {
                    cout << "Site: " << entry.first << ", Password: " << entry.second << endl;
                }
                break;
            }
            case 3: {
                // Retrieve and decrypt a password for a specific site
                string site, key;
                cout << "Enter the site: ";
                cin >> site;
                cout << "Enter the encryption key: ";
                cin >> key;
                // Check if the site exists for the user
                if (manager[username].find(site) != manager[username].end()) {
                    string encryptedPassword = manager[username][site];
                    // Decrypt the password using the same key
                    string decryptedPassword = xorEncryptDecrypt(encryptedPassword, key);
                    cout << "Password for " << site << " is: " << decryptedPassword << endl;
                } else {
                    cout << "Site not found.\n"; // Inform if the site doesn't exist
                }
                break;
            }
            case 4: {
                // Delete a password for a specific site
                string site;
                cout << "Enter the site to delete: ";
                cin >> site;
                // Check if the site exists
                if (manager[username].find(site) != manager[username].end()) {
                    manager[username].erase(site); // Remove the site and its associated password
                    cout << "Site " << site << " deleted successfully.\n";
                } else {
                    cout << "Site not found.\n"; // Inform if the site doesn't exist
                }
                break;
            }
            case 5:
                return; // Exit the password management menu
            default:
                cout << "Invalid choice, try again.\n"; // Handle invalid inputs
        }
    }
}

/*
    The Main program loop , serves as the entry point and main control loop of the password manager program. It 
    displays a menu to the user for performing operations like adding users, listing users, managing passwords 
    and deleting users. Based on user input, it calls the appropriate function and continues running until 
    the user decides to exit the program.
*/
int main() {
    unordered_map<string, unordered_map<string, string>> manager; // Manager to store users and their password data

    while (true) {
        // Display the main menu options
        cout << "Enter an action:\n";
        cout << "1. Add a user\n";
        cout << "2. List all users\n";
        cout << "3. Manage a user's passwords\n";
        cout << "4. Delete User\n";
        cout << "5. Exit Program\n";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                addUser(manager); // Add a new user
                break;
            }
            case 2: {
                listUsers(manager); // List all users
                break;
            }
            case 3: {
                string username;
                cout << "Enter the username: ";
                cin >> username;
                // Check if the username exists
                if (manager.find(username) != manager.end()) {
                    managePasswords(username, manager); // Manage passwords for the user
                } else {
                    cout << "Invalid username.\n"; // Inform if the user doesn't exist
                }
                break;
            }
            case 4:
                deleteUser(manager); // Delete a user
                break;
            case 5:
                cout << "Exiting program.\n";
                return 0; // Exit the program
            default:
                cout << "Invalid choice, try again.\n"; // Handle invalid inputs
        }
    }
}
