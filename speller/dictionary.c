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
const unsigned int N = 26;

// Hash table
node *table[N];
node *n;
node *list = NULL;

long count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    char *low[LENGTH + 1];
    strcpy(low, word);
    for (int i = 0; i < (LENGTH + 1); i++)
    {
        int c = tolower(low[i]);
        low[i] = c;
    }
    int pos = hash(word);

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
   int pos = word[0];
   return pos;
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
        // printf("Hash pos: %i\n", pos);
        // printf("Word to add: %s\n", buffer);
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
    for (int i = 0; i < N; i++)
    {
        while (table[i] != NULL)
        {
            node *tmp = table[i]->next;
            free(table[i]);
            table[i] = tmp;
        }
        return true;
    }
    {
        return false;
    }
}
