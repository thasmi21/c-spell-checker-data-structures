#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "../include/cell_wf.h"
#include "../include/cell.h"

cell_wf_t cell_wf_new(void* key, void* data, size_t hashcode, void (*print_data)(void*),
    void (*print_key)(void*), void* (*delete_data)(void*),void*(*delete_key)(void*),
    int(*compare_data)(void*, void*), int (*compare_key)(void*, void*)) {

    
    cell_t cell = cell_new(key, data, hashcode);
    
    if (cell == NULL) {
        printf("Error in cell_wf.c/cell_wf_new: cell_new failed\n");
        return NULL;
    }

    if (key == NULL) {
        printf("Error in cell_wf.c/cell_wf_new: key is NULL\n");
        return NULL;
    }

    if (data == NULL) {
        printf("Error in cell_wf.c/cell_wf_new: data is NULL\n");
        return NULL;
    }

    if (print_data == NULL) {
        printf("Error in cell_wf.c/cell_wf_new: print_data is NULL\n");
        return NULL;
    }

    if (print_key == NULL) {
        printf("Error in cell_wf.c/cell_wf_new: print_key is NULL\n");
        return NULL;
    }

    if (delete_data == NULL) {
        printf("Error in cell_wf.c/cell_wf_new: delete_data is NULL\n");
        return NULL;
    }
    
    if (delete_key == NULL) {
        printf("Error in cell_wf.c/cell_wf_new: delete_key is NULL\n");
        return NULL;
    }

    if (compare_data == NULL) {
        printf("Error in cell_wf.c/cell_wf_new: compare_data is NULL\n");
        return NULL;
    }
    
    if (compare_key == NULL) {
        printf("Error in cell_wf.c/cell_wf_new: compare_key is NULL\n");
        return NULL;
    } 

    cell_wf_t cell_wf;
    cell_wf = malloc(sizeof(*cell_wf));

    cell_wf->cell = cell;
    cell_wf->print_data = print_data;
    cell_wf->print_key = print_key;
    cell_wf->delete_data = delete_data;
    cell_wf->delete_key = delete_key;
    cell_wf->compare_data = compare_data;
    cell_wf->compare_key = compare_key;

    return cell_wf;
}

cell_wf_t cell_wf_new2(cell_t cell, void (*print_data)(void*),
    void (*print_key)(void*), void* (*delete_data)(void*),void*(*delete_key)(void*),
    int(*compare_data)(void*, void*), int (*compare_key)(void*, void*)) {

    if (cell == NULL) {
        printf("Error in cell_wf.c/cell_wf_new2: cell == NULL\n");
        return NULL;
    }

    if (print_data == NULL) {
        printf("Error in cell_wf.c/cell_wf_new2: print_data is NULL\n");
        return NULL;
    }

    if (print_key == NULL) {
        printf("Error in cell_wf.c/cell_wf_new2: print_key is NULL\n");
        return NULL;
    }

    if (delete_data == NULL) {
        printf("Error in cell_wf.c/cell_wf_new2: delete_data is NULL\n");
        return NULL;
    }
    
    if (delete_key == NULL) {
        printf("Error in cell_wf.c/cell_wf_new2: delete_key is NULL\n");
        return NULL;
    }

    if (compare_data == NULL) {
        printf("Error in cell_wf.c/cell_wf_new2: compare_data is NULL\n");
        return NULL;
    }
    
    if (compare_key == NULL) {
        printf("Error in cell_wf.c/cell_wf_new2: compare_key is NULL\n");
        return NULL;
    } 

    cell_wf_t cell_wf;
    cell_wf = malloc(sizeof(*cell_wf));

    cell_wf->cell = cell;
    cell_wf->print_data = print_data;
    cell_wf->print_key = print_key;
    cell_wf->delete_data = delete_data;
    cell_wf->delete_key = delete_key;
    cell_wf->compare_data = compare_data;
    cell_wf->compare_key = compare_key;

    return cell_wf;
}


void cell_wf_print(cell_wf_t cell_wf) {

    if (cell_wf == NULL) {
        printf("Error in cell_wf.c/cell_wf_print: cell_wf is NULL\n");
        return;
    }
    printf("Cell_wf (");
    cell_print_for_wf(cell_wf->cell, cell_wf->print_data, cell_wf->print_key);
    printf(")\n");
    return;
}

cell_wf_t cell_wf_delete(cell_wf_t cell_wf) {

    if (cell_wf == NULL) {
        return NULL;
    }

    if (cell_wf->delete_data == NULL) {
        printf("Error in cell_wf.c/cell_wf_delete: delete_data is NULL\n");
        return NULL;
    }
    
    if (cell_wf->delete_key == NULL) {
        printf("Error in cell_wf.c/cell_wf_delete: delete_key is NULL\n");
        return NULL;
    }

    cell_wf->cell = cell_delete(cell_wf->cell, cell_wf->delete_data, cell_wf->delete_key);
    assert(cell_wf->cell == NULL);

    free(cell_wf);
    cell_wf = NULL;
    return NULL;
}

//The 3rd one is only there to have 3 params has other want it
int cell_wf_compare(cell_wf_t cell_wf1, cell_wf_t cell_wf2, int (*unused)(void*, void*)) {

    if (cell_wf1 == NULL) {
        printf("Error in cell_wf.c/cell_wf_compare: cell_wf1 is NULL\n");
        return -1;
    }       
    
    if (cell_wf2 == NULL) {
        printf("Error in cell_wf.c/cell_wf_compare: cell_wf2 is NULL\n");
        return -2;
    }

    int rst = cell_compare(cell_wf1->cell, cell_wf2->cell, cell_wf1->compare_data, cell_wf1->compare_key);

    if (rst < 0) {
        printf("Error in cell_wf.c/cell_wf_compare: cell_compare from cell_wf1 failed\n");
        return -3;
    }

    return rst;
}

int cell_wf_compare_key(cell_wf_t cell_wf1, cell_wf_t cell_wf2, int (*unused)(void*, void*)) {
    
    if (cell_wf1 == NULL) {
        printf("Error in cell_wf.c/cell_wf_compare_key: cell_wf1 is NULL\n");
        return -1;
    }       
    
    if (cell_wf2 == NULL) {
        printf("Error in cell_wf.c/cell_wf_compare_key: cell_wf2 is NULL\n");
        return -2;
    }

    int rst = cell_compare_key(cell_wf1->cell, cell_wf2->cell, cell_wf1->compare_key);

    if (rst < 0) {
        printf("Error in cell_wf.c/cell_wf_compare_key: cell_wf_compare_key from cell_wf1 failed\n");
        return -3;
    }

    return rst;   
}
