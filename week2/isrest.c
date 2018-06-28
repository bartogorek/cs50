
#include <stdio.h>
#include <string.h>
#include <cs50.h>

int main(void)
{
    string test = get_string("your string : ");

    if (strcmp(test, "") == 0)
    {
        printf("Empty line\n");
    }
    else
    {
        printf("Your string : %s", test);
    }
    return 0;
}