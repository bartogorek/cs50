
#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    string s = get_string("String : ");
    int x = s[0] - '0';
    int y = s[2] - '0';
    return x * (((y * 8) / y) / y);

    printf("Result : %i\n", res);
}