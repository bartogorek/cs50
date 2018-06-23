#include <stdio.h>

int main(void)
{
    long long n1[2] = {34, 98};
    long long n2[2] = {51, 67};

    long long s1 = n1[0];
    long long s2 = n2[0];

    for (long long i = 1; i < n1[1]; i++)
    {
    s1 = s1 * n1[0];
    }

    for (long long i = 1; i < n2[1]; i++)
    {
    s2 = s2 * n2[0];
    }

    if (s1 > s2)
    {
        printf("-1\n");
        return -1;
    }
    else if (s1 == s2)
    {
        printf("0\n");
        return 0;
    }
    else
    {
        printf("1\n");
        return 1;
    }
}