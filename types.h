#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <map>
#include <sstream>
using namespace std;

typedef uint8_t BYTE;
typedef uint32_t DWORD;
typedef int32_t LONG;
typedef uint16_t WORD;

// Define BITMAPFILEHEADER struct
typedef struct
{
    WORD bfType;
    DWORD bfSize;
    WORD bfReserved1;
    WORD bfReserved2;
    DWORD bfOffBits;
} __attribute__((__packed__))
BITMAPFILEHEADER;

// Define BITMAPINFOHEADER struct
typedef struct
{
    DWORD biSize;
    LONG biWidth;
    LONG biHeight;
    WORD biPlanes;
    WORD biBitCount;
    DWORD biCompression;
    DWORD biSizeImage;
    LONG biXPelsPerMeter;
    LONG biYPelsPerMeter;
    DWORD biClrUsed;
    DWORD biClrImportant;
} __attribute__((__packed__))
BITMAPINFOHEADER;

// Define the type of each pixel: RGBTRIPLE
typedef struct
{
    BYTE rgbtBlue;
    BYTE rgbtGreen;
    BYTE rgbtRed;
} RGBTRIPLE;

enum operationMode
{
    encrypt,
    decrypt
};

class BitMapPicture
{
public:
    unsigned int height;
    unsigned int width;
    string fileName;
    vector<RGBTRIPLE> rawPixels;
    BITMAPFILEHEADER bf;
    BITMAPINFOHEADER bi;
    unsigned int padding;

    BitMapPicture(string fileName)
    {
        this->fileName = fileName;
    };

