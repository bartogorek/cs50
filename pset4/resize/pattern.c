
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <cs50.h>

char new_pattern(float factor, float removed, float step, int offset, char *pattern, int width, float new_width);


int main(void)
{
    float factor = get_float("Factor : ");
    int width = get_int("Width : ");
    int height = get_int("Height : ");

    int offset = 0;
    float step = 0;
    float new_width = floor(width * factor);
    float new_height = floor(height * factor);
    float removed = 0;
    float removed_ver = 0;

    // create an array to store horizontal pattern
    char pattern_hor[width + 1];
    pattern_hor[width] = '\0';

    // create an array to store vertical pattern
    char pattern_ver[height + 1];
    pattern_ver[height] = '\0';

    // call function new_pattern to create copy/skip pattern
    *pattern_hor = new_pattern(factor, removed, step, offset, pattern_hor, width, new_width);
    *pattern_ver = new_pattern(factor, removed_ver, step, offset, pattern_ver, height, new_height);

    // print all characters from 'pattern_hor' array
    for (int i = 0; i < width; i++)
        printf("%c, ", pattern_hor[i]);
    printf("\n");
    // print all characters from 'pattern_var' array
    for (int i = 0; i < height; i++)
        printf("%c, ", pattern_ver[i]);
    printf("\n");

    return 0;
}



// function new_pattern takes an array that represents height or width of the bitmap in number of items/pixels
// using factor provided, it creates new pattern that will be used to copy or skip pixels
char new_pattern(float factor, float removed, float step, int offset, char *pattern, int width, float new_width)
{
    // check if factor below or above 0.5 before modifying pattern
    if (factor > 0.49 && factor < 1)
    {
        removed = floor(width - new_width);
        step = ceil(width / removed);
        offset = step / 2;
        for (int j = 0; j < width; j++)
            pattern[j] = '1';
        for (int k = offset; k < width; k += step)
        {
            pattern[k] = '0';
        }
    }
    else if (factor < 0.50)
    {
        removed = floor(width - new_width);
        step = ceil(removed / new_width);
        offset = step / 2;
        for (int j = 0; j < width; j++)     // REFACTOR THIS !!! ONE FUNCTION
            pattern[j] = '0';
        for (int k = offset; k < width; k += step + 1)
        {
            pattern[k] = '1';
        }
    }
    else if ((factor - floor(factor)) == 0)
    {
        // change all items in the pattern array to represent how many times each pixel should be copied (=factor)
        for (int l = 0; l < width; l++)
        {
            pattern[l] = '3';
        }
    }
    else if (factor > 1 && (factor - floor(factor)) > 0.49)
    {
        // change all items in the pattern array to represent how many times each pixel should be copied (=factor)
        for (int m = 0; m < width; m++)
        {
            pattern[m] = '3';
        }

        // change selected items in the pattern array by adding 1, to indicate that these need to be copied one additional time
        removed = (width * ceil(factor)) - new_width;
        step = ceil(width / removed);
        offset = step / 2;
        for (int k = offset; k < width; k += step)
        {
            pattern[k] = '2';
        }
    }
    else if (factor > 1 && (factor - floor(factor)) < 0.50)
    {
        // change all items in the pattern array to represent how many times each pixel should be copied (=factor)
        for (int n = 0; n < width; n++)
        {
            pattern[n] = '2';
        }

        // change selected items in the pattern array by adding 1, to indicate that these need to be copied one additional time
        removed = new_width - (width * floor(factor));
        step = ceil(width / removed);
        offset = step / 2;
        for (int k = offset; k < width; k += step + 1)
        {
            pattern[k] = '3';
        }
    }

    return *pattern;
}