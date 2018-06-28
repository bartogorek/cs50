#define _XOPEN_SOURCE
//#include <crypt.h>  needed or not ?
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <cs50.h>
#include <unistd.h>

int main(int argc, string argv[])
{

    string input = get_string("Input : ");
    printf("Args: %i\n", argc);
    //char input[6] = {'A', 'A', 'A', 'A', 'A', '\0'};

    char salt[4];
    memset(salt, '\0', sizeof(salt));     // setting memory to \0

    strncpy(salt, argv[1], 3);
    printf("Salt: %s\n", salt);
    string output = crypt(input, salt);
    printf("%s\n", output);

}