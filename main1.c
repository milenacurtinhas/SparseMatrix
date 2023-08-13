#include "matrix.h"

int main (){
    Matrix* m1 = matrix_construct(5, 5);

    matrix_set(m1, 0, 0, 4);
    matrix_set(m1, 2, 3, 8);
    matrix_set(m1, 3, 1, 1);
    matrix_set(m1, 3, 4, 3);
    matrix_set(m1, 4, 3, 6);
    matrix_set(m1, 4, 4, 9);
    matrix_set(m1, 3, 1, 2);

    FILE* file1;
    file1 = fopen("matrix1.bin", "wb");
    save_binary_matrix(m1, file1);
    fclose(file1);

    Matrix* m2 = matrix_construct(5, 5);

    matrix_set(m2, 0, 0, 5);
    matrix_set(m2, 1, 1, 8);
    matrix_set(m2, 2, 3, 9);
    matrix_set(m2, 3, 0, 12);
    matrix_set(m2, 3, 3, 7);
    matrix_set(m2, 4, 2, 3);
    matrix_set(m2, 4, 4, 1);

    FILE* file2;
    file2 = fopen("matrix2.bin", "wb");
    save_binary_matrix(m2, file2);
    fclose(file2);

    Matrix* m3 = matrix_construct(3, 3);

    matrix_set(m3, 0, 0, 1);
    matrix_set(m3, 0, 2, 2);
    matrix_set(m3, 1, 1, 5);
    matrix_set(m3, 2, 0, 2);
    matrix_set(m3, 2, 2, 1);
 
    FILE* file3;
    file3 = fopen("matrix3.bin", "wb");
    save_binary_matrix(m3, file3);
    fclose(file3);

    matrix_destroy(m1);
    matrix_destroy(m2);
    matrix_destroy(m3);

    return 0;
}