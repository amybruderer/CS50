/****************************************************************************
 * node.h
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Declares a node's structure.
 ***************************************************************************/

#include <stdlib.h>

#include "node.h"

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
