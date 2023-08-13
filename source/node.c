#include "node.h"

Node* node_construct(int row, int column, data_type value, Node* row_next, Node* column_next) {
    Node* n = (Node*)calloc(1, sizeof(Node));
    n->row = row;
    n->column = column;
    n->value = value;
    n->row_next = row_next;
    n->column_next = column_next;
    return n;
}

void node_destroy(Node *n){
    free(n);
}

void save_binary_nodes(Node* n, FILE* file){
    fwrite(&n->row, sizeof(int), 1, file);
    fwrite(&n->column, sizeof(int), 1, file);
    fwrite(&n->value, sizeof(float), 1, file);
}

void change_node_value(Node* n, int row, data_type value){
    while(n->row != row){
        n = n->column_next;
    }
    n->value = value;
}
