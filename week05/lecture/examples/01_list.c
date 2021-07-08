#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    // int list[3];

    // list[0] = 1;
    // list[1] = 2;
    // list[2] = 3;

    // for (int i = 0; i < 3; i++)
    // {
    //     printf("%i\n", list[i]);
    // }

    int *list = malloc(3 * sizeof(int));

    if (list == NULL)
    {
        return 1;
    }

    *list = 1;
    *(list + 1) = 2;
    *(list + 2) = 3;

    for (int i = 0; i < 3; i++)
    {
        printf("%i\n", list[i]);
    }
    printf("\n");

    int *tmp = malloc(4*sizeof(int));
    if (tmp == NULL)
    {
        free(list);
        return 1;
    }

    for (int i = 0; i < 3; i++)
    {
        tmp[i] = list[i];
    }
    tmp[3] = 4;
    free(list);

    list = tmp;

    for (int i = 0; i < 4; i++)
    {
        printf("%i\n", list[i]);
    }
    // free(tmp);
    // free(list);
}