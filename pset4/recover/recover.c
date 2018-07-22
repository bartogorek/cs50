// Recover.c - the program recovers jpeg files from memory card
// Usage : ./recover <file_name>, where file name is *.raw

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define BLOCK 512       // jpeg consists of blocks that are 512 bytes long

// aliases for C/C++ primitive data types
// https://msdn.microsoft.com/en-us/library/cc230309.aspx
typedef uint8_t  BYTE;

// helper functions that checks if BLOCK contains jpeg signature
int is_jpeg(BYTE *buffer);



int main(int argc, char *argv[])
{
    // confirm correct usage (command line arguments)
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover [filename].raw");
        return 1;
    }


    // initialize variables
    BYTE buffer[BLOCK];                 // buffer to store BLOCK of 512 bytes
    char *infile = argv[1];             // input file, memory card *.raw
    char outfile[8];                    // outfile name counter, 8 chars to accommodate 'xxx.jpg'
    char *outfile_ext = ".jpg";         // ouftile extension : .jpg
    int count = 0;                      // count jpegs, used to 'outfile' name
    FILE *outjpeg = NULL;               // create outfile


    // open input file and confirm it's valid
    FILE *raw_file = fopen(infile, "r");
    if (raw_file == NULL)
    {
        fprintf(stderr, "Input file invalid or cannot be opened");
        return 2;
    }


    // iterate over all blocks in the raw_file, if jpeg found, start writing into
    // separate jpeg file, until next jpeq is found
    while (fread(&buffer, sizeof(BYTE), BLOCK, raw_file) == BLOCK)
    {
        if (is_jpeg(buffer) == 5)
        {
            // if outjpeg already exists, close it before
            // opening a new one
            if (outjpeg != NULL)
            {
                fclose(outjpeg);                // close outjpeg
            }

            // create new filename for outjpeg using 'count'
            sprintf(outfile, "%03i", count);    // format 'count' to show leading zeros and print into 'outfile'
            strcat(outfile, outfile_ext);       // concatenate with file extension : .jpg
            count++;                            // add 1 to 'count' ready for the next jpeg file

            // open new jpeg file and confirm it's valid
            outjpeg = fopen(outfile, "w");
            if (outjpeg == NULL)
            {
                fclose(raw_file);
                fprintf(stderr, "Could not create %s\n.", outfile);
                return 3;
            }

            // write BLOCK into new outjpeg
            fwrite(buffer, sizeof(BYTE), BLOCK, outjpeg);
        }
        else
        {
            // BLOCK didn't have jpeg signature, check if outjpeg already
            // exists and add the BLOCK to the end of it
            if (outjpeg != NULL)
            {
                fwrite(buffer, sizeof(BYTE), BLOCK, outjpeg);
            }
        }
    }

    // close files before the program ends
    fclose(outjpeg);        // close the last outjpeg
    fclose(raw_file);       // close *.raw file

    return 0;
}


// helper functions
// checks if block of BLOCK contains jpeg signature
int is_jpeg(BYTE *buffer)
{
    // check if first four bytes form jpeg signature
    if (buffer[0] == 0xff &&
        buffer[1] == 0xd8 &&
        buffer[2] == 0xff &&
        (buffer[3] & 0xf0) == 0xe0)
    {
        return 5;       // success, jpeg signature found
    }
    else
    {
        return 4;       // jpeg signature not found
    }
}
