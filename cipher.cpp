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

int main()
{
    // TODO: input processing and validation (+check file's encryption and decryption status)
    int choice;
    string password;
    string option;
    string FILENAME;
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

    cout << "Enter file name (in the format of bmp): ";
    getline(cin, FILENAME);
    cin.clear();
    cin.ignore(1000, '\n');
    BitMapPicture BMP(FILENAME);

    switch (choice)
    {
    case 1:
        option = "encrypt";
        break;
    case 2:
        option = "decrypt";
        break;
    }

    if (BMP.encrypt_option_validation(FILENAME, option) == true)
    {
        cout << "File has already been used to " << option;
        exit(0);
    }
    
    // TODO: password confirmation (if password is not configured, prompt user for entering the password)
    cout << "\nEnter the password: ";
    cin >> password;

    // TODO: generate key

   
    // TODO: read bitmap file picture + file format validation
    BMP.read();

    // TODO: encryption or decryption
    switch (choice)
    {
    case '1':
        BMP.cipherBMP(BMP.key_generator(password), 123, operationMode::encrypt);
        break;
    case '2':

        string e_skey = BMP.read_key(password);
        int e_ikey = atoi(e_skey.c_str());      //convert key from integer to string
        BMP.cipherBMP(e_ikey, 123, operationMode::decrypt);
        break;
    }

    // TODO: write the pixels back to output bmp file
    BMP.write();
}