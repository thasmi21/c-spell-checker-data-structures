#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "../include/cell.h"

cell_t cell_new(void* key, void* data, size_t hashcode) {

    cell_t p_cell;
    p_cell = malloc(sizeof(*p_cell));

    if (p_cell == NULL) {
        printf("Error in cell.c/cell_new: malloc cell failed\n");
        return NULL;
    }

    p_cell->key = key;
    p_cell->data = data;
    p_cell->hashcode = hashcode;

    return p_cell;
}

void cell_print(cell_t cell, void (*print_data)(void*), void (*print_key)(void*)) {

    if (cell == NULL) {
        printf("Error in hash_table.c/cell_print: cell is NULL\n");
    }

    else if (print_data == NULL) {
        printf("Error in hash_table.c/cell_print: print_data is NULL\n");
    }

    else if (print_key == NULL) {
        printf("Error in hash_table.c/cell_print: print_key is NULL\n");
    }

    else {
        printf("Cell { key = ");
        print_key(cell->key);
        printf(", data = ");
        print_data(cell->data);
        printf(", hashcode = %zu }\n", cell->hashcode);
    }
}

cell_t cell_delete(cell_t cell, void* (*delete_data)(void*), void*(*delete_key)(void*)) {

    if (cell == NULL) {
        return NULL;
    }

    if (delete_data == NULL) {
        printf("Error in hash_table.c/cell_print: delete_data is NULL\n");
        return NULL;
    }


    if (delete_key == NULL) {
        printf("Error in hash_table.c/cell_print: delete_key is NULL\n");
        return NULL;
    }

    else {
        cell->data = delete_data(cell->data);
        assert(cell->data == NULL);
        cell->key = delete_data(cell->key);
        assert(cell->key == NULL);
    }

    return NULL;

}

int compare_cell(cell_t cell1, cell_t cell2, int(*compare_data)(void*, void*), int (*compare_key)(void*, void*)) {

    int rst1 = compare_data(cell1->data, cell2->data);
    int rst2 = compare_key(cell1->key, cell2->key);

    if (rst1 == 1 && rst2 == 1) {
        return 1;
    }
    return 0;
}