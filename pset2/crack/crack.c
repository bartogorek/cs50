// CRACK.C - program built as part of CS50 assignment, executed as follows : ./crack hash
// takes the first two characters of 'hash' to use as 'salt', searches for password string of
// up to five characters by trying all different possibilities, that, when hashed,
// matches the hash provided in the command line.

// TESTS & RESULTS from CS50 website :
// anushree:50xcIMJ0y.RXo   YES
// brian:50mjprEcqC/ts      CA
// bjbrown:50GApilQSG3E2    UPenn
// lloyd:50n0AAUD.pL8g      lloyd
// malan:50CcfIk1QrPr6      maybe
// maria:509nVI8B9VfuA      TF
// natmelo:50JIIyhDORqMU    nope
// rob:50JGnXUgaafgc        ROFL
// stelios:51u8F0dkeDSbY    NO
// zamyla:50cI2vYkF0YU2     LOL

#define _XOPEN_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <cs50.h>
#include <unistd.h>

// test2func - clears passwd_string2 string by loading it with '\0' then it copies specified
// number of character ('short_pswd_length') from 'passwd_string1' string into 'passwd_string2'
// so that strings containing less than five chars can be hashed and tested
int test2func(string passwd_string2, string passwd_string1, int short_pswd_length, int passwd_length)
{
    for (int z = 0; z < passwd_length; z++)
    {
        passwd_string2[z] = '\0';
    }
    strncpy(passwd_string2, passwd_string1, short_pswd_length);
    return 0;
}


int main(int argc, string argv[])
{
    // checks if argc = 2, that is, if hash key is provided with program name
    if (argc != 2)
    {
        printf("Usage: ./crack hash\n");
        return 1;
    }

    char passwd_string1[6];                     // initial passwd_string1 password string
    char passwd_string2[5];                     // string that is used for less than five characters
    char salt[3];                               // string used to store 'salt'
    // characters that will be used to crack the passwd
    char characters[53] = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz";
    //char characters[5] = "loyd";

    int chars_size = strlen(characters);        // number of loops for each character / size of the array (passwd_string2-Z + passwd_string2-z, counting from zero)
    int passwd_length = 5;                      // length of passwd_string2 / maximum length of password

    string hash = argv[1];                      // hash provided as argument from command line

    memset(salt, '\0', sizeof(salt));           // setting memory to '\0' for 'salt'
    strncpy(salt, hash, 2);                     // extracting 'salt' from the hash key and assigning to 'salt'

    for (int h = 0; h < passwd_length; h++)
    {
        passwd_string1[h] = characters[0];
    }
    passwd_string1[passwd_length] = '\0';

    // 'for' loops checking every possible iteration of every character (passwd_string2-Za-z)
    for (int i = 0; i < chars_size; i++)                     // iterating character #1 in the string 'passwd_string1' -> *AAAA
    {
        for (int j = 0; j < chars_size; j++)                 // iterating character #2 in the string 'passwd_string1' -> A*AAA
        {
            for (int k = 0; k < chars_size; k++)             // iterating character #3 in the string 'passwd_string1' -> AA*AA
            {
                for (int l = 0; l < chars_size; l++)         // iterating character #4 in the string 'passwd_string1' -> AAA*A

                    for (int m = 0; m < chars_size; m++)     // iterating character #5 in the string 'passwd_string1' -> AAAA*
                    {
                        passwd_string1[4] = characters[m];
                        if (strcmp(crypt(passwd_string1, salt), hash) == 0)
                        {
                            printf("%s\n", passwd_string1);
                            exit(0);
                        }
                    }
                    test2func(passwd_string2, passwd_string1, 4, passwd_length);
                    if (strcmp(crypt(passwd_string2, salt), hash) == 0)
                    {
                        printf("%s\n", passwd_string2);
                        exit(0);
                    }
                    passwd_string1[4] = characters[0];
                    passwd_string1[3] = characters[l + 1];
                }
                test2func(passwd_string2, passwd_string1, 3, passwd_length);
                if (strcmp(crypt(passwd_string2, salt), hash) == 0)
                {
                    printf("%s\n", passwd_string2);
                    exit(0);
                }
                passwd_string1[3] = characters[0];
                passwd_string1[2] = characters[k + 1];
            }
            test2func(passwd_string2, passwd_string1, 2, passwd_length);
            if (strcmp(crypt(passwd_string2, salt), hash) == 0)
            {
                printf("%s\n", passwd_string2);
                exit(0);
            }
            passwd_string1[2] = characters[0];
            passwd_string1[1] = characters[j + 1];
        }
        test2func(passwd_string2, passwd_string1, 1, passwd_length);
        if (strcmp(crypt(passwd_string2, salt), hash) == 0)
        {
            printf("%s\n", passwd_string2);
            exit(0);
        }
        passwd_string1[1] = characters[0];
        passwd_string1[0] = characters[i + 1];
    }
    return 0;
}
