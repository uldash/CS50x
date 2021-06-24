#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>
#include <math.h>


// https://cs50.harvard.edu/x/2021/psets/2/caesar/

bool is_bad_digit(string key);
string crypt_caesar(int key, string text);

int main(int argc, string argv[])
{
    if (argc != 2 || is_bad_digit(argv[1]) || atoi(argv[1]) < 0)
    {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }

    string text = get_string("plaintext: ");
    printf("ciphertext: %s\n", crypt_caesar(atoi(argv[1]), text));

}

bool is_bad_digit(string key)
{
    for (int i = 0; key[i] != '\0'; i++)
    {
        if (!isdigit(key[i]))
        {
            return true;
        }
    }
    return false;
}

string crypt_caesar(int key, string text)
{
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            if (islower(text[i]))
            {
                text[i] = (text[i] + key - 'a') % 26 + 'a';
            }
            else
            {
                text[i] = (text[i] + key - 'A') % 26 + 'A';
            }
        }
    }
    return text;
}