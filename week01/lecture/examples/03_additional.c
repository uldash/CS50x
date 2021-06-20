#include <stdio.h>
#include <cs50.h>

int main(void){
    int x = get_int("x: ");
    int y = get_int("y: ");
    printf("%i + %i = %i\n", x, y, x + y);
}