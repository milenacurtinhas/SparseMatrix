#include "matrix.h"

Matrix* matrix_construct(int row, int column){
    Matrix* m = (Matrix*)calloc(1, sizeof(Matrix));

    m->column_size = column;
    m->row_size = row;

    m->column_head = (struct Node**)calloc(column, sizeof(struct Node*));
    m->row_head = (struct Node**)calloc(row, sizeof(struct Node*));

    return m;
}

void matrix_destroy(Matrix* m){
    if (m == NULL){
        return;
    }
    
    for (int i = 0; i < m->row_size; i++){
        Node* n = m->row_head[i];

        while (n != NULL) {
            Node* head = n->row_next;
            node_destroy(n);
            n = head;
        }
    }

    free(m->column_head);
    free(m->row_head);
    free(m);
}

void save_binary_matrix(Matrix* m, FILE* file){
    fwrite(&m->column_size, sizeof(int), 1, file);
    fwrite(&m->row_size, sizeof(int), 1, file);

    Node* aux;
    int i;

    for(i = 0; i < m->row_size; i++){
        aux = m->row_head[i];
        
        while(aux){
            save_binary_nodes(aux, file);
            
            aux = aux->row_next;
        }
    }
}

Matrix* read_binary_matrix(FILE* file){
    if(file == NULL){
        printf("ERROR: Arquivo binário vazio.\n");
        exit(1);
    }

    int row, column;
    data_type value;
    
    fread(&column, sizeof(int), 1, file);
    fread(&row, sizeof(int), 1, file);
    
    Matrix* m = matrix_construct(row, column);
    
    while (fread(&row, sizeof(int), 1, file) && 
           fread(&column, sizeof(int), 1, file) && 
           fread(&value, sizeof(float), 1, file)){
        matrix_set(m, row, column, value);
    }
    
    return m;
}

void print_sparse_matrix(Matrix* m){
    Node* aux;

    for(int i = 0; i < m->row_size; i++) {
        aux = m->row_head[i];

        while(aux){
            printf("(%d, %d): %05.2f\n", aux->row, aux->column, aux->value);

            aux = aux->row_next;
        }
    }
    printf("\n");
}

