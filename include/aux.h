#include "matrix.h"

#define ONLINE 1
#define RED_COLOUR printf("\033[1;31m");
#define NORMAL_COLOUR printf("\033[0m");

int show_menu();

void options_of_display(Matrix* m);

int show_display_menu();

void clear_terminal();

void quit_program(Matrix* m1, Matrix* m2, Matrix* m3);