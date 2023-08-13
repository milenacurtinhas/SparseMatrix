#include "aux.h"

int show_menu(){
    printf("01) SOMAR DUAS MATRIZES\n");
    printf("02) MULTIPLICAR UMA MATRIZ POR UM ESCALAR\n");
    printf("03) MULTIPLICAR DUAS MATRIZES\n");
    printf("04) MULTIPLICAR DUAS MATRIZES PONTO A PONTO\n");
    printf("05) TROCAR DUAS LINHAS\n");
    printf("06) TROCAR DUAS COLUNAS\n");
    printf("07) SLICE\n");
    printf("08) TRANSPOR UMA MATRIZ\n");
    printf("09) REALIZAR CONVOLUÇÃO DE UMA MATRIZ POR UM KERNEL\n");
    printf("10) SAIR DO PROGRAMA\n\n");

    printf("► Digite a opção desejada: ");

    int input;
    scanf("%d", &input);
    clear_terminal();

    return input;
}

void options_of_display(Matrix* m){
    switch(show_display_menu()){
        case 1:
            print_sparse_matrix(m);
            break;
        case 2:
            print_dense_matrix(m);
            break;
        case 3:
            print_sparse_matrix(m);
            print_dense_matrix(m);
            break;
        case 4:
            break;
    }
}

int show_display_menu(){
    printf("01) IMPRIMIR MATRIZ ESPARSA\n");
    printf("02) IMPRIMIR MATRIZ DENSA\n");
    printf("03) IMPRIMIR MATRIZ ESPARSA E DENSA\n");
    printf("04) NÃO IMPRIMIR MATRIZ\n");

    printf("► Digite a opção desejada: ");

    int input;
    scanf("%d", &input);
    clear_terminal();

    return input;
}

void clear_terminal(){
    while (system("clear") == 0) {
        break;
    }
}

void quit_program(Matrix* m1, Matrix* m2, Matrix* m3){
    matrix_destroy(m1);    
    matrix_destroy(m2);
    matrix_destroy(m3);
}