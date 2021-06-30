#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

void draw(int h);

int main(void)
{
    int height = get_int("Height: ");
    draw(height);
}

// void draw(int h)
// {
//     for (int i = 1; i <= h; i++)
//     {
//         for (int j = 1; j <= i; j++)
//         {
//             printf("#");
//         }
//         printf("\n");
//     }
// }

void draw(int h)
{
    if (h == 0)
    {
        return;
    }
    else
    {
        draw(h - 1);
    }
    for(int i = 0; i < h; i++)
    {
        printf("#");
    }
    printf("\n");
}