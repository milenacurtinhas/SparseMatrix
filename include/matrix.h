#ifndef _MATRIX_H_
#define _MATRIX_H_

#include "node.h"

typedef struct Matrix{
    struct Node **column_head;
    struct Node **row_head;
    int column_size;
    int row_size;
} Matrix;

/**
 * @brief Construct a new Matrix.
 * Allocates memory for a new matrix and returns a pointer to it.
 * @param row 
 * Matrix column size.
 * @param column 
 * Matrix column size.
 * @return Matrix*
 * Pointer to the newly allocated matrix.
 * @note Complexity O(n). Being "n" the amount of times the calloc funtion is multiplied, i.e. row + column.
 * The other operations of the function have O(1) complexity, which makes the function a O(n).
 */
Matrix* matrix_construct(int row, int column);

/**
 * @brief Destroys the matrix.
 * Frees the memory allocated.
 * @param m 
 * Pointer to the matrix.
 * @note Complexity O(n). Being "n" the number of rows in the matrix multiplied by the number of nodes contained in each row.
 * The complexity is defined by the loop that has a inner loop.
 * The external loop is defined by the quantity of rows in the matrix, the inner loop is defined by the quantity of allocated nodes in each row.
 * The other operations of the function have O(1) complexity, which makes the function a O(n).
 */
void matrix_destroy(Matrix* m);

/**
 * @brief Saves matrix in a binary file.
 * @param m 
 * Pointer to the matrix.
 * @param file
 * File where the binary is going to be saved in.
 * @note Complexity O(n). Being "n" the number of rows in the matrix multiplied by the number of nodes contained in each row.
 * The complexity is defined by the loop that has a inner loop.
 * The external loop is defined by the quantity of rows in the matrix, the inner loop is defined by the quantity of allocated nodes in each row.
 * The other operations of the function have O(1) complexity, which makes the function a O(n).
 */
void save_binary_matrix(Matrix* m, FILE* file);

/**
 * @brief Reads a matrix from a binary file.
 * Allocate memory for the matrix.
 * @param file 
 * Binary file where the matrix is saved in.
 * @return Matrix* 
 * Pointer to the newly read and allocated matrix.
 * @note Complexity O(n). Where "n" is the number of entries in the matrix.
 * While it is reading information for the "matrix_set" it keeps in the loop.
 * The other operations of the function have O(1) complexity, which makes the function a O(n).
 */
Matrix* read_binary_matrix(FILE* file);

/**
 * @brief Prints only the not null elements of a matrix.
 * It displays the coordinates and the value of a not null position.
 * @param m 
 * Pointer to the matrix to be printed.
 * @note Complexity O(n * m). Being "n" the number of rows in the matrix and "m" the number of nodes contained in each row.
 * The complexity is defined by the loop that has a inner loop.
 * The external loop is defined by the quantity of rows in the matrix, the inner loop is defined by the quantity of allocated nodes in each row.
 * The other operations of the function have O(1) complexity.
 */
void print_sparse_matrix(Matrix* m);

/**
 * @brief Prints all elements of a matrix.
 * It displays all values in its position.
 * @param m 
 * Pointer to the matrix to be printed.
 * @note Complexity O(n * m). Being "n" the number of rows in the matrix and "m" the number of nodes contained in each row.
 * The complexity is defined by the loop that has a inner loop.
 * The external loop is defined by the quantity of rows in the matrix, the inner loop is defined by the quantity of allocated nodes in each row.
 * The if-else conditions inside the loop can be counted as constant for each row.
 * The other operations of the function have O(1) complexity.
 */
void print_dense_matrix(Matrix* m);

/**
 * @brief It nulls a element that was already allocated.
 * If there was a not null element that needs to be turned into a null one
 * it turns it into a null element, linking the previous and next elements to each other
 * and it free the previous allocated element.
 * @param m
 * Pointer to the matrix where the change is going to be happening in.
 * @param row
 * Coordinate to the the row where the element is.
 * @param column 
 * Coordinate to the the column where the element is.
 * @param column_aux 
 * Pointer to the node that contains the head of the column where the element in the matrix.
 * @param row_aux 
 * Pointer to the node that contains the head of that row where the element in the matrix.
 * @note Complexity O(n). Where "n" represents the number of nodes in the column or row, which can range from 1 to "n".
 * The other operations of the function have O(1) complexity, which makes the function a O(n).
 */
void set_null_value(Matrix* m, int row, int column, Node* column_aux, Node* row_aux);

