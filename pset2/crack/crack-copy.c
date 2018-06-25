#define _XOPEN_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <cs50.h>
#include <unistd.h>

int main(int argc, string argv[])
{
    // checks if argc = 2, that is, if hash key is provided with program name
    if (argc != 2)
    {
        printf("Usage: ./crack hash");
        return 1;
    }

    int c = 51;             // number of loops for each character / size of the array (A-Z + a-z, counting from zero)
    char test[6] = {'A', 'A', 'A', 'A', 'A', '\0'};     // initial test password string
    char test2[5];          // string that is used for less than five characters
    char salt[2];           // string used to store 'salt'
    char characters[3] = "ABC";

    memset(test2, '\0', sizeof(test2));             // setting memory to \0
    memset(salt, '\0', sizeof(salt));               // setting memory to \0

    strncpy(salt, argv[1], 2);                      // extracting 'salt' from the hash key and assigning to 'salt'

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
                        if (strcmp(crypt(test, salt), argv[1]) == 0)
                        {
                            printf("%s\n", test);
                            exit(0);
                        }
                        test[4] += 1;
                        if (m == 25)        // A-Z completed, shift to lower case by skipping ASCII characters 91-96
                        {
                            test[4] += 6;
                        }
                    }
                    if (strcmp(crypt(strncpy(test2, test, 4), salt), argv[1]) == 0)
                    {
                        printf("%s\n", test2);
                        exit(0);
                    }
                    if (strcmp(crypt(test, salt), argv[1]) == 0)
                    {
                        printf("%s\n", test);
                        exit(0);
                    }
                    test[4] = 'A';
                    test[3] += 1;
                    if (l == 25)        // A-Z completed, shift to lower case by skipping ASCII characters 91-96
                    {
                        test[3] += 6;
                    }
                }
                if (strcmp(crypt(strncpy(test2, test, 3), salt), argv[1]) == 0)
                {
                    printf("%s\n", test2);
                    exit(0);
                }
                if (strcmp(crypt(test, salt), argv[1]) == 0)
                {
                    printf("%s\n", test);
                    exit(0);
                }
                test[3] = 'A';
                test[2] += 1;
                if (k == 25)        // A-Z completed, shift to lower case by skipping ASCII characters 91-96
                {
                    test[2] += 6;
                }
            }
            if (strcmp(crypt(strncpy(test2, test, 2), salt), argv[1]) == 0)
            {
                printf("%s\n", test2);
                exit(0);
            }
            if (strcmp(crypt(test, salt), argv[1]) == 0)
            {
                printf("%s\n", test);
                exit(0);
            }
            test[2] = 'A';
            test[1] += 1;
            if (j == 25)        // A-Z completed, shift to lower case by skipping ASCII characters 91-96
            {
                test[1] += 6;
            }
        }
        if (strcmp(crypt(strncpy(test2, test, 1), salt), argv[1]) == 0)
        {
            printf("%s\n", test2);
            exit(0);
        }
        if (strcmp(crypt(test, salt), argv[1]) == 0)
        {
            printf("%s\n", test);
            exit(0);
        }
        test[1] = 'A';
        test[0] += 1;
        if (i == 25)        // A-Z completed, shift to lower case by skipping ASCII characters 91-96
        {
            test[0] += 6;
        }
    }
    return 0;
}