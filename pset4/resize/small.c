#include <stdio.h>
#include <math.h>

int main(void)
{
    float step;
    float x = 11;
    float y = 4;

    step = ceil(x / y);
    printf("%f", step);

    return 0;
}