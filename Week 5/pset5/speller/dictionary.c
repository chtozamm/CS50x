// Implements a dictionary's functionality

/*

    QUESTIONS:

    Q1: Could load() function be implemented with fread() instead of fscanf()?
    A1:

*/

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a number of words loaded from dictionary
int word_count = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Represents a number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

/*
________________________________________________________________________
    FUNCTIONS:
    - load
    - hash
    - check
    - unload
________________________________________________________________________
*/

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Couldn't open %s\n", dictionary);
        return false;
    }

    // Scan dictionary word by word and populate hash table with nodes containing words found in dictionary
    char buffer[LENGTH + 1];
    while (fscanf(file, "%s", buffer) != EOF)
    {
        // Create new node
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            printf("Failed to allocate memory for 'node *new_node'.\n");
            unload();
            return false;
        }

        // Copy word from file to the node
        strcpy(new_node->word, buffer);
        new_node->next = NULL;

        // Hash word to obtain a hash value
        int hash_index = hash(new_node->word);

        // Insert new node at the beginning of the list
        node *head = table[hash_index];
        if (head == NULL)
        {
            table[hash_index] = new_node;
            word_count++;
        }
        else
        {
            new_node->next = table[hash_index];
            table[hash_index] = new_node;
            word_count++;
        }
    }

    fclose(file);
    return true;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    return toupper(word[0]) - 'A';
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Returns true if word is in dictionary, else false
bool check(const char *word)
{

    int hash_index = hash(word);

    if (table[hash_index] == NULL)
        return false;

    node *temp_node = table[hash_index];

    while (temp_node->next != NULL && strcasecmp(temp_node->word, word) != 0)
    {
        temp_node = temp_node->next;
    }

    if (strcasecmp(temp_node->word, word) == 0)
        return true;

    return false;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{

    for (int i = 0; i < N; i++)
    {
        if (table[i] == NULL)
            continue;

        node *head = table[i];
        node *cursor = head;

        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }

    return true;
}
