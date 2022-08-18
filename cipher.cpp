/*
Group names:
Description
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <utility>
#include "types.h"

using namespace std;

void print_menu();
int get_file_name(string &FILENAME);
void get_input_choice(int &choice);

int main()
{
    print_menu();

    // Prompt user for choice and validate user input choice
    int choice;
    get_input_choice(choice);

    // Interpret user's choice
    string option = choice == 1 ? "encrypt" : "decrypt";

    // Prompt user for filename and check if it can be openned
    string FILENAME;
    if (get_file_name(FILENAME) == false)
    {
        cout << endl << "file cannot be openned\n" << endl; 
        return 1;
    }

    // Validate its enc/dec status
    BitMapPicture BMP(FILENAME);
    if (BMP.encrypt_option_validation(FILENAME, option) == true)
    {
        cout << "Operation is INVALID!" << endl;
        exit(0);
    }

    // Prompt user for password configuration if a password has not been signed up
    ifstream get_password("password.txt");
    string configured_password, user_entered_password;
    if (get_password.is_open())
    {
        get_password.seekg(0, ios::end);
        if (get_password.tellg() == 0)
        {
            ofstream put_password("password.txt", ios::app);
            string password;
            cout << "Please configure a new passsword: ";
            cin >> password;
            put_password << password << endl;
            put_password.close();
        }
        else
        {
            // Read password.txt file
            get_password.seekg(0, ios::beg);
            get_password >> configured_password;
            // Get password
            cout << "Enter the password: ";
            cin >> user_entered_password;
            if (configured_password != user_entered_password)
            {
                cout << "Wrong password!" << endl;
                get_password.close();
                exit(0);
            }
            get_password.close();
        }
    }

    // Read bitmap file picture into memory 
    BMP.read();

    // Generate key from the password
    pair <unsigned int, unsigned int> key_pairs = BMP.key_pairs_generator(configured_password);

    // Encrypt or decrypt the image
    switch (choice)
    {
        case 1:
            // Encryptthe the image
            BMP.cipherBMP(key_pairs.first, key_pairs.second, operationMode::encrypt);
            break;
        case 2: 
            // Decrypt the image
            BMP.cipherBMP(key_pairs.first, key_pairs.second, operationMode::decrypt);
            break;
    }
    
    // Write the pixels back to output bmp file
    BMP.write();
}

void print_menu()
{
    cout << "========= Ecryption & Decryption Program =========" << endl;
    cout << "[1]. Encryption" << endl
         << "[2]. Decryption" << endl
         << "\tEnter your choice: ";
}

int get_file_name(string &FILENAME)
{
    cout << "\tEnter file name (in the format of bmp): ";
    cin >> FILENAME;
    ifstream inputBMP(FILENAME);
    if (!inputBMP.is_open())
    {
        return 0;
    }
    return 1;
}

void get_input_choice(int &choice)
{
    bool input_err;
    do
    {
        input_err = false;
        cin >> choice;
        if (cin.fail() || (choice != 2 && choice != 1))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            input_err = true;
            cout << "\n\tInvalid input choice\n\n";
            cout << "\tEnter your choice: ";
        }
    }
    while (input_err);
}