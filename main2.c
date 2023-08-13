#include "aux.h"

int main (){
    FILE* file1;
    file1 = fopen("matrix1.bin", "rb");
    Matrix* m1 = read_binary_matrix(file1);
    fclose(file1);

    FILE* file2;
    file2 = fopen("matrix2.bin", "rb");
    Matrix* m2 = read_binary_matrix(file2);
    fclose(file2);

    FILE* file3;
    file3 = fopen("matrix3.bin", "rb");
    Matrix* mk = read_binary_matrix(file3);
    fclose(file3);

    while(1){
        switch(show_menu()){
            case 1:
                Matrix* m3 = add_matrices(m1, m2);
                options_of_display(m3);
                matrix_destroy(m3);
                break;
            case 2:
                Matrix* m4 = matrix_scalar_mult(m1, 2.0);
                options_of_display(m4);
                matrix_destroy(m4);
                break;
            case 3:
                Matrix* m5 = matrix_matrix_mult(m1, m2);
                options_of_display(m5);
                matrix_destroy(m5);
                break;
            case 4:
                Matrix* m6 = matrix_point_by_point_mult(m1, m2);
                options_of_display(m6);
                matrix_destroy(m6);
                break;
            case 5:
                Matrix* m7 = matrix_swap_rows(m1, 2, 3);
                options_of_display(m7);
                matrix_destroy(m7);
                break;
            case 6:
                Matrix* m8 = matrix_swap_columns(m2, 2, 3);
                options_of_display(m8);
                matrix_destroy(m8);
                break;
            case 7:
                Matrix* m9 = matrix_slice(m2, 2, 3, 4, 4);
                options_of_display(m9);
                matrix_destroy(m9);
                break;
            case 8:
                Matrix* m10 = matrix_transpose(m2);
                options_of_display(m10);
                matrix_destroy(m10);
                break;
            case 9:
                Matrix* m11 = matrix_convolve(m1, mk);
                options_of_display(m11);
                matrix_destroy(m11);
                break;
            case 10:
                quit_program(m1, m2, mk);
                return 0;
        }
    }
}