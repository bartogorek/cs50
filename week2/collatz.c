/**
 * Collatz conjecture - program counts how many steps it takes
 * to get to 1 from any integer provided by the user.
 * Created as part of CS50, week 2, recursion short video.
 */

#include <stdio.h>
#include <cs50.h>

int steps = 0;

int collatz(n)
{
    if (n == 1)
        return 0;
    else
    {
        if (n % 2 == 0)
            n = n / 2;
        else
            n = (3 * n) + 1;
        steps++;
        collatz(n);
    }
    return 0;
}

int main(void)
{
    int n = get_int("Input an integer : ");
    collatz(n);
    printf("Steps : %i\n", steps);
}