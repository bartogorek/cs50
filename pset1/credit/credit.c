#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    long long cardNo;
    // asks for user input
    do
    {
        cardNo = get_long_long("Number: ");
    }
    while (cardNo < 0);

    // declaring variables
    long long digits = cardNo;  // copies user input to another variable for processing
    int numCount = 0;           // variable that will contain number of digits in the card number submitted

    // counts number of digits
    while (digits > 0)
    {
        digits = digits / 10;
        numCount++;
    }

    int card[numCount];     // array to that will store all digits of the card number supplied

    // puts each digit of the card number into an array
    for (int i = numCount - 1; i >= 0; i--)
    {
        card[i] = cardNo % 10;
        cardNo = cardNo / 10;
    }

    // variables that will contain the sums of numbers
    int sum1 = card[numCount - 1];  // sum of all digits not multiplied by 2
    int sum2 = 0;                   // sum of digits multiplied by 2

    // loop through the numbers and add together into sum1 and sum2
    for (int c = numCount - 2; c >= 0; c = c - 2)
    {
        int d = (card[c] * 2);  // local variable that takes

        if (d > 9)
        {
            sum2 += (d - 10) + 1;
        }
        else
        {
            sum2 += d;
        }

        // add to sum1
        if (c > 0)
        {
            sum1 += card[c - 1];
        }
    }

    // check if total modulo = 0
    if ((sum1 + sum2) % 10 == 0)
    {
        // the first switch checks if the first digit of input equals to 3, 4 or 5
        // the second nested switch inside some cases, checks the second digit to verify card company
        switch (card[0])
        {
            case 3:
                if (numCount == 15)
                {
                    switch (card[1])
                    {
                        case 4:
                        case 7:
                            printf("AMEX\n");
                            break;
                        default:
                            printf("INVALID\n");
                    }
                }
                else
                {
                    printf("INVALID\n");
                }
                break;
            case 4:
                if (numCount == 13 || numCount == 16)
                {
                    printf("VISA\n");
                }
                else
                {
                    printf("INVALID\n");
                }
                break;
            case 5:
                if (numCount == 16)
                {
                    switch (card[1])
                    {
                        case 1:
                        case 2:
                        case 3:
                        case 4:
                        case 5:
                            printf("MASTERCARD\n");
                        default:
                            printf("INVALID\n");
                    }
                }
                else
                {
                    printf("INVALID\n");
                }
                break;
            default:
                printf("INVALID\n");
                break;
        }
    }
    else
    {
        printf("INVALID\n");
    }
}