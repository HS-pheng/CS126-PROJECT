/*
Group names:
Description
Compilation: g++ cipher.cpp -o cipher
Run guide: ./cipher -enc/-dec inFile.bmp [optional: outFile.bmp]
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include "functions.h"
#include "types.h"

using namespace std;

bool encrypt_option_validation(string FILENAME, string option)
{
}

int main()
{
    // TODO: input processing and validation (+check file's encryption and decryption status)
    int choice;
    string password, configured_password, e_d_password;
    string option;
    string FILENAME;

    ifstream fin("password.txt");
    ofstream fout("password.txt", ios::app);
    if (fin.is_open())
    {
        fin.seekg(0, ios::end);
        if (fin.tellg() == 0)
        {
            string password;
            cout << "Please configure a passsword: ";
            cin >> password;
            fout << password << endl;
        }
    }

    cout << "========= Ecryption & Decryption Program =========" << endl;
    cout << "[1]. Encryption" << endl
         << "[2]. Decryption" << endl
         << "\tEnter your choice: ";
    cin >> choice;

    if (choice > 2 or choice < 1)
    {
        cout << "Invalid input! Please enter the choice in NUMBER!" << endl;
        main();
    }

    switch (choice)
    {
    case 1:
        option = "encrypt";
        break;
    case 2:
        option = "decrypt";
        break;
    }

    cout << "Enter file name (in the format of bmp): ";
    cin >> FILENAME;

    BitMapPicture BMP(FILENAME);

    if (BMP.encrypt_option_validation(FILENAME, option) == true)
    {
        cout << "Operation is INVALID!" << endl;
        exit(0);
    }

    // TODO: password confirmation (if password is not configured, prompt user for entering the password)

    // TODO: read bitmap file picture + file format validation
    BMP.read();

    //read password.txt file
    ifstream get_password("password.txt");
    // TODO: encryption or decryption
    switch (choice)
    {
    case 1:

        get_password >> configured_password;
        // get password
        cout << "Enter the password: ";
        cin >> e_d_password;
        if (configured_password != e_d_password)
        {
            cout << "Wrong password!" << endl;
            exit(0);
        }
        
        // encryption function
        BMP.cipherBMP(BMP.key_generator(configured_password), 123, operationMode::encrypt);

        break;
    case 2:
       
        get_password >> configured_password;
        //get password
        cout << "Enter the password: ";
        cin >> e_d_password;
        if (configured_password != e_d_password)
        {
            cout << "Wrong password!" << endl;
            exit(0);
        }
        get_password.close();

        string e_skey = BMP.read_key(configured_password);
        int e_ikey = atoi(e_skey.c_str()); // convert key from string to int
        BMP.cipherBMP(e_ikey, 123, operationMode::decrypt);

        break;
    }
    

    // TODO: write the pixels back to output bmp file
    BMP.write();
}