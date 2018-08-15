
#include <stdio.h>

int rgb(int r, int g, int b);

int main(void)
{
    rgb(0, 0, 255);

    return 0;

}

int rgb(int r, int g, int b)
{
//pass the result to the 'char *output'
    int length = 6;
    int count = length - 1;
    char out[length + 1];
    for (int z = 0; z < length; z++)
        out[z] = 48;
    int i = 0;

    while (r > 0)
    {
        out[i] = r % 16;
        r /= 16;
        i++;
    }
    while (g != 0)
    {
        out[i] = g % 16;
        g /= 16;
        i++;
    }
    while (b != 0)
    {
        out[i] = b % 16;
        b /= 16;
        i++;
    }

    while (count >= 0)
    {
        if (out[count] > 9)
        {
            out[count] = 'A' + (out[count] - 10);
        }
        printf("result : %c\n", out[count]);
        count--;
    }

    return 0;
}