/*
Group names:
Description
Compilation: g++ cipher.cpp -o cipher
Run guide: ./cipher -enc/-dec inFile.bmp [optional: outFile.bmp]
*/

#include <iostream>
#include <vector>
#include <cmath>
#include "functions.h"
#include "types.h"

using namespace std;

int main()
{
    // TODO: input processing and validation (+check file's encryption and decryption status)
    char choice;
    char password[30];
    string FILENAME;
    cout << "========= Ecryption & Decryption Program =========" << endl;
    cout << "[1]. Encryption" << endl
         << "[2]. Decryption" << endl
         << "\tEnter your choice: ";
    cin >> choice;
    if (choice_validation(choice) == false)
    {
        cout << "Invalid input! Please enter the choice in NUMBER!" << endl;
        main();
    }

    cout << "Enter file name (in the format of bmp): ";
    cin >> FILENAME;
    BitMapPicture BMP(FILENAME);
    cin.clear();
    cin.ignore();
    // TODO: password confirmation (if password is not configured, prompt user for entering the password)
    cout << "\nEnter the new password for encryption: ";
    cin.getline(password, 30);
    // TODO: generate key
    BMP.key_generator(password);
    
    // TODO: read bitmap file picture + file format validation
    BMP.read();

    // TODO: encryption or decryption
    switch (choice)
    {
    case '1':
        BMP.cipherBMP(321, 123, operationMode::encrypt);
        break;
    case '2':
        BMP.cipherBMP(321, 123, operationMode::decrypt);
        break;
    }

    // TODO: write the pixels back to output bmp file
    BMP.write();
    
}