#include <iostream>
#include <string>
#include <vector>

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
        static unsigned int height;
        static unsigned int width;
        vector <RGBTRIPLE> raw_pixel;

        BitMapPicture(unsigned int height, unsigned int width)
        {
            this -> height = height;
            this -> width = width;
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