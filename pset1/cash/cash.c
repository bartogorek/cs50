#include <stdio.h>
#include <cs50.h>

int main(void)
{
    float input;

    do
    {
        input = get_float("Change owed : ");
    }
    while (input < 0);

    int change = input * 100;
    int penny = 1;
    int nickel = 5;
    int dime = 10;
    int quarter = 25;
    int number = 0;

    while (change >= quarter)
    {
        change -= quarter;
        number++;
    }
    while (change >= dime)
    {
        change -= dime;
        number++;
    }
    while (change >= nickel)
    {
        change -= nickel;
        number++;
    }
    while (change >= penny)
    {
        change -= penny;
        number++;
    }

    printf("%i\n", number);
}