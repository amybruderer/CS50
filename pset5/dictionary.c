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

#include "dictionary.h"
#include "node.h"

// children per node (one for every lowercase character and apostrophe)
#define CHILDREN 27

// prototypes
void add_word(const char* word);
int get_node_index(char c);

// in memory dictionary
node tree;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // TODO
    return false;
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
    init_node(&tree, CHILDREN);

    char word[LENGTH+1];

    // load each word from dictionary file
    while (EOF != fscanf(file, "%s", word))
    {
        // add word to dictionary
        add_word(word);
    }

    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    return 0;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    return false;
}

/**
 * Adds a word to the dictionary.
 */
void add_word(const char* word)
{
    // just return if word is NULL
    if (word == NULL)
    {
        return;
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
            charNode = malloc(sizeof(tree));

            // initialize new node
            init_node(charNode, CHILDREN);

            // insert node into dictionary
            curNode->children[nodeIndex] = charNode;
        }

        // update current node for next character
        curNode = charNode;
    }

    // mark node as a word
    curNode->data = true;
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
        index = c - 'a';
    }

    return index;
}
