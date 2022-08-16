/*
Group names:
Description
Compilation: g++ cipher.cpp -o cipher
Run guide: ./cipher -enc/-dec inFile.bmp [optional: outFile.bmp]
*/

#include <iostream>
#include <vector>
#include "functions.h"
#include "types.h"

using namespace std;

int main()
{
    // TODO: input processing and validation (+check file's encryption and decryption status)
    char choice;
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
    getline(cin, FILENAME);
    BitMapPicture BMP(FILENAME);

    // TODO: password confirmation (if password is not configured, prompt user for entering the password)

    // TODO: generate key

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