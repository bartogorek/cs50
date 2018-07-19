// Resizes bitmap file by 'factor' provided in the command line
// Usage : ./resize <factor> <input_file> <output_file>
// Input file will be resized by <factor> passed as float

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "bmp.h"

// function that generates an array that represents copy/skip pattern
char new_pattern(float factor, float removed_hor, float step, int offset, char *pattern, int width, float new_width);


int main(int argc, char *argv[])
{


/***********************************************************************************************/
// CHECKING USAGE AND INITIALZING VARIABLES

    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: resize factor infile outfile\n");
        return 1;
    }

    // remember and parse factor float (argv[1])
    char *f = argv[1];
    float factor = atof(f);             // converts 'factor' provided in the command line into 'float'

    // set additional variables
    int new_padding = 0;                // stores new padding once calculated


/***********************************************************************************************/
// OPENING AND CHECKING THE FILES

    // remember filenames
    char *infile = argv[2];             // input file
    char *outfile = argv[3];            // output file

    // open input file and ensure it's valid
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s\n.", infile);
        return 2;
    }

    // open output file and ensure it's valid
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s\n.", outfile);
        return 3;
    }


/***********************************************************************************************/
// READING FILE AND INFO HEADERS

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure the input file is a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
    bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }


 /***********************************************************************************************/
 // CREATING NEW PATTERN BEFORE RESIZING

    // initializing required variables
    int width = bi.biWidth;
    int height = abs(bi.biHeight);
    int offset = 0;
    float step = 0;
    float new_width = floor(width * factor);
    float new_height = floor(height * factor);
    float removed_hor = 0;
    float removed_ver = 0;

    // create an array to store horizontal pattern
    char pattern_hor[bi.biWidth + 1];
    pattern_hor[bi.biWidth] = '\0';

    // create an array to store vertical pattern
    char pattern_ver[height + 1];
    pattern_ver[height] = '\0';

    // call function new_pattern to create copy/skip pattern
    *pattern_hor = new_pattern(factor, removed_hor, step, offset, pattern_hor, width, new_width);
    *pattern_ver = new_pattern(factor, removed_ver, step, offset, pattern_ver, height, new_height);

    // initialize variables to store the width and height of the output file
    int nwidth = 0;
    int nheight = 0;

    // calculate new width based on pattern array
    for (int u = 0; u < width; u++)
    {
        if (pattern_hor[u] == '0')
        {
            nwidth += 0;
        }
        else if (pattern_hor[u] == '1')
            nwidth += 1;
        else if (pattern_hor[u] == '2')
            nwidth += floor(factor);
        else if (pattern_hor[u] == '3')
            nwidth += floor(factor) + 1;
    }

    // calculate new height based on pattern array
    for (int v = 0; v < height; v++)
    {
        if (pattern_ver[v] == '0')
        {
            nheight += 0;
        }
        else if (pattern_ver[v] == '1')
            nheight += 1;
        else if (pattern_ver[v] == '2')
            nheight += floor(factor);
        else if (pattern_ver[v] == '3')
            nheight += floor(factor) + 1;
    }


