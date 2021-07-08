// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

unsigned int dsize = 0;

// Number of buckets in hash table
const unsigned int N = 10000;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    //printf("WORD: %s", word);

    // TODO
    node *p = table[hash(word)];
    if (p == NULL)
    {
        return false;
    }
    while (p != NULL)
    {
        if (!strcasecmp(word, p->word))
        {
            //printf("\tTRUE\t");
            return true;
        }
        else
        {
            p = p->next;
            // printf("\tFALSE\t");
        }
    }

    //printf("\n");
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    //return (unsigned int)((tolower(word[0]) - 'a') % N) ;
    int tmp = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        tmp += tolower(word[i]);
    }
    return tmp;
}

// PRINT LIST
void print_list(void)
{
    for (unsigned int i = 0; i < N; i++)
    {
        node *p;
        p = table[i];
        if (p == NULL)
        {
            printf("%i:\tNULL\n", i);
        }
        else
        {
            printf("%i:\t", i);
            do
            {
                printf("%s ", p->word);
                p = p->next;
            }
            while (p != NULL);
            printf("\n");
        }
    }
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    for (unsigned int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    char word[LENGTH + 1];
    unsigned int h = 0;
    node *n = NULL;
    node *tmp = NULL;

    while (fscanf(file, "%s", word) != EOF)
    {
        // printf("Word: %s\tHash: %i\n", word, hash(word));

        n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        strcpy(n->word, word);
        n->next = NULL;
        dsize++;

        h = hash(word);
        if (table[h] != NULL)
        {
            n->next = table[h];
        }
        table[h] = n;
    }

    // print_list();
    // printf("Dictionary size: %u\n", dsize);
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return dsize;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    node *p;
    for (unsigned int i = 0; i < N; i++)
    {
        p = table[i];
        while (p != NULL)
        {
            node *tmp = p->next;
            free(p);
            p = tmp;
        }
    }
    return true;
}
