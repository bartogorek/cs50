#include <cs50.h>
#include <stdio.h>

// main funtcion
int main(void)
{
    // takes input from user : pyramid height
    int n = get_int("Height: ");

    // check if input <= 23, if not, repeat input
    while (n > 23 || n < 0)
    {
        n = get_int("Height: ");
    }

    // input is correct, proceed with printing
    for (int p = 0; p < n; p++)
    {

        // prints spaces to the left of the pyramid
        for (int i = 0; i < n - p - 1; i++)
        {
            printf(" ");
        }

        // prints pyramid bricks (left hand side)
        for (int i = 0; i <= p; i++)
        {
            printf("#");
        }

        // prints two hashes
        printf("  ");

        // prints pyramid bricks (right hand side)
        for (int i = 0; i <= p; i++)
        {
            printf("#");
        }

        // goes to new line
        printf("\n");

    }
}
