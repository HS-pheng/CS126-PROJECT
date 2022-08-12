#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

typedef uint8_t  BYTE;
typedef uint32_t DWORD;
typedef int32_t  LONG;
typedef uint16_t WORD;

// Define BITMAPFILEHEADER struct 
typedef struct
{
    WORD   bfType;
    DWORD  bfSize;
    WORD   bfReserved1;
    WORD   bfReserved2;
    DWORD  bfOffBits;
} __attribute__((__packed__))
BITMAPFILEHEADER;

// Define BITMAPINFOHEADER struct
typedef struct
{
    DWORD  biSize;
    LONG   biWidth;
    LONG   biHeight;
    WORD   biPlanes;
    WORD   biBitCount;
    DWORD  biCompression;
    DWORD  biSizeImage;
    LONG   biXPelsPerMeter;
    LONG   biYPelsPerMeter;
    DWORD  biClrUsed;
    DWORD  biClrImportant;
} __attribute__((__packed__))
BITMAPINFOHEADER;

// Define the type of each pixel: RGBTRIPLE
typedef struct
{
    BYTE rgbtBlue;
    BYTE rgbtGreen;
    BYTE rgbtRed;
}
RGBTRIPLE;

class BitMapPicture
{
    public:
        unsigned int height;
        unsigned int width;
        string fileName;
        vector <RGBTRIPLE> raw_pixels;
        BITMAPFILEHEADER bf;
        BITMAPINFOHEADER bi;
        unsigned int padding;

        BitMapPicture(string fileName)
        {
            this -> fileName = fileName;
        };
        
        // TODO: read from bitmapfile picture in a linear fashion
        void read()
        {
            fstream fin(fileName, ios::in);

            fin.read((char *) &bf, sizeof(BITMAPFILEHEADER));
            fin.read((char *) &bi, sizeof(BITMAPINFOHEADER));

            this->height = bi.biHeight;
            this->width = bi.biWidth;

            // Calculate extra padding 
            padding = (4 - ((width * 3) % 4)) % 4;
            for (int y = 0; y < height; y++)
            {
                for (int x = 0; x < width; x++)
                {
                    RGBTRIPLE tmp;
                    fin.read((char *) &tmp, sizeof(RGBTRIPLE));
                    raw_pixels.push_back(tmp);
                }
                fin.seekg(padding, ios::cur);
            }
        }
        // TODO: write to bitmapfile picture
        void write()
        {
            fstream fout("hi.bmp", ios::out);

            fout.write((char *) &bf, sizeof(BITMAPFILEHEADER));
            fout.write((char *) &bi, sizeof(BITMAPINFOHEADER));

            for (int y = 0; y < height; y++)
            {
                for (int x = 0; x < width; x++)
                {
                    fout.write((char *) &raw_pixels[(width * y) + x], sizeof(RGBTRIPLE));
                }
                for (int k = 0; k < padding; k++)
                {
                    // Write null byte to complete padding
                    fout.put(0x00);
                }
            }
        }

        // TODO: 
        void encryptBMP(unsigned int key)
        {
            //TODO:
            // Call Random Number Generator Function
            // Call Pixel Permutation Function
            // Call Pixel Encryption Function
        }

        // TODO:
        void decryptBMP(unsigned int key)
        {
            //TODO:
            // Call Random Number Generator Function
            // Call Pixel Permutation Function
            // Call Pixel Decryption Function
        }
};
