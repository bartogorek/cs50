
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <cs50.h>


int main(void)
{
    float factor = get_float("Factor : ");
    int width = get_int("Width : ");
    int new_width = width * factor;
    int removed = width - new_width;
    int normal_gap = 0;
    int first_gap = 0;

    int counter = 0;


    if (factor > 0.49 && factor < 1)
    {

        normal_gap = new_width / removed;
        first_gap = normal_gap / 2;

        for (int k = 0; k < first_gap; k++)
        {
            printf("1 ");
            counter++;
        }
        for (int i = counter; i < width; i++)
        {
            printf("r ");

            for (int j = 0; j < normal_gap; j++)
            {
                i++;
                if (i < width)
                {
                    printf("1 ");
                }
                else
                    break;
            }
        }

    }
    else if (factor > 0 && factor < 0.50)
    {

        normal_gap = removed / new_width;
        first_gap = normal_gap / 2;

        for (int k = 0; k < first_gap; k++)
        {
            printf("r ");
            counter++;
        }
        for (int i = counter; i < width; i++)
        {
            printf("1 ");

            for (int j = 0; j < normal_gap; j++)
            {
                i++;
                if (i < width)
                {
                    printf("r ");
                }
                else
                    break;
            }
        }

    }
    else if ((factor - floor(factor)) == 0)
    {

        for (int l = 0; l < width; l++)
        {
            for (int m = 0; m < factor; m++)
                printf("1 ");
        }

    }

    return 0;
}
