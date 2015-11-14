/****************************************************************************
 * dictionary.h
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Declares a dictionary's functionality.
 ***************************************************************************/

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word);

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary);

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void);

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void);

typedef struct node
{
    // indicates completion of dictionary key
    bool data;

    // max number of children
    int maxChildren;

    // collection of pointers to other nodes
    struct node** children;
} node;

/**
 * Initializes node:
 * - data set to false
 * - allocate memory for specified number of children node pointers
 * - each child node pointer set to NULL
 *
 * Returns true if successful else false.
 */
bool init_node(node* n, int count);

/**
 * Recursively cleans up memory allocated for this node and all children.
 * Returns true if successful else false.
 */
bool destroy_node(node* n);

#endif // DICTIONARY_H
