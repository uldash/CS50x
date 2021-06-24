#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>
#include <math.h>


// https://cs50.harvard.edu/x/2021/psets/2/substitution
// YTNSHKVEFXRBAUQZCLWDMIPGJO

string crypt_substitution(string key, string text);
bool has_dublicate(int count, string text);
bool is_bad_key(string key);

int main(int argc, string argv[])
{
    if (argc != 2 || is_bad_key(argv[1]))
    {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }

    string text = get_string("plaintext: ");
    printf("ciphertext: %s\n", crypt_substitution(argv[1], text));

}

bool is_bad_key(string key)
{
    if (strlen(key) != 26)
    {
        return true;
    }

    for (int i = 0, n = strlen(key); i < n; i++)
    {
        if (!isalpha(key[i]))
        {
            return true;
        }
        if (has_dublicate(i, key))
        {
            return true;
        }

    }

    return false;
}

bool has_dublicate(int count, string text)
{
    for (int i = count + 1, n = strlen(text); i < n; i++)
    {
        if (toupper(text[count]) == toupper(text[i]))
        {
            return true;
        }
    }

    return false;
}

string crypt_substitution(string key, string text)
{
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            if (islower(text[i]))
            {
                // printf("%i\n", text[i] - 'a');
                text[i] = tolower(key[text[i] - 'a']);
            }
            else
            {
                // printf("%i\n", text[i] - 'A');
                text[i] = toupper(key[text[i] - 'A']);
            }
        }
    }
    return text;
}