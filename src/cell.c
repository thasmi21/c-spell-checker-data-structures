#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "../include/cell.h"

cell_t cell_new(void* key, void* data, size_t hashcode) {

    if (key == NULL) {
        return NULL;
    }

    if (data == NULL) {
        return NULL;
    }

    cell_t cell;
    cell = malloc(sizeof(*cell));

    if (cell == NULL) {
        printf("Error in cell.c/cell_new: malloc cell failed\n");
        return NULL;
    }

    cell->key = key;

    cell->data = data;
    cell->hashcode = hashcode;

    return cell;
}

void cell_print(cell_t cell, void (*print_data)(void*), void (*print_key)(void*)) {

    if (cell == NULL) {
        printf("Error in cell.c/cell_print: cell is NULL\n");
        return;
    }

    if (print_data == NULL) {
        printf("Error in cell.c/cell_print: print_data is NULL\n");
        return;
    }

    if (print_key == NULL) {
        printf("Error in cell.c/cell_print: print_key is NULL\n");
        return;
    }
    
    printf("Cell {key = ");
    print_key(cell->key);
    printf(", data = ");
    print_data(cell->data);
    printf(", hashcode = %zu }\n", cell->hashcode);
    return;
}

void cell_print_for_wf(cell_t cell, void (*print_data)(void*), void (*print_key)(void*)) {

    if (cell == NULL) {
        printf("Error in cell.c/cell_print: cell is NULL\n");
    }

    else if (print_data == NULL) {
        printf("Error in cell.c/cell_print: print_data is NULL\n");
    }

    else if (print_key == NULL) {
        printf("Error in cell.c/cell_print: print_key is NULL\n");
    }

    else {
        printf("Cell {key = ");
        print_key(cell->key);
        printf(", data =");

        print_data(cell->data);

        printf(", hashcode = %zu }", cell->hashcode);
    }
}

cell_t cell_delete(cell_t cell, void* (*delete_data)(void*), void*(*delete_key)(void*)) {

    if (cell == NULL) {
        return NULL;
    }

    if (delete_data == NULL) {
        printf("Error in cell.c/cell_print: delete_data is NULL\n");
        return cell;
    }


    if (delete_key == NULL) {
        printf("Error in cell.c/cell_print: delete_key is NULL\n");
        return cell;
    }

    assert(cell->data != NULL);

    if (delete_data != (void*(*)(void*))0x1) {
        cell->data = delete_data(cell->data);
        assert(cell->data == NULL);
    }

    cell->key = delete_key(cell->key);
    assert(cell->key == NULL);

    free(cell); 
    return NULL;
}

int cell_compare(cell_t cell1, cell_t cell2, int(*compare_data)(void*, void*), int (*compare_key)(void*, void*)) {

    if (cell1 == NULL) {
        printf("Error in cell.c/compare_cell: cell1 is NULL\n");
        return -1;
    }

    if (cell2 == NULL) {
        printf("Error in cell.c/compare_cell: cell2 is NULL\n");
        return -2;
    }

    if (compare_data == NULL) {
        printf("Error in cell.c/compare_cell: compare_data is NULL\n");
        return -3;
    }

    if (compare_key == NULL) {
        printf("Error in cell.c/compare_cell: compare_key is NULL\n");
        return -4;
    }


    int rst1 = compare_data(cell1->data, cell2->data);
    if (rst1 < 0) {
        printf("Error in cell.c/compare_cell: rst1 < 0\n");
        return -5;
    }

    int rst2 = compare_key(cell1->key, cell2->key);
    if (rst1 < 0) {
        printf("Error in cell.c/compare_cell: rst2 < 0\n");
        return -6;
    }

    if (rst1 == 1 && rst2 == 1) {
        return 1;
    }
    return 0;
}

int cell_compare_key(cell_t cell1, cell_t cell2, int (*compare_key)(void*, void*)) {

    if (cell1 == NULL) {
        printf("Error in cell.c/compare_cell_key: cell1 is NULL\n");
        return -1;
    }

    if (cell2 == NULL) {
        printf("Error in cell.c/compare_cell_key: cell2 is NULL\n");
        return -2;
    }

    if (compare_key == NULL) {
        printf("Error in cell.c/compare_cell: compare_key is NULL\n");
        return -3;
    }

    int rst = compare_key(cell1->key, cell2->key);

    if (rst < 0) {
        printf("Error in cell.c/compare_cell: rst1 < 0\n");
        return -4;
    }

    if (rst == 1) {
        return 1;
    }
    return 0;
}