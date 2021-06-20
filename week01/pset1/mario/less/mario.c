#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int h;
    do
    {
        h = get_int("Height: ");
    }
    while (1 > h || h > 8);

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < h; j++)
        {
            if (j > h - i - 2)
            {
                printf("%s", "#");
            }
            else
            {
                printf("%s", " ");
            }
        }
        printf("\n");
    }
}