#include <stdio.h>

int main()
{
    int size = 100;
    int array[size];

    for (int i = 0; i < 100; i++)
    {
        array[i] = i;
    }

    printf("Array[96] : %i\n", array[96]);
    return 0;

}