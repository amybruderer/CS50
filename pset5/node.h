/****************************************************************************
 * node.h
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Declares a node's structure.
 ***************************************************************************/

#ifndef NODE_H
#define NODE_H

#include <stdbool.h>

typedef struct node
{
    // indicates completion of dictionary key
    bool data;
    
    // collection of pointers to other nodes
    struct node** children;
} node;

/**
 * Initializes node:
 * - data set to false
 * - allocate memory for specified number of children node pointers
 * - each child node pointer set to NULL
 */
void init_node(node* n, int count);

#endif // NODE_H