void print_dense_matrix(Matrix* m){
    Node* aux;
    int column = 0;

    for(int i = 0; i < m->row_size; i++){
        aux = m->row_head[i];
        int prev_column = -1;

        if(aux){
            while(aux){
                column = aux->column;
                if(column > prev_column + 1){
                    while(prev_column + 1 < column){
                        printf("00.00 ");
                        prev_column++;
                    }
                }
                RED_COLOUR;
                printf("%05.2f ", aux->value);
                NORMAL_COLOUR;
                prev_column = aux->column;
                aux = aux->row_next;
            }
            if(column + 1 < m->column_size){
                for(int i = column + 1; i < m->column_size; i++){
                    printf("00.00 ");
                }
            }
        }
        else{
            for(int i = 0; i < m->column_size; i++){
                printf("00.00 ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

void set_null_value(Matrix* m, int row, int column, Node* column_aux, Node* row_aux){
    if(read_value(m, row, column)){
        Node* n = m->column_head[column];

        while(n->row != row){
            n = n->column_next;
        }

        if(m->row_head[row] == n){
            m->row_head[row] = n->row_next;
        }
        else if(row_aux->column < column){
            while(row_aux->column < row){
                row_aux = row_aux->row_next;
            }
            row_aux->row_next = n->row_next;
        }

        if(m->column_head[column] == n){
            m->column_head[column] = n->column_next;
        }
        else if(column_aux->row < row){
            while(column_aux->row < row){
                column_aux = column_aux->column_next;
            }
            column_aux->column_next = n->column_next;
        }

        node_destroy(n);
        n = NULL;
    }
}

void set_value(Matrix* m, int row, int column, Node* column_aux, Node* row_aux, data_type value){
    if (column_aux != NULL){
        while (column_aux->column_next != NULL && column_aux->column <= column){
            column_aux = column_aux->column_next;
        }
    }
    if (row_aux != NULL){
        while (row_aux->row_next != NULL && row_aux->row <= row){
            row_aux = row_aux->row_next;
        }
    }

    Node* n = node_construct(row, column, value, NULL, NULL);

    if (m->column_head[column] == NULL){
        m->column_head[column] = n;
    }
    else if(m->column_head[column]->row > row){
        Node* aux = m->column_head[column];
        n->column_next = aux;
        m->column_head[column] = n;
    }
    else if (column_aux->column_next == NULL){
        column_aux->column_next = n;
    }
    else{
        Node* aux = column_aux->column_next;
        n->column_next = aux;
        column_aux->column_next = n;
    }

    if (m->row_head[row] == NULL){
        m->row_head[row] = n;
    }
    else if(m->row_head[row]->column > column){
        Node* aux = m->row_head[row];
        n->row_next = aux;
        m->row_head[row] = n;
    }
    else if (row_aux->row_next == NULL){
        row_aux->row_next = n;
    }
    else{
        Node* aux = row_aux->row_next;
        n->row_next = aux;
        row_aux->row_next = n;
    }
}

void matrix_set(Matrix* m, int row, int column, data_type value){
    Node* column_aux = m->column_head[column];
    Node* row_aux = m->row_head[row];

    if(!value){
        set_null_value(m, row, column, column_aux, row_aux);
    }
    else{
        if(read_value(m, row, column)){
            change_node_value(column_aux, row, value);
        }
        else{
            set_value(m, row, column, column_aux, row_aux, value);
        }
    }
}

float read_value(Matrix* m, int row, int column){
    if((row > (m->row_size - 1)) || (row < 0) || (column > (m->column_size - 1)) || (column < 0)){
        return 0;
    }
    
    Node* aux = m->column_head[column];
    Node* searched = NULL;

    if(aux){
        while(aux->row <= row){
            if(aux->row == row){
                searched = aux;
            }
            aux = aux->column_next;
            if(!aux){
                break;
            }
        }
    }

    if (!searched){
        return 0;
    } else{
        return searched->value;
    }
}

Matrix* add_matrices(Matrix* m1, Matrix* m2){
    if(m1->column_size != m2->column_size || m1->row_size != m2->row_size){
        printf("Matrizes com tamanhos diferentes.\n");
        exit(1);
    }

    Matrix* m = matrix_construct(m1->row_size, m1->column_size);

    int row_size = m1->row_size, column_size = m1->column_size;
    data_type m1_value, m2_value, add_value;

    for (int i = 0; i < row_size; i++){
        if(m1->row_head[i] != NULL || m2->row_head[i] != NULL){
            
            for (int j = 0; j < column_size; j++){
                if(m1->column_head[i] != NULL || m2->column_head[i] != NULL){
                    m1_value = read_value(m1, i, j);
                    m2_value = read_value(m2, i, j);
                    add_value = m1_value + m2_value;

                    if (add_value != 0){
                        matrix_set(m, i, j, add_value);
                    }
                }
            }
        }
    }

    return m;
}

Matrix* matrix_scalar_mult(Matrix* m1, data_type scalar){
    Matrix* m = matrix_construct(m1->row_size, m1->column_size);

    Node* aux;
    data_type value;

    for(int i = 0; i < m1->row_size; i++) {
        aux = m1->row_head[i];

        while(aux){
            value = aux->value * scalar;
            matrix_set(m, i, aux->column, value);

            aux = aux->row_next;
        }
    }

    return m;
}

Matrix* matrix_matrix_mult(Matrix* m1, Matrix* m2){
    if(m1->column_size != m2->row_size){
        printf("ERROR!\n");
        exit(1);
    }

    Matrix* m = matrix_construct(m1->row_size, m2->column_size);
    data_type m1_value, m2_value, mult_value = 0;

    for(int i = 0; i < m1->row_size; i++){
        if(m1->row_head[i]){

            for (int j = 0; j < m2->column_size; j++){
                if(m2->column_head[j]){
                    mult_value = 0;

                    for (int k = 0; k < m1->column_size; k++){
                        if(m1->column_head[k]){

                            m1_value = read_value(m1, i, k);
                            m2_value = read_value(m2, k, j);
                            mult_value += m1_value * m2_value;
                        }
                    }

                    if(mult_value != 0){
                        matrix_set(m, i, j, mult_value);
                    }
                }
            }
        }
    }

    return m;
}

Matrix* matrix_point_by_point_mult(Matrix* m1, Matrix* m2){
    if(m1->column_size != m2->column_size || m1->row_size != m2->row_size){
        printf("Matrizes com tamanhos diferentes.\n");
        exit(1);
    }

    Matrix* m = matrix_construct(m1->row_size, m1->column_size);

    Node* n1;
    Node* n2;
    data_type value;

    for(int i = 0; i < m1->row_size; i++){
        n1 = m1->row_head[i];
        n2 = m2->row_head[i];

        while(n1 != NULL && n2 != NULL){
            if(n1->column == n2->column){
                value = n1->value * n2->value;
                
                matrix_set(m, n1->row, n1->column, value);
                n1 = n1->row_next;
                n2 = n2->row_next; 
            }
            else if(n1->column > n2->column){
                n2 = n2->row_next;
            }
            else if(n2->column > n1->column){
                n1 = n1->row_next;
            }   
        }
    }

    return m;
}

Matrix* matrix_swap_rows(Matrix* m1, int r1, int r2){
    Matrix* m = matrix_construct(m1->row_size, m1->column_size);
    Node* aux;
    int x;
    data_type value;

    for(int i = 0; i < m1->row_size; i++) {
        aux = m1->row_head[i];

        if(i == r1){
            x = r2;
            while(aux){
                value = aux->value;
                matrix_set(m, x, aux->column, value);

                aux = aux->row_next;
            }
        }
        else if(i == r2){
            x = r1;
            while(aux){
                value = aux->value;
                matrix_set(m, x, aux->column, value);

                aux = aux->row_next;
            }
        }
        else{
            while(aux){
                value = aux->value;
                matrix_set(m, i, aux->column, value);

                aux = aux->row_next;
            }
        }
    }

    return m;
}

Matrix* matrix_swap_columns(Matrix* m1, int c1, int c2){
    Matrix* m = matrix_construct(m1->row_size, m1->column_size);
    Node* aux;
    int x;
    data_type value;

    for(int i = 0; i < m1->column_size; i++) {
        aux = m1->column_head[i];

        if(i == c1){
            x = c2;
            while(aux){
                value = aux->value;
                matrix_set(m, aux->row, x, value);

                aux = aux->column_next;
            }
        }
        else if(i == c2){
            x = c1;
            while(aux){
                value = aux->value;
                matrix_set(m, aux->row, x, value);

                aux = aux->column_next;
            }
        }
        else{
            while(aux){
                value = aux->value;
                matrix_set(m, aux->row, i, value);

                aux = aux->column_next;
            }
        }
    }

    return m;
}

Matrix* matrix_slice(Matrix* m1, int row1, int column1, int row2, int column2){
    int row_size = (row2 - row1) + 1, column_size = (column2 - column1) + 1, x = 0, y = 0;
    float value;

    Matrix* m = matrix_construct(row_size, column_size);

    for(int i = row1; i <= row2; i++){
        y = 0;
        for(int j = column1; j <= column2; j++){
            value = read_value(m1, i, j);

            if(value != 0){
                matrix_set(m, x, y, value);
            }
            y++;   
        }
        x++;
    }

    return m;
}

Matrix* matrix_transpose(Matrix* m1){
    Matrix* m = matrix_construct(m1->column_size, m1->row_size);

    float value;
    for(int i = 0; i < m1->column_size; i++){
        if(m1->column_head[i]){

            for(int j = 0; j < m1->row_size; j++){
                if(m1->row_head[j]){
                    value = read_value(m1, j, i);
                    if(value != 0){
                        matrix_set(m, i, j, value);
                    }
                }
            }
        }
    }

    return m;
}

Matrix* matrix_convolve(Matrix* m1, Matrix* mk){
    if((mk->column_size % 2 == 0) && (mk->row_size % 2 == 0)){
        printf ("ERROR: tamanho de kernel inválido\n");
        exit(1);
    }

    Matrix* m = matrix_construct(m1->column_size, m1->row_size);
    data_type value;

    for(int i = 0; i < m1->row_size; i++){
        Node* aux = m1->row_head[i];

        while(aux){
            Matrix *submatrix = prepares_submatrix(m1, mk, aux);
            Matrix *multiplied_matrix = matrix_point_by_point_mult(submatrix, mk);

            value = 0;

            for(int j = 0; j < multiplied_matrix->row_size; j++){
                Node* head = multiplied_matrix->row_head[j];

                while(head){
                    value += read_value(multiplied_matrix, j, head->column);

                    head = head->row_next;
                }
            }

            matrix_set(m, i, aux->column, value);
            matrix_destroy(submatrix);
            matrix_destroy(multiplied_matrix);
            aux = aux->row_next;
        }
    }

    return m;
}

Matrix* prepares_submatrix(Matrix* m, Matrix* mk, Node* n){
    int middle_row, middle_column, start_r, start_c, end_r, end_c; 
    
    middle_row = mk->row_size/2;
    middle_column = mk->column_size/2;

    start_r = n->row - middle_row;
    start_c = n->column - middle_column;
    end_r = n->row + middle_row;
    end_c = n->column + middle_column;

    Matrix* sliced = matrix_slice(m, start_r, start_c, end_r, end_c);
    
    return sliced;
}