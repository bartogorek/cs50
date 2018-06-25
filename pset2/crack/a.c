
#define _XOPEN_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <cs50.h>
#include <unistd.h>


int main(void)
{
    char test[4] = "bart";
    char test2[3];
    printf("Output: %c\n", test[1]);
    strncpy(test2, test, 2);
    test2[2] = '\0';
    printf("Output 2: %s\n", test2);

}