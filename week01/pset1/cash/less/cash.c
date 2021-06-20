// Find out the minimum number of coins for change, coins in denominations of 25, 10, 5, 1 cent

#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float dollars;
    do
    {
        dollars = get_float("Change owed: ");
    }
    while (dollars <= 0);

    int cents = round(dollars * 100);

    int count = 0;

    count = cents / 25;
    cents = cents % 25;

    count += cents / 10;
    cents = cents % 10;

    count += cents / 5;
    cents = cents % 5;

    count += cents;

    printf("%i\n", count);
}