/**
 * @brief Adds a not null element to the matrix.
 * Allocates memory for a new node and inserts it in its place in the matrix.
 * @param m 
 * Pointer to the matrix where the node is going to be added.
 * @param row 
 * Coordinate to the row where the element is going to be added.
 * @param column 
 * Coordinate to the column where the element is going to be added.
 * @param column_aux 
 * Pointer to the node that contains the head of that column where the new node is going to be placed in the matrix.
 * @param row_aux 
 * Pointer to the node that contains the head of that row where the new node is going to be placed in the matrix.
 * @param value 
 * Value of the node that is going to be added in the matrix.
 * @note Complexity can range between O(n) and O(1). The complexity in this function is determined by the loops or the insertion of nodes in the matrix.
 * The loops depend on the row or column size of the matrix, i.e. O(n), where "n" is the size of rows and columns.
 * The insertion of nodes in the matrix dependes on the position of insertion.
 * The worst case is the node being inserted in the beginning or ending, making the function O(n), where "n" is the number of nodes in the column.
 * The best case is the node being inserted in the middle of the linked list, making the complexity O(1).
 * The other operations of the function have O(1) complexity.
 */
void set_value(Matrix* m, int row, int column, Node* column_aux, Node* row_aux, data_type value);

/**
 * @brief Makes changes in the nodes of the matrix.
 * It adds a new node in the matrix or it changes a existing a node to a null one.
 * @param m 
 * Pointer to the matrix where the changes of nodes are going to be happening.
 * @param row 
 * Coordinate to the row where the element is going to be changed.
 * @param column 
 * Coordinate to the column where the element is going to be changed.
 * @param val 
 * Value of the element that is going to be changed.
 * @note Complexity can range between O(n) an O(1), as it depends and the other functions called in this one.
 * The functions called depend on the number of nodes in the columns and rows, that's it ranges from the worst and best case.
 * The other operations of the function have O(1) complexity.
 */
void matrix_set(Matrix* m, int row, int column, data_type val);

/**
 * @brief Returns the data stored in the node at the given index.
 * @param m 
 * Pointer to the matrix.
 * @param row 
 * Coordinate to the row where the node is.
 * @param column 
 * Coordinate to the column where the node is.
 * @return float 
 * Data stored in the node at the given index.
 * @note Complexity can range between O(n) and O(1). Where "n" represents the number of nodes in the column.
 * The complexity of this function is defined by the only loop in it.
 * The other operations of the function have O(1) complexity.
 */
float read_value(Matrix* m, int row, int column);

/**
 * @brief Adds two matrices.
 * @param m1 
 * Pointer to one of the matrices of the operation.
 * @param m2 
 * Pointer to the other matrix of the operation.
 * @return Matrix* 
 * Pointer to matrix that contains the result of the operation.
 * @note Complexity O(n * m). Being "n" the size of the rows an "m" the size of the columns.
 * The complexity of this function is defined by the two loops in it. 
 * One that uses the row size as a parameter and the other that use the column size.
 * The other operations of the function have O(1) complexity.
 */
Matrix* add_matrices(Matrix* m1, Matrix* m2);

/**
 * @brief Multiply a matrix by a scalar number
 * @param m1 
 * Pointer to the matrix where the operation is happening.
 * @param scalar 
 * Scalar number of the operation.
 * @return Matrix* 
 * Pointer to matrix that contains the result of the operation
 * @note Complexity O(n * m). Being "n" the number of rows in the matrix and "m" the number of nodes contained in each row.
 * The complexity is defined by the loop that has a inner loop.
 * The external loop is defined by the quantity of rows in the matrix, the inner loop is defined by the quantity of allocated nodes in each row.
 * The other operations of the function have O(1) complexity.
 */
Matrix* matrix_scalar_mult(Matrix* m1, data_type scalar);

/**
 * @brief Multiplys a matrix by another.
 * @param m1 
 * Pointer to one of the matrices of the operation.
 * @param m2 
 * Pointer to the other matrix of the operation.
 * @return Matrix* 
 * Pointer to matrix that contains the result of the operation.
 * @note O(m * n * o). Being "m" the row size of the first matrix, "n" the column size of the first matrix and "o" the column size of the second matrix.
 * The complexity of this function is defined by the three loops contained in it.
 * Each of the loops (that are one inside of the other) are ruled respectively by "m", "n" and "o".
 * The other operations of the function have O(1) complexity.
 */
Matrix* matrix_matrix_mult(Matrix* m1, Matrix* m2);

