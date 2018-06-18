#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
    long long card = get_long_long("Input : ");
    int digits = card;
    int count = 0;

    while (digits > 0)
    {
        digits = digits / 10;
        count++;
    }

    printf("number of digits : %i\n", count);

    int array[digits];

    for (int i = count - 1; i > 0; i--)
    {
        array[i] = card % 10;
        card = card / 10;
        printf("%i\n", array[i]);
    }

    //int n = i % 10;
    //long long number[1];
    //number[0] = n;
    //printf("Result : %i\n", n);


}