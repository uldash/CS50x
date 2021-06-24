#include <cs50.h>
#include <stdio.h>

int main(int argc, string argv[])
{
    // printf("%s\n", argv[0]); // program name
    if (argc == 2)
    {
        printf("hello, %s\n", argv[1]);
    }
    else
    {
        printf("hello, world\n");
    }
}