// Merge.c - program demonstrating merge sort algorithm using recursion

#include <stdio.h>
#include <cs50.h>

void sort(int a, int z)
{
    int leftA = a;
    int leftZ = z / 2;
    int rightA = z / 2 + 1;
    int rightZ = z;

    if (z > 1)
    {
        sort(leftA, leftZ);
        sort(rightA, rightZ);
    }

    printf("")
}


int main(void)
{
    // declaring variables
    int size = get_int("Enter size of array : ");           // number of characters held in the array
    int max_index = size - 1;                               // highest index in the array
    int array[size];                                        // creating array
    array[max_index] = '\0';                                // setting last character in the array to '\0'

    // load the array with numbers
    for (int i = 0; i < max_index; i++)
    {
        array[i] = get_int("Your number : ");
    }

    // set boundaries for left, middle and right
    int a = 0;
    int z = max_index;

    // print out the content of the array
    printf("Array : ");
    for (int k = 0; k < max_index; k++)
    {
        printf("%i  ", array[k]);
    }
    printf("\n");

    sort(a, z);

    return 0;
}