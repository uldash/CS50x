#include <stdio.h>
#include <cs50.h>

const int TOTAL = 3;

float average(int length, int array[]);

int main(void)
{
    // int score1 = 72;
    // int score2 = 73;
    // int score3 = 33;
    int scores[TOTAL];

    for(int i = 0; i < TOTAL; i++)
    {
        scores[i] = get_int("Score:");
    }

    printf("Average: %.*f\n", 3, average(TOTAL, scores));
}

float average(int length, int array[])
{
    int sum = 0;
    for(int i = 0; i < length; i++)
    {
        sum += array[i];
    }
    return sum / (float) length;
}