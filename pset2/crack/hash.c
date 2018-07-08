

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <cs50.h>
#include <unistd.h>

void char1(string set, int i, int length, char test[4], int counter, int counter2)
{
    if (i < length)
    {
        test[counter] = set[i];
        printf("%s\n", test);
        i++;
        char1(set, i, length, test, counter, counter2);
    }
    test[counter] = set[counter2];
}

void sequence(string set, int i, int length, char test[4], int c)
{
    for (int counter2 = 0; counter2 < 3; counter2++)
    {
        for (int counter = 0; counter < c; counter++)
        {
            char1(set, i, length, test, counter, counter2);
        }
    }
}

int main()
{
    int i = 0;
    int c = 3;  // number of characters
    char test[4];
    memset(test, '\0', sizeof(test));
    string set = "123";
    int length = strlen(set);
    sequence(set, i, length, test, c);
    return 0;
}