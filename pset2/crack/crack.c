#define _XOPEN_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <cs50.h>
#include <unistd.h>

// test2func - clears test2 string by loading it with '\0'
// then it copies 'w' characters from 'test' string into 'test2'
// so that strings containing less than five chars can be hashed and tested
int test2func(string a, string b, int w, int x)
{
    for (int z = 0; z < x; z++)
    {
        a[z] = '\0';
    }
    strncpy(a, b, w);
    return 0;
}

int main(int argc, string argv[])
{
    // checks if argc = 2, that is, if hash key is provided with program name
    if (argc != 2)
    {
        printf("Usage: ./crack hash");
        return 1;
    }

    char test[6] = "AAAAA";                 // initial test password string
    char test2[5];                          // string that is used for less than five characters
    char salt[3];                           // string used to store 'salt'
    // all characters that will be used to crack the passwd
    char characters[53] = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz";

    int c = strlen(characters);             // number of loops for each character / size of the array (A-Z + a-z, counting from zero)
    int x = 5;                              // length of test2 / maximum length of password

    string hash = argv[1];                  // hash provided as argument from command line

    memset(salt, '\0', sizeof(salt));               // setting memory to '\0' for 'salt'
    strncpy(salt, hash, 2);                         // extracting 'salt' from the hash key and assigning to 'salt'

    // 'for' loops checking every possible iteration of every character (A-Za-z)
    for (int i = 0; i < c; i++)                     // iterating character #1 in the string 'test' -> *AAAA
    {
        for (int j = 0; j < c; j++)                 // iterating character #2 in the string 'test' -> A*AAA
        {
            for (int k = 0; k < c; k++)             // iterating character #3 in the string 'test' -> AA*AA
            {
                for (int l = 0; l < c; l++)         // iterating character #4 in the string 'test' -> AAA*A
                {
                    for (int m = 0; m < c; m++)     // iterating character #5 in the string 'test' -> AAAA*
                    {
                        test[4] = characters[m];
                        if (strcmp(crypt(test, salt), hash) == 0)
                        {
                            printf("%s\n", test);
                            exit(0);
                        }
                    }
                    test2func(test2, test, 4, x);
                    if (strcmp(crypt(test2, salt), hash) == 0)
                    {
                        printf("%s\n", test2);
                        exit(0);
                    }
                    test[4] = characters[0];
                    test[3]++;
                }
                test2func(test2, test, 3, x);
                if (strcmp(crypt(test2, salt), hash) == 0)
                {
                    printf("%s\n", test2);
                    exit(0);
                }
                test[3] = characters[0];
                test[2]++;
            }
            test2func(test2, test, 2, x);
            if (strcmp(crypt(test2, salt), hash) == 0)
            {
                printf("%s\n", test2);
                exit(0);
            }
            test[2] = characters[0];
            test[1]++;
        }
        test2func(test2, test, 1, x);
        if (strcmp(crypt(test2, salt), hash) == 0)
        {
            printf("%s\n", test2);
            exit(0);
        }
        test[1] = characters[0];
        test[0]++;
    }
    return 0;
}
