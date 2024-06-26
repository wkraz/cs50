// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

int counter = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int TABLE_SIZE = 25000; // highest ascii value we can get is 26, max length is 45, *
                                       // 13 at end => # buckets = 26 * 45 * 13 = 15210
// I ended up going with 25000 because it was slightly faster than 15210
/*
Holmes results:
15210: 6.61
75000: 6.46
25000: 6.46
250000: 6.61
7500: 6.81

*/

// Hash table
node *table[TABLE_SIZE];

// Returns true if word is in dictionary, else false
// compare it to hash table
bool check(const char *word)
{
    // TODO
    int l = strlen(word);
    char lowerword[l + 1];
    for (int i = 0; i < l; i++)
    {
        lowerword[i] = tolower(word[i]);
    }
    lowerword[l] = '\0';
    unsigned int index = hash(lowerword); // hash word to get index
    node *cursor = table[index];
    while (cursor != NULL)
    {
        if (strcmp(lowerword, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
// Hash function: add up every ascii value in the word and multiply by 13 at the end
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    int bucket = 0;
    int l = strlen(word);
    char lowerword[l + 1];
    for (int i = 0; i < l; i++)
    {
        lowerword[i] = tolower(word[i]);
    }
    lowerword[l] = '\0';
    for (int i = 0; i < l; i++)
    {
        if (isalpha(lowerword[i]) != 0)
        {
            bucket += lowerword[i] - 97; // if not apostrophe, assign it to 0-25
        }
        else
        {
            bucket += 26; // if apostrophe, assign it to 26
        }
    }
    bucket *= 13;
    return bucket;

    // cs50 hash function: return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // read file
    FILE *f = fopen(dictionary, "r");
    if (f == NULL)
    {
        printf("Loading unsuccessful.\n");
        return false;
    }
    // read each word & add to hash file
    char wordList[LENGTH + 1];
    while (fscanf(f, "%s", wordList) != EOF)
    {
        counter++;
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("Error. Could not load.\n");
            return false;
        }
        strcpy(n->word, wordList);
        n->next = NULL;             // end of linked list so point to null
        int index = hash(wordList); // seeing what bucket to put this in --- implement later
        if (table[index] == NULL)
        {
            table[index] = n;
        }
        else
        {
            n->next = table[index];
            table[index] = n;
        }
    }

    // close file

    fclose(f);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // Have to free every node on every linked list basically
    node *cursor = NULL;
    node *tmp = NULL;
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        cursor = table[i];
        while (cursor != NULL)
        {
            tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
