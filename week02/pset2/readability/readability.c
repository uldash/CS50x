#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>
#include <math.h>


// https://cs50.harvard.edu/x/2021/psets/2/readability/

int coleman_liau_index(int letter, int word, int sentence);

int main(void)
{
    string text = get_string("Text: ");

    int letter = 0, word = 1, sentence = 0, index;
    char c;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        c = toupper(text[i]);
        if (c >= 'A' && c <= 'Z')
        {
            letter++;
        }

        if (c == ' ')
        {
            word++;
        }

        if (c == '.' || c == '!' || c == '?')
        {
            sentence++;
        }
    }

    // printf("%i letter(s)\n", letter);
    // printf("%i word(s)\n", word);
    // printf("%i sentence(s)\n", sentence);

    index = coleman_liau_index(letter, word, sentence);
    if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

int coleman_liau_index(int letter, int word, int sentence)
{
    return round(0.0588 * (letter * 100.0 / word) - 0.296 * (sentence  * 100.0 / word) - 15.8);
}