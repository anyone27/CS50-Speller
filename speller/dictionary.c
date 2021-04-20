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

long count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int pos = hash(word);
    for (node *tmp = table[pos]; tmp != NULL; tmp = tmp->next)
    {
        if (tmp->word == word)
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
    int pos1 = 0;
    // int pos2 = 0;
    // int pos3 = 0;

    pos1 = (tolower(word[0]) - 97);
    return pos1;

    // if (strlen(word) == 1)
    // {
    //     pos1 = (tolower(word[0]) - 97);
    //     printf("Pos1: %i\n", pos1);
    //     return pos1;
    // }
    // else if (strlen(word) == 2)
    // {
    //     pos1 = (tolower(word[0]) - 97)*26;
    //     pos2 = (tolower(word[1]) - 97)*26*26;
    //     return pos1 + pos2;
    //     printf("Pos1: %i\n", pos1);
    //     printf("Pos2: %i\n", pos2);
    // }
    // else
    // {
    //     pos1 = (tolower(word[0]) - 97)*26;
    //     pos2 = (tolower(word[1]) - 97)*26*26;
    //     pos3 = (tolower(word[2]) - 97)*26*26*26;
    //     return (pos1+pos2+pos3);
    //     printf("Pos1: %i\n", pos1);
    //     printf("Pos2: %i\n", pos2);
    //     printf("Pos3: %i\n", pos3);
    // }

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

    char buffer[LENGTH +1];
    while (fscanf(inptr, "%s", buffer) == 1)
    {

        //HASH FUNCTION
        int pos = hash(buffer);
        printf("Hash pos: %i\n", pos);
        //INSERT TO HASH TABLE
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        n->next = NULL;
        strcpy(n->word, buffer);
        table[pos]->next = n;
        count++;
        fclose(inptr);

    }
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