/**
 * @brief Multiplys a matrix by another point by point.
 * @param m1 
 * Pointer to one of the matrices of the operation.
 * @param m2 
 * Pointer to the other matrix of the operation.
 * @return Matrix* 
 * Pointer to matrix that contains the result of the operation.
 * @note O(m*n), being "m" the row size of the matrices and "n" being the max(column_size_of_matrix1, column_size_of_matrix2).
 * The complexity is defined by the two loops.
 * The first one is commanded by the general row size of the matrices. 
 * The second one is commanded by the maximum number of columns allocated between the two matrices.
 */
Matrix* matrix_point_by_point_mult(Matrix* m1, Matrix* m2);

/**
 * @brief Swaps two rows of matrix.
 * @param m1 
 * Pointer to the matrix where the operation is happening.
 * @param r1 
 * Coordinate of the row that is going to be swaped. 
 * @param r2 
 * Coordinate of the row that is going to be swaped. 
 * @return Matrix* 
 * Pointer to matrix that contains the result of the operation.
 * @note Complexity O(n * m). Being "n" the number of rows in the matrix and "m" the number of nodes contained in each row.
 * The complexity is defined by the loop that has three inner loops.
 * Although it has three loops, only one is going to be executed each time the outer loop runs.
 * The external loop is defined by the quantity of rows in the matrix, the inner loop is defined by the quantity of allocated nodes in each row.
 * The other operations of the function have O(1) complexity.
 */
Matrix* matrix_swap_rows(Matrix* m1, int r1, int r2);

/**
 * @brief Swaps two columns of matrix.
 * @param m1 
 * Pointer to the matrix where the operation is happening.
 * @param c1 
 * Coordinate of the column that is going to be swaped. 
 * @param c2 
 * Coordinate of the column that is going to be swaped. 
 * @return Matrix* 
 * Pointer to matrix that contains the result of the operation.
 * @note Complexity O(n * m). Being "n" the number of columns in the matrix and "m" the number of nodes contained in each column.
 * The complexity is defined by the loop that has three inner loops.
 * Although it has three loops, only one is going to be executed each time the outer loop runs.
 * The external loop is defined by the quantity of columns in the matrix, the inner loop is defined by the quantity of allocated nodes in each row.
 * The other operations of the function have O(1) complexity.
 */
Matrix* matrix_swap_columns(Matrix* m1, int c1, int c2);

/**
 * @brief Creates a submatrix.
 * It slices previous matrix in certain points.
 * @param m1 
 * Pointer to the matrix that is going to be used as base.
 * @param row1 
 * Row coordinate of the start point of slicing.
 * @param column1 
 * Column coordinate of the start point of slicing.
 * @param row2 
 * Row coordinate of the end point of slicing.
 * @param column2 
 * Column coordinate of the end point of slicing.
 * @return Matrix* 
 * Pointer to matrix that contains the result of the slicing.
 * @note O(m * n). "m" being the row size of the sliced matrix and "n" being the column size of the sliced matrix.
 * The complexity is defined by the two loops.
 * The other operations of the function have O(1) complexity.
 */
Matrix* matrix_slice(Matrix* m1, int row1, int column1, int row2, int column2);

/**
 * @brief Transposes a Matrix
 * @param m1 
 * Pointer to the not transposed matrix.
 * @return Matrix* 
 * Pointer to the transposed matrix.
 * @note Complexity O(m * n), where "m" is the column size of the matrix and "n" is the row size of the matrix.
 * The complexity in this function is defined by the two loops in it.
 * The other operations of the function have O(1) complexity.
 */
Matrix* matrix_transpose(Matrix* m1);

/**
 * @brief Makes the convolution of a matrix by a kernel.
 * @param m1 
 * Pointer to matrix 
 * @param mk 
 * Pointer to the kernel matrix.
 * @return Matrix* 
 * Pointer to the matrix that contains the result of the operation.
 * @note Complexity O(n * m * o * p). Being "n" the row size on the matrix, "m" the amount of nodes per row of the matrix,
 * "o" the row size of the kernel and "p" the amount of nodes per row of the kernel.
 * The complexity of this function depend on the four loops, which run all the rows of the matrix and the kernel and each allocated node in those rows.
 */
Matrix* matrix_convolve(Matrix* m1, Matrix* mk);

/**
 * @brief It slices the matrix that is undergoing the convolution operation. 
 * @param m 
 * Pointer to the matrix that is being convoluted.
 * @param mk
 * Pointer to the kernel matrix.
 * @param n 
 * Pointer to the node that is the middle target of the kernel.
 * @return Matrix* 
 * Pointer to the submatrix created.
 * @note Complexity O(1). The fucntion does't have any loops or iterations.
 * All the values and operations are static which makes the complexity of the function O(1).
 */
Matrix* prepares_submatrix(Matrix* m, Matrix* mk, Node* n);

#endif