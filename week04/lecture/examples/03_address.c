#include <stdio.h>

int main(void)
{
    // string s = "HI!";
    char *s = "HI!";
    printf("%c\n", *s);
    printf("%c\n", *(s+1));
    printf("%c\n", *(s+2));
}