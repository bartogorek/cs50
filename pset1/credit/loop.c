#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
    // ask for user input
    long long cardnumber = get_long_long("Number : ");

    int digits = cardnumber;
    int numDigits = 0;

    while (digits > 0)
    {
        digits = digits/10;
        numDigits++;
    }

    int digit[numDigits];

    for (int i = numDigits - 1; i >= 0; i--)
    {
        digit[i] = cardnumber % 10;
        cardnumber = cardnumber / 10;
    }

}