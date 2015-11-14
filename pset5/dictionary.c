/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// children per node (one for every lowercase character and apostrophe)
#define CHILDREN 27

// prototypes
bool add_word(const char* word);
int get_node_index(char c);

// in memory dictionary
node tree;

// words in dictionary
int words = 0;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // just return if word is NULL or empty
    if ((word == NULL) || (strlen(word) == 0))
    {
        return false;
    }

    // start at the beginning of dictionary
    node* curNode = &tree;

    // check each character
    for (int i = 0; word[i] != '\0'; ++i)
    {
        // get character node index
        int nodeIndex = get_node_index(word[i]);

        // get node for character
        curNode = curNode->children[nodeIndex];

        // word isn't in dictionary
        if (curNode == NULL)
        {
            return false;
        }
    }

    return curNode->data;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // open dictionary file
    FILE* file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return false;
    }

    // initialize dictionary
    if (!init_node(&tree, CHILDREN))
    {
        printf("Could not initialize dictionary.");
        fclose(file);
        return false;
    }

    words = 0;

    char word[LENGTH+1];

    // load each word from dictionary file
    while (EOF != fscanf(file, "%s", word))
    {
        // add word to dictionary
        if (!add_word(word))
        {
            printf("Could not add %s to dictionary.", word);
            fclose(file);
            return false;
        }
        words++;
    }

    // close dictionary file
    fclose(file);

    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return words;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    words = 0;
    return destroy_node(&tree);
}

/**
 * Adds a word to the dictionary.  Returns true if successful else false.
 */
bool add_word(const char* word)
{
    // just return if word is NULL or empty
    if ((word == NULL) || (strlen(word) == 0))
    {
        // consider this successful
        return true;
    }

    // start at the beginning of dictionary
    node* curNode = &tree;

    // add each character
    for (int i = 0; word[i] != '\0'; ++i)
    {
        // get character node index
        int nodeIndex = get_node_index(word[i]);

        // get node for character
        node* charNode = curNode->children[nodeIndex];

        // create node for character if it doesn't exist
        if (charNode == NULL)
        {
            charNode = malloc(sizeof(node));

            // out of memory
            if (charNode == NULL)
            {
                printf("Could not allocate memory for character node.");
                return false;
            }

            // initialize new node
            bool result = init_node(charNode, CHILDREN);

            if (!result)
            {
                printf("Could not initialize character node.");
                return false;
            }

            // insert node into dictionary
            curNode->children[nodeIndex] = charNode;
        }

        // update current node for next character
        curNode = charNode;
    }

    // mark node as a word
    curNode->data = true;

    return true;
}

/**
 * Returns corresponding node index for given character.
 */
int get_node_index(char c)
{
    // default return value to apostrophe index
    int index = CHILDREN - 1;

    if (isalpha(c))
    {
        index = tolower(c) - 'a';
    }

    return index;
}

/**
 * Initializes node:
 * - data set to false
 * - allocate memory for specified number of children node pointers
 * - each child node pointer set to NULL
 *
 * Returns true if successful else false.
 */
bool init_node(node* n, int count)
{
    // can't initialize NULL pointer
    if (n == NULL)
    {
        return false;
    }

    n->data = false;
    n->maxChildren = count;
    n->children = calloc(count, sizeof(*n->children));

    return (n->children != NULL);
}

/**
 * Recursively cleans up memory allocated for this node and all children.
 * Returns true if successful else false.
 */
bool destroy_node(node* n)
{
    // no need to destroy NULL pointer
    if (n == NULL)
    {
        return true;
    }

    // clean up all children
    for (int i = 0; i < n->maxChildren; ++i)
    {
        destroy_node(n->children[i]);
        free(n->children[i]);
        n->children[i] = NULL;
    }

    // clean up pointer to children
    free(n->children);

    return true;
}