/***********************************************************************************************/
// SETTING FILE AND INFO HEADERS

    // build new BITMAPINFOHEADER
    BITMAPINFOHEADER out_bi;
    out_bi = bi;                                    // copy all values from 'bi' to 'out_bi'
    out_bi.biWidth = nwidth;                        // new width assigned
    out_bi.biHeight = nheight;                      // new height assigned
    if (bi.biHeight < 1)                            // convert to negative if original height was negative
        out_bi.biHeight *= -1;
    int padding2 = (4 - (out_bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;          // calculate padding for the output file
    out_bi.biSizeImage = ((sizeof(RGBTRIPLE) * out_bi.biWidth) + padding2) * abs(out_bi.biHeight);

    // build new BITMAPFILEHEADER
    BITMAPFILEHEADER out_bf;
    out_bf = bf;
    out_bf.bfSize = out_bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write BITMAPFILEHEADER and BITMAPINFOHEADER into outfile
    fwrite(&out_bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    fwrite(&out_bi, sizeof(BITMAPINFOHEADER), 1, outptr);


/***********************************************************************************************/
// ITERATING OVER EACH SCANLINE AND COPYING OR SKIPPING

    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;       // used when skipping padding in the infile

    // if factor is a multiple precision number and/or less than 1, we'll need to work out how to
    // skip/multiply pixels; example : factor = 1.5, step will equal 2 and therefore every other pixel
    // will be written twice into the outfile

    // iterate through each scanline
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        float repeat_ver = 0;
        // copy or skip next pixel
        if (pattern_ver[i] == '0')
        {
            repeat_ver = 0;
            int skip = (bi.biWidth * sizeof(RGBTRIPLE)) + padding;
            fseek(inptr, skip, SEEK_CUR);                               // skip this scanline
            continue;
        }
        else if (pattern_ver[i] == '1')
            repeat_ver = 1;
        else if (pattern_ver[i] == '2')
            repeat_ver = floor(factor);
        else if (pattern_ver[i] == '3')
            repeat_ver = floor(factor) + 1;

         for (int y = 0; y < repeat_ver; y++)
         {
            // go back to the beginning of scanline if printing multiple times (making bitmap bigger)
            if (y > 0)
                fseek(inptr, -(bi.biWidth * sizeof(RGBTRIPLE)) - padding, SEEK_CUR);

            for (int w = 0; w < bi.biWidth; w++)
            {
                float repeat_hor = 0;
                // copy or skip next pixel
                if (pattern_hor[w] == '0')
                {
                    repeat_hor = 0;
                    fseek(inptr, sizeof(RGBTRIPLE), SEEK_CUR);      // skip this pixel
                    continue;
                }
                else if (pattern_hor[w] == '1')
                    repeat_hor = 1;
                else if (pattern_hor[w] == '2')
                    repeat_hor = floor(factor);
                else if (pattern_hor[w] == '3')
                    repeat_hor = floor(factor) + 1;

                RGBTRIPLE triple;
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                for (int x = 0; x < repeat_hor; x++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            printf("\n");

            // skip over padding, if any
            fseek(inptr, padding, SEEK_CUR);                                    // skip over padding
            new_padding = (4 - (nwidth * sizeof(RGBTRIPLE)) % 4) % 4;       // calculate new padding

            // add padding as calculated above
            for (int o = 0; o < new_padding; o++)
                fputc(0x00, outptr);
         }
    }


/***********************************************************************************************/
// CLOSING AND FINISHING

    // close input and output files
    fclose(inptr);
    fclose(outptr);
    return 0;
}

// END OF MAIN PROGRAM
/***********************************************************************************************/




// HELPER FUNCTION
// function new_pattern takes an array that represents height or width of the bitmap in number of items/pixels
// using factor provided, it creates new pattern that will be used to copy or skip pixels
char new_pattern(float factor, float removed_hor, float step, int offset, char *pattern, int width, float new_width)
{
    // check if factor below or above 0.5 before modifying pattern
    if (factor >= 0.50 && factor < 1)
    {
        removed_hor = floor(width - new_width);
        step = ceil(width / removed_hor);
        offset = step / 2;
        for (int j = 0; j < width; j++)
            pattern[j] = '1';
        for (int k = offset; k < width; k += step)
        {
            pattern[k] = '0';
        }
    }
    else if (factor < 0.50)
    {
        removed_hor = floor(width - new_width);
        step = ceil(removed_hor / new_width);
        offset = step / 2;
        for (int j = 0; j < width; j++)     // REFACTOR THIS !!! ONE FUNCTION
            pattern[j] = '0';
        for (int k = offset; k < width; k += step + 1)
        {
            pattern[k] = '1';
        }
    }
    else if ((factor - floor(factor)) == 0)
    {
        // change all items in the pattern array to represent how many times each pixel should be copied (=factor)
        for (int l = 0; l < width; l++)
        {
            pattern[l] = '2';
        }
    }
    else if (factor > 1 && (factor - floor(factor)) > 0.49)
    {
        // change all items in the pattern array to represent how many times each pixel should be copied (=factor)
        for (int m = 0; m < width; m++)
        {
            pattern[m] = '3';
        }

        // change selected items in the pattern array by adding 1, to indicate that these need to be copied one additional time
        removed_hor = (width * ceil(factor)) - new_width;
        step = ceil(width / removed_hor);
        offset = step / 2;
        for (int k = offset; k < width; k += step)
        {
            pattern[k] = '2';
        }
    }
    else if (factor > 1 && (factor - floor(factor)) < 0.50)
    {
        // change all items in the pattern array to represent how many times each pixel should be copied (=factor)
        for (int n = 0; n < width; n++)
        {
            pattern[n] = '2';
        }

        // change selected items in the pattern array by adding 1, to indicate that these need to be copied one additional time
        removed_hor = new_width - (width * floor(factor));
        step = ceil(width / removed_hor);
        offset = step / 2;
        for (int k = offset; k < width; k += step + 1)
        {
            pattern[k] = '3';
        }
    }

    return *pattern;
}