
#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"
#include <string.h>

int main(int argc, char *argv[])
{
    // checking if correct arguments passed
    if (argc != 3)
    {
        printf("use three args");
        return 1;
    }

    // opening input and output files
    FILE *inputr = fopen(argv[1], "r");
    FILE *outptr = fopen(argv[2], "w");

    int len = strlen(argv[1]);
    char *file = malloc(len * sizeof(char));

    file = argv[1];

    // reading bitmap header info from input file
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inputr);
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inputr);

    // writing (copying) bitmap header info to output file
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // add triples
    RGBTRIPLE triple;
    triple.rgbtBlue = 0xD4;
    triple.rgbtGreen = 0xEE;
    triple.rgbtRed = 0xD9;

    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        for (int j = 0; j < bi.biWidth; j++)
        {
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
        }
    }

    // closing files
    fclose(outptr);
    fclose(inputr);

    return 0;
}