    // Read from bitmapfile picture in a linear fashion
    void read()
    {
        fstream fin(fileName, ios::in);

        fin.read((char *)&bf, sizeof(BITMAPFILEHEADER));
        fin.read((char *)&bi, sizeof(BITMAPINFOHEADER));

        this->height = bi.biHeight;
        this->width = bi.biWidth;
        // Calculate extra padding
        padding = (4 - ((width * 3) % 4)) % 4;
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                RGBTRIPLE tmp;
                fin.read((char *)&tmp, sizeof(RGBTRIPLE));
                rawPixels.push_back(tmp);
            }
            fin.seekg(padding, ios::cur);
        }
    }
    // Write to bitmapfile picture
    void write()
    {
        fstream fout(fileName, ios::out);

        fout.write((char *)&bf, sizeof(BITMAPFILEHEADER));
        fout.write((char *)&bi, sizeof(BITMAPINFOHEADER));

        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                fout.write((char *)&rawPixels[(width * y) + x], sizeof(RGBTRIPLE));
            }
            for (int k = 0; k < padding; k++)
            {
                // Write null byte to complete padding
                fout.put(0x00);
            }
        }
        fout.close();
    }

    void generateRandomNumberArray(unsigned int R[])
    {
        unsigned int r = R[0];
        for (unsigned int k = 1; k < 2 * width * height; k++)
        {
            r = r ^ r << 13;
            r = r ^ r >> 17;
            r = r ^ r << 5;
            R[k] = r;
        }
    }

    void generateRandomPermutationArray(unsigned int P[], unsigned int R[])
    {
        unsigned int totalPixels = height * width;
        for (int i = 0; i < totalPixels; i++)
            P[i] = i;

        for (int i = totalPixels - 1; i >= 1; i--)
            swap(P[R[i] % i], P[i]);
    }

    void XORintegerXpixel(unsigned int integer, RGBTRIPLE &pixel)
    {
        unsigned char *c;
        c = (unsigned char *)&integer;
        pixel.rgbtBlue = (pixel.rgbtBlue) ^ (*c);
        c++;
        pixel.rgbtGreen = (pixel.rgbtGreen) ^ (*c);
        c++;
        pixel.rgbtRed = (pixel.rgbtRed) ^ (*c);
    }

    void XORpixelXpixel(RGBTRIPLE &pixel1, RGBTRIPLE pixel2)
    {
        pixel1.rgbtBlue = (pixel1.rgbtBlue) ^ (pixel2.rgbtBlue);
        pixel1.rgbtGreen = (pixel1.rgbtGreen) ^ (pixel2.rgbtGreen);
        pixel1.rgbtRed = (pixel1.rgbtRed) ^ (pixel2.rgbtRed);
    }

    void cipherBMP(unsigned int R0, unsigned int SV, operationMode mode)
    {
        unsigned int totalPixels = height * width;
        unsigned int *R = new unsigned int[2 * totalPixels];

        R[0] = R0;
        generateRandomNumberArray(R);

        unsigned int *P = new unsigned int[totalPixels];
        generateRandomPermutationArray(P, R);

        vector<RGBTRIPLE> tempPixels(rawPixels.begin(), rawPixels.end());

        if (mode == operationMode::encrypt)
        {
            // Permutate the pixels
            for (unsigned int i = 0; i < totalPixels; i++)
            {
                rawPixels[P[i]] = tempPixels[i];
            }

            // Encipher the permutated pixels
            for (unsigned int k = 0; k < totalPixels; k++)
            {
                XORintegerXpixel(SV, rawPixels[k]);
                XORintegerXpixel(R[(width * height) + k], rawPixels[k]);
            }

            ifstream e_file_validation("ED_validate.txt");

            map<string, string> m;
            while (!e_file_validation.eof())
            {
                string file_name;
                getline(e_file_validation, file_name);
                string status;
                getline(e_file_validation, status);
                m[file_name] = status;
            }
            e_file_validation.close();
            // for (auto e : m)
            // {
            //     cout << e.first << " " << e.second << endl;
            // }
            m[fileName] = "encrypt";
            fstream fout("ED_validate.txt", ios::out);
            stringstream ss;
            for (auto e : m)
            {
                string temp1 = e.first;
                string temp2 = e.second;
                ss << temp1 << endl << temp2 << endl;
            }
            cout << ss.str() << endl;
            fout << ss.str() << endl;

            fout.close();
        }
        else
        {
            // Decipher the permutated pixels
            for (unsigned int k = 0; k < totalPixels; k++)
            {
                XORintegerXpixel(SV, rawPixels[k]);
                XORintegerXpixel(R[(width * height) + k], rawPixels[k]);
            }

            // Reverse permutate the deciphered pixels
            vector<RGBTRIPLE> decipheredPixels(rawPixels.begin(), rawPixels.end());
            for (unsigned int i = 0; i < totalPixels; i++)
            {
                rawPixels[i] = decipheredPixels[P[i]];
            }

            ifstream e_file_validation("ED_validate.txt");

            map<string, string> m;
            while (!e_file_validation.eof())
            {
                string file_name;
                getline(e_file_validation, file_name);
                string status;
                getline(e_file_validation, status);
                m[file_name] = status;
            }
            e_file_validation.close();
            for (auto e : m)
            {
                cout << e.first << endl << e.second << endl;
            }

            m[fileName] = "decrypt";
            ofstream fout("ED_validate.txt");
            
            for (auto e : m)
            {
                fout << e.first << endl << e.second << endl;
            }

        } 
        delete[] R;
        delete[] P;
    }

    bool is24_bit_BMP(BITMAPFILEHEADER bf, BITMAPINFOHEADER bi)
    {
        if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
            bi.biBitCount != 24 || bi.biCompression != 0)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    int key_generator(string password)
    {
        ofstream password_store("password.txt", ios::app);
        string p = password;
        long long int random_n = 0;
        string random_s, random_cipher_key;
        
        for (int i = 0; i < password.length(); i++)
        {
            random_n = int(password[i]);
            random_n += random_n;
        }
        random_n = pow(random_n, 2);
        // for (int i = 0; i < password.length(); i++)
        // {
        //     random_n = int(password[i]);
        //     random_n += random_n;
        // }
        
        random_s = to_string(random_n);

        password_store << random_s << endl;

        // fin >> configured_password;
        // entered password;
        // 
                    //    << random_cipher_key << endl;
        password_store.close();

        return random_n;
    }

    bool encrypt_option_validation(string t_filename, string choice)
    {
        string f;
        string e_d_status;
        ifstream e_file_validation("ED_validate.txt");

        map<string, string> m;
        while (!e_file_validation.eof())
        {
            string file_name;
            getline(e_file_validation, file_name);
            string status;
            getline(e_file_validation, status);
            m[file_name] = status;
        }


        if (m.find(t_filename) == m.end())
        {
            if (choice == "encrypt")
                
                return false;
            else
                return true;
        }
        else
        {
            if (m[t_filename] == "encrypt" && choice == "encrypt")
            {
                return true;
            }
            else if(m[t_filename] == "decrypt" && choice == "decrypt")
            {
                return true;
            }
            else 
            {
                return false;
            }
        }

        e_file_validation.close();
    }
    
    string read_key(string password)
    {
        string t_line;
        string e_key;
        bool flag = false;
        ifstream key("password.txt");

        while (!key.eof())
        {
            getline(key, t_line);
            if (password == t_line)
            {
                getline(key, e_key);
                flag = true;
                return e_key;
            }
            
        }
        if(!flag)
            {
                cout << "Password is incorrect!" << endl;
                exit(0);
            }
    }
};