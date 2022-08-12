#include <iostream>
#include <string>
#include <vector>

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

class BitMapPicture
{
public:
    static unsigned int height;
    static unsigned int width;
    vector<RGBTRIPLE> raw_pixel;

    BitMapPicture(unsigned int height, unsigned int width)
    {
        this->height = height;
        this->width = width;
    }
    // TODO: read from bitmapfile picture in a linear fashion
    void read(string inFile)
    {
    }

    // TODO: write to bitmapfile picture
    void write(string outFile)
    {
    }

    // TODO:
    void encryptBMP(unsigned int key)
    {
        // TODO:
        //  Call Random Number Generator Function
        //  Call Pixel Permutation Function
        //  Call Pixel Encryption Function
    }

    // TODO:
    void decryptBMP(unsigned int key)
    {
        // TODO:
        //  Call Random Number Generator Function
        //  Call Pixel Permutation Function
        //  Call Pixel Decryption Function
    }
    
    //input file format validation
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

    //encryption_validation
    bool is_valid_encryption(string encrypt_option, string option[])
    {
        for (int i = 0; i < 2; i++)
        {
            if (!encrypt_option.compare(option[i]))
            {
                return true;
            }
            else if (i == 1)
            {
                return false;
            }
        }
        return false;
    }
};