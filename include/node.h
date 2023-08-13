#ifndef _NODE_H_
#define _NODE_H_

#include <stdio.h>
#include <stdlib.h>

#define RED_COLOUR printf("\033[1;31m");
#define NORMAL_COLOUR printf("\033[0m");

typedef float data_type;

typedef struct Node{
    int row;
    int column;
    data_type value;
    struct Node *column_next;
    struct Node *row_next;
} Node;

/**
 * @brief Construct a new Node.
 * Allocates memory for a new node and returns a pointer to it.
 * @param row 
 * Row coordinate of the node.
 * @param column 
 * Column coordinate of the node.
 * @param value 
 * Value of the node.
 * @param row_next 
 * Pointer to the next node in the row.
 * @param column_next 
 * Pointer to the next node in the column.
 * @return Node* 
 * Pointer to the newly allocated node.
 * @note Complexity O(1), as all its operations are linear and don't depend on any iteration.
 */
Node *node_construct(int row, int column, data_type value, Node *row_next, Node *column_next);

/**
 * @brief Destroys the node.
 * Frees the memory allocated.
 * @param n 
 * Pointer to the node.
 * @note Complexity O(1), as all its operations are linear and don't depend on any iteration.
 */
void node_destroy(Node *n);

/**
 * @brief Saves node in a binary file.
 * @param n 
 * Pointer to the node.
 * @param file 
 * File where the binary is going to be saved in.
 * @note Complexity O(1), as all its operations are linear and don't depend on any iteration.
 */
void save_binary_nodes(Node* n, FILE* file);

/**
 * @brief Changes a value of a previously allocated node.
 * @param n 
 * Pointer of the node that is going to be changed.
 * @param row 
 * Row coordinate of the node.
 * @param value 
 * Value that is going to be stored in the node.
 * @note Complexity O(n). Where "n" is the number of nodes in the row.
 * The complexity of this function depends on its only loop.
 */
void change_node_value(Node* n, int row, data_type value);

#endif
