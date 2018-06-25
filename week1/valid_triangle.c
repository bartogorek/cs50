#include <stdio.h>
#include <cs50.h>

bool valid_triangle(float x, float y, float z)
{
    if (x <= 0 || y <= 0 || z <= 0)
    {
        return false;
    }

    if ((x + y) > z && (x + z) > y && (z + y) > x)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
    printf("Give me #1 length : ");
    float x = get_float();
    printf("Give me #2 length : ");
    float y = get_float();
    printf("Give me #3 length : ");
    float z = get_float();

    if (valid_triangle(x, y, z))
    {
        printf("Valid triangle\n");
    }
    else
    {
        printf("Invalid triangle\n");
    }
    return 0;
}