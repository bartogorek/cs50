#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    // checks if argv[2] equals '2', if not, prints correct usage instruction
    if (argc != 2)
    {
        printf("Usage : ./caesar k\n");
        return 1;
    }

    int k = atoi(argv[1]);  // converts program parameter from string to int
    string plain = get_string("plaintext: ");

    printf("ciphertext: ");

    for (int i = 0; i < strlen(plain); i++)
    {
        char x = plain[i];  // i-th character from plaintext
        char y;             // enciphered character container
        char a;             // will contain 'a' or 'A' depending on result of if statement, used to go from ASCII to alpha

        if (isalpha(x))
        {
            // check if lower or upper case
            if (islower(x))
            {
                a = 'a';    // used to go from ASCII to alphabetical index
            }
            else
            {
                a = 'A';    // used to go from ASCII to alphabetical index
            }

            // Perform enciphering (could be in one line, but easier to follow)
            x = x - a;          // go from ASCII to alphabetical index
            x = (x + k) % 26;   // shift the letter by 'k' positions
            y = x + a;          // go from alphabetical to ASCII

            printf("%c", y);    // print enciphered char
        }
        else
        {
            printf("%c", x);    // print char without enciphering (non-alpha)
        }
    }
    printf("\n");
    return 0;
}