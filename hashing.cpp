//with file handling
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <cmath>
using namespace std;

struct EncryptedPassword {
    string website;
    string username;
    string encryptedPassword;
    int e;
    int d;
    int n;
};

int findGCD(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int modExponentiation(int base, int exponent, int modulus) {
    if (modulus == 1) {
        return 0;
    }

    int result = 1;
    base = base % modulus;

    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % modulus;
        }
        exponent = exponent >> 1; // Right-shift the exponent
        base = (base * base) % modulus;
    }

    return result;
}

string encryptWord(const string& word, int e, int n) {
    string encryptedWord;
    for (char c : word) {
        int M = static_cast<int>(c);
        int C = modExponentiation(M, e, n);
        encryptedWord += to_string(C) + " ";
    }
    return encryptedWord;
}

string decryptWord(const string& encryptedWord, int d, int n) {
    string decryptedWord = "";
    string token;
    istringstream iss(encryptedWord);
    while (getline(iss, token, ' ')) {
        int C = stoi(token);
        int M = modExponentiation(C, d, n);
        decryptedWord += static_cast<char>(M);
    }
    return decryptedWord;
}
bool containsSpace(const string& text) {
    for (char c : text) {
        if (c == ' ') {
            return true;
        }
    }
    return false;
}

int main() {
    string input;
    string website;
    string username;
    int p = 73;
    int q = 53;
    int n = p * q;
    int e = 2;
    int d = 1;

    // phi(n)=(p-1)*(q-1)
    int phi = (p - 1) * (q - 1);

    for (d = 2; d < phi; d++) {
        if (findGCD(d, phi) == 1) {
            break;
        }
    }
    for (e = 2; e < phi; e++) {
        if ((e * d) % phi == 1) {
            break;
        }
    }

    // Database created (vector)
    vector<EncryptedPassword> passwordDatabase;

    // Reading from the file
    ifstream readfile("passwords.txt");
    if (readfile.is_open()) {
        string line;
        while (getline(readfile, line)) {
            EncryptedPassword entry;
            string rwebsite;
            string rusername;
            string rencrypted;
            int r_e = 0;
            int r_d = 0;
            int r_n = 0;
            int count=0;
            for (char c : line) {
                if (c == ',') {
                    count++;
                    continue;
                }
                if (count == 0) {
                    rwebsite += c;
                } else if (count == 1) {
                    rusername += c;
                }else if (count == 2) {
                    rencrypted += c;
                }
                else if (count == 3) {
                    r_e = r_e * 10 + (c-'0');
                } else if (count == 4) {
                    r_d = r_d * 10 + (c - '0');
                } else if (count == 5) {
                    r_n = r_n * 10 + (c - '0');
                }
            }

            entry.website=rwebsite;
            entry.username = rusername;
            entry.encryptedPassword = rencrypted;
            entry.e = r_e;
            entry.d = r_d;
            entry.n = r_n;
            passwordDatabase.push_back(entry);
        }
        readfile.close(); // Close the file after reading
    }

//    for (const EncryptedPassword &entry: passwordDatabase) {
//        std::cout << "Name: " << entry.username << std::endl;
//        std::cout << "Encrypted Password: " << entry.encryptedPassword << std::endl;
//        std::cout << "e: " << entry.e << std::endl;
//        std::cout << "d: " << entry.d << std::endl;
//        std::cout << "n: " << entry.n << std::endl;
//        std::cout << std::endl; // Add a newline for separation
//    }
    bool flag=true;
    while (flag) {
        cout << "-----------WELCOME TO ECHOCRYPT MANAGER---------" << endl;
        cout<<""<<endl;
        cout << "----------MENU----------" << endl;
        cout << "1. Enter a password" << endl;
        cout << "2. Find password" << endl;
        cout << "3. Delete a password" << endl;
        cout << "4. Save&Exit" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        bool success = false;


        if (choice == 1) {
            cout << "Enter the website name: ";
            cin.ignore();  // Clear the newline character from the buffer
            getline(cin, website);
            cout << "Enter your username: ";
            getline(cin, username);
            try {
                do {
                    cout << "Enter a Password (without spaces): ";
                    getline(cin, input);
                    if (containsSpace(input)) {
                        flag = false;
                        throw runtime_error("Error: Password should not contain spaces.");

                    }
                } while (containsSpace(input));

                // Encryption
                string encryptedWord = encryptWord(input, e, n);

                // Storing in the class object
                EncryptedPassword userEntry;
                userEntry.website=website;
                userEntry.username = username;
                userEntry.encryptedPassword = encryptedWord;
                userEntry.e = e;
                userEntry.d = d;
                userEntry.n = n;
                passwordDatabase.push_back(userEntry);

                cout << "Encrypted Password: " << encryptedWord << endl;
            } catch (const runtime_error &e) {
                cerr << e.what() << endl;
            }
        }

        if (choice == 2) {
            cout<<"Enter Website: ";
            cin>>website;
            cout << "Enter username: ";
            cin >> username;
            // Decryption
            for (const EncryptedPassword& storedPassword : passwordDatabase) {
                if (website == storedPassword.website && username == storedPassword.username) {
                    string decryptedPassword = decryptWord(storedPassword.encryptedPassword, storedPassword.d,
                                                           storedPassword.n);
                    cout<<"\nWebsite: "<<storedPassword.website<<endl;
                    cout << "User Name: " << storedPassword.username << endl;
                    cout << "Decrypted password: " << decryptedPassword << endl;
                    success = true;
                }
            }
            if (!success) {
                cout << "Password not found / Incorrect details entered" << endl;
            }
        }

        if (choice == 3) {
            cout << "Enter website name: ";
            cin >> website;
            cout << "Enter username: ";
            cin >> username;

            for (int i = 0; i < passwordDatabase.size(); i++) {
                if (website == passwordDatabase[i].website && username == passwordDatabase[i].username) {
                    passwordDatabase.erase(passwordDatabase.begin() + i);
                    cout << "Password deleted" << endl;
                    success = true;
                }
            }

            if (!success) {
                cout << "Password not found" << endl;
            }
        }

        if (choice == 4) {
            // Open the file for overwriting
            ofstream overwritefile("passwords.txt", ios::trunc);
            if (overwritefile.is_open()) {
                for (const EncryptedPassword& entry : passwordDatabase) {
                    overwritefile << entry.website<<","<<entry.username << "," << entry.encryptedPassword << "," << entry.e << "," << entry.d << ","
                                  << entry.n << endl;
                }
                overwritefile.close(); // Close the file after writing
                cout << "File saved successfully" << endl;
            }
            break;
        }
    }

    cout << "Program exited successfully" << endl;
    return 0;

}