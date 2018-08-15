// test program implementing 'load' function for pset5 of CS50



// include libraries
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// define constant values
#define LENGTH 45
#define COLLECTION 10

// define global data structures
char *collection;

// prototype functions
bool load(const char *dictionary);



// main program
int main(int argc, char* argv[])
{
    collection = malloc(sizeof(char) * LENGTH * COLLECTION);
    // ensure correct usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage : ./load <dictionary>\n");
        return 1;
    }

    // declare data structures
    char *infile = argv[1];           // remember input file

    // load dictionary into a data structure
    bool loaded = load(infile);

    // test print
    printf("%s\n", &collection[0]);
    printf("%s\n", &collection[1]);

    // print all items from the data struct
    if (loaded)
        printf("success\n");

    free(collection);

    return 0;
}



// HELPER functions
// function loading dictionary from file into data struct
bool load(const char *dictionary)
{
    // declare variables
    char *word = malloc(sizeof(char) * LENGTH);     // allocate memory for to store 'word'
    int count = 0;                                  // count characters for each word

    // open file and confirm it's valid
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        fprintf(stderr, "Could not open %s\n", dictionary);
        return false;
    }
    else
    {
        printf("loading dictionary\n");
    }

    // iterate over characters in file
    for (int c = fgetc(dict); c != EOF; c = fgetc(dict))
    {
        if (c != '\n')
        {
            word[count] = c;
            count++;
        }
        else
        {
            count = 0;
            printf("%s\n", word);
            strcpy(&collection[count], word);
        }
    }
    printf("%s\n", word);   // print last word of the file
    strcpy(&collection[count], word);

    // success, close file, return true
    free(word);
    printf("closing file once operations complete\n");
    fclose(dict);
    return true;
}