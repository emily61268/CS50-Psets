// Implements a dictionary's functionality

#include <cs50.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>


#include "dictionary.h"
#include "node.h"

node *hashtable[70000] = {NULL};
int count = 0;
// hash function. reference: commonly used hash functions: https://gist.github.com/qxj/1520414
unsigned int hashing(char *str)
{
    unsigned int seed = 131;
    unsigned int hash = 0;
    while (*str)
    {
        hash = hash * seed + tolower(*str++);
    }
    return hash % 70000;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    char *tword = (char *) word;
    int h = hashing(tword);
    node *cursor = hashtable[h];

    while (cursor != NULL)
    {
        if (!strcasecmp(tword, cursor -> word))
        {
            return true;
        }
        else
        {
            cursor = cursor -> next;
        }
    }
    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{

    char word[LENGTH + 1];
    FILE *file = fopen(dictionary, "r");

    while (fscanf(file, "%s", word) != EOF)
    {
        // create a new node
        node *new_node = malloc(sizeof(node));
        // check if new_node is null
        if (new_node == NULL)
        {
            unload();
            return false;
        }
        // if new_node is not null, copy word to new_node and point it to null
        strcpy(new_node -> word, word);
        new_node -> next = NULL;
        int h = hashing(new_node -> word);
        // check if the first node is empty
        if (hashtable[h] == NULL)
        {
            // if the first node is empty, point the first node to the new_node
            hashtable[h] = new_node;
        }
        else
        {
            if (!new_node -> next)
            {
                // point the new_node to the node that the first node is pointing at to maintain the chain
                new_node -> next = hashtable[h];
                // move the first node pointer to point to the new_node
                hashtable[h] = new_node;
            }
        }
        // increment dictionary word count
        count++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (&load)
    {
        return count;
    }
    else
    {
        return 0;
    }
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // check if the dictionary is loaded
    if (&load)
    {
        for (int i = 0; i < 70000; i++)
        {
            if (hashtable[i] != NULL)
            {
                node *cursor = hashtable[i];
                while (cursor != NULL)
                {
                    node *tmp = cursor;
                    cursor = cursor -> next;
                    free(tmp);
                }
            }
        }
        return true;
    }
    else
    {
        return false;
    }
}
