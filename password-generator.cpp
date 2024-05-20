#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

string generateRandomString(int length) {
    const string CHARACTERS = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOOPASDFGHJKLZXCVBNM1234567890";
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<> distribution(0, CHARACTERS.size() - 1);

    string random_string;
    for (int i = 0; i < length; ++i) {
        random_string += CHARACTERS[distribution(generator)];
    }

    return random_string;
}

void generatePasswords(vector<string>& passwords, int length, int count) {
    passwords.clear();
    for (int i = 0; i < count; ++i) {
        passwords.push_back(generateRandomString(length));
    }
}

void displayPasswords(const vector<string>& passwords) {
    for (size_t i = 0; i < passwords.size(); ++i) {
        cout << i + 1 << ". " << passwords[i] << endl;
    }
}

void saveSelectedPasswords(const vector<string>& passwords) {
    vector<int> selections;
    int selection;
    cout << "Enter the numbers of the passwords you want to save (separated by spaces, end with 0): ";
    while (cin >> selection && selection != 0) {
        selections.push_back(selection - 1);
    }

    ofstream outfile("passwords.txt");
    for (int index : selections) {
        string login, purpose;
        cout << "Enter login for password " << passwords[index] << ": ";
        cin >> login;
        cout << "Enter purpose for password " << passwords[index] << ": ";
        cin >> purpose;
        outfile << "Password: " << passwords[index] << ", Login: " << login << ", Purpose: " << purpose << endl;
    }
    outfile.close();
    cout << "Selected passwords saved to passwords.txt" << endl;
}

void settings(int& passwordLength, int& passwordCount) {
    cout << "Current password length: " << passwordLength << endl;
    cout << "Current number of passwords to generate: " << passwordCount << endl;
    cout << "Enter new password length: ";
    cin >> passwordLength;
    cout << "Enter new number of passwords to generate: ";
    cin >> passwordCount;
}

int main() {
    int passwordLength = 21;
    int passwordCount = 5;
    vector<string> passwords;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Display passwords\n";
        cout << "2. Generate new passwords\n";
        cout << "3. Save selected passwords\n";
        cout << "4. Settings\n";
        cout << "5. Exit\n";
        cout << "Choose an option: ";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            displayPasswords(passwords);
            break;
        case 2:
            generatePasswords(passwords, passwordLength, passwordCount);
            displayPasswords(passwords);
            break;
        case 3:
            saveSelectedPasswords(passwords);
            break;
        case 4:
            settings(passwordLength, passwordCount);
            break;
        case 5:
            cout << "Exiting...\n";
            return 0;
        default:
            cout << "Invalid choice, please try again.\n";
            break;
        }
    }

    return 0;
}
