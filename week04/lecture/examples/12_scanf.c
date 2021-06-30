#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    //char *s = malloc(sizeof(char) * 4);
    char s[4];
    printf("s: ");
    scanf("%s", s);
    printf("s: %s\n", s);
    // free(s)
}