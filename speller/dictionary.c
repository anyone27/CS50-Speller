// Implements a dictionary's functionality

#include <stdbool.h>

#include "dictionary.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 4834435;

// Hash table
node *table[N];
node *n;
node *list = NULL;

long count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int c = strlen(word);
    char low[c];
    strcpy(low, word);
    for (int i = 0; i < c; i++)
    {
        char j = tolower(low[i]);
        low[i] = j;
    }

    // printf("Low: %s\n", low);
    int pos = hash(low);

    // printf("Hash check: %i\n", pos);
    for (node *tmp = table[pos]; tmp != NULL; tmp = tmp->next)
    {
        char *check = tmp->word;
        if (strcmp(check, low) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO

    // Source: DJBX33A (Daniel J. Bernstein, Times 33 with Addition)

    unsigned int hash = 5381;
    unsigned int i = 0;
    unsigned int len = strlen(word);

    for (; i < len; word++, i++)
    {
        hash = ((hash << 5) + hash) + (*word);
    }

    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO

    FILE *inptr = fopen(dictionary, "r");
    if (inptr == NULL)
    {
        return false;
    }

    char buffer[LENGTH + 1];
    while (fscanf(inptr, "%s", buffer) == 1)
    {

        //HASH FUNCTION
        int pos = hash(buffer);

        //INSERT TO HASH TABLE
        n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        strcpy(n->word, buffer);
        n->next = list;

        list = n;
        table[pos] = list;
        count++;

    }
    fclose(inptr);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (!(&load))
    {
        return 0;
    }
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    if (list != NULL)
    {
        while (list != NULL)
        {
            node *tmp = list->next;
            free(list);
            list = tmp;
        }
        return true;
    }
    return false;
}
