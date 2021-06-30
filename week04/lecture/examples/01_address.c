#include <stdio.h>

int main(void)
{
    int n = 50;
    int *p = &n;
    // printf("%i\n", *&n); // 50
    // printf("%p\n", &n);  // address
    // printf("%i\n", *&n); // 50
    // printf("%p\n", p); // address
    printf("%i\n", *p); // address
}