
#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage ./boom <filename>");
        return 1;
    }

    char *outfile = argv[1];
    FILE *outptr = fopen(outfile, "w");

    BITMAPFILEHEADER bf;
    bf.bfType = 19778;
    bf.bfSize = 55;
    bf.bfReserved1 = 0;
    bf.bfReserved2 = 0;
    bf.bfOffBits = 54;

    BITMAPINFOHEADER bi;
    bi.biSize = 40;
    bi.biWidth = 1;
    bi.biHeight = 1;
    bi.biPlanes = 1;
    bi.biBitCount = 24;
    bi.biCompression = 0;
    bi.biXPelsPerMeter = 2834;
    bi.biYPelsPerMeter = 2834;
    bi.biClrUsed = 0;
    bi.biClrImportant = 0;

    RGBTRIPLE triple;
    triple.rgbtRed = 0x00;
    triple.rgbtGreen = 0x00;
    triple.rgbtBlue = 0xff;

    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);

    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    for (int l = 0; l < padding; l++)
        fputc(0x00, outptr);

    bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + padding) * abs(bi.biHeight);

    fclose(outptr);

    return 0;

}