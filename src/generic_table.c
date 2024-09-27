#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "../include/generic_table.h"

table_t table_new(size_t n, void (*print_data)(void*), void* (*delete_data)(void*), int (*equal_data)(void*, void*)) {

    if (n == 0) {
        printf("Error in generic_table.c/table_new: n must be > 0\n");
        return NULL;
    }

    if (print_data == NULL) {
        printf("Error in generic_table.c/table_new: print_data must not be NULL\n");
        return NULL;
    }

    if (delete_data == NULL) {
        printf("Error in generic_table.c/table_new: delete_data must not be NULL\n");
        return NULL;
    }

    if (equal_data == NULL) {
        printf("Error in generic_table.c/table_new: equal_data must not be NULL\n");
        return NULL;
    }

    table_t tab = calloc(1, sizeof(*tab));

    if (tab == NULL) {
        printf("Error in generic_table.c/table_new: tab is NULL malloc failed\n");
        return NULL;
    }
    
    tab->data = calloc(n, sizeof(*(tab->data)));

    if (tab->data == NULL) {
        printf("Error in generic_table.c/table_new: tab->data is NULL malloc failed\n");
        free(tab);
        return NULL;
    }
    
    tab->max_size = n;
    tab->actual_size = 0;
    tab->print_data = print_data;
    tab->delete_data = delete_data;
    tab->equal_data = equal_data;

    return tab;
}

int table_append(void* val, table_t tab) {

    if (tab == NULL) {
        printf("Error in generic_table.c/table_append: tab is NULL\n");
        return -1;
    }

    void** p_data = tab->data;
    
    if (tab->data == NULL) {
        printf("Error in generic_table.c/table_append: tab->data is NULL malloc failed\n");
        free(tab);
        return -2;
    }

    if (tab->actual_size == tab->max_size) {
        printf("Error in generic_table.c/table_append: tab->actual_size == tab->max_size, table is full\n");
        return -3;
    }

    if (val == NULL) {
        printf("Error in generic_table.c/table_append: val is NULL\n");
        return -4;
    }
    
    if (tab->actual_size > tab->max_size) {
        printf("Error in generic_table.c/table_append: tab->actual_size > tab->max_size, wrong usage of the struct\n");
        return -5;
    }

    if (tab->actual_size < 0 || tab->max_size <= 0) {
        printf("Error in generic_table.c/table_append: tab->actual_size < 0 || tab->max_size <= 0, wrong usage of the struct\n");
        return -3;
    }

    size_t new_index = tab->actual_size;
    p_data[new_index] = val;
    (tab->actual_size)++;
    return 1;
}

int table_insert_at(void* val, size_t index, table_t tab) {

    if (tab == NULL) {
        printf("Error in generic_table.c/table_insert_at: tab is NULL\n");
        return -1;
    }

    void** p_data = tab->data;
    if (p_data == NULL) {
        printf("Error in generic_table.c/table_insert_at: tab->data is NULL\n");
        return -2;
    }

    if (index < 0) {
        printf("Error in generic_table.c/table_insert_at: index < 0\n");
        return -3;
    }

    size_t actual_size = tab->actual_size;

    if (actual_size < 0) {
        printf("Error in generic_table.c/table_insert_at: actual_size < 0\n");
        return -4;
    }

    if (index >= actual_size) {
        printf("Error in generic_table.c/table_insert_at: index >= actual_size\n");
        return -5;
    }

    if (actual_size == tab->max_size) {
        printf("Error in generic_table.c/table_insert_at: actual_size == tab->max_size\n");
        return -6;
    }
    
    if (val == NULL) {
        printf("Error in generic_table.c/table_insert_at: val is NULL\n");
        return -7;
    }

    if (tab->actual_size > tab->max_size) {
        printf("Error in generic_table.c/table_insert_at: tab->actual_size > tab->max_size, wrong usage of the struct\n");
        return -8;
    }

    for (size_t i = actual_size; i > index; i--) {
        p_data[i] = p_data[i-1];
    }

    p_data[index] = val;

    tab->actual_size++;

    return 1;
}

int table_remove_at(size_t index, table_t tab) {

    if (tab == NULL) {
        printf("Error in generic_table.c/table_remove_at: tab is NULL\n");
        return -1;
    }

    void** p_data = tab->data;
    if (p_data == NULL) {
        printf("Error in generic_table.c/table_remove_at: tab->data is NULL\n");
        return -2;
    }

    if (index < 0) {
        printf("Error in generic_table.c/table_remove_at: index < 0\n");
        return -3;
    }

    size_t actual_size = tab->actual_size;
    if (actual_size < 0) {
        printf("Error in generic_table.c/table_remove_at: actual_size < 0\n");
        return -4;
    }

    if (actual_size == 0) {
        printf("Error in generic_table.c/table_remove_at: actual_size == 0\n");
        return -5;
    }

    if (index >= actual_size) {
        printf("Error in generic_table.c/table_remove_at: index > actual_size\n");
        return -6;
    }
    
    void* p_val_index = p_data[index];
    if (p_val_index == NULL) {
        printf("Error in generic_table.c/table_remove_at: p_val_index == NULL\n");
        return -7;
    }

    if (tab->actual_size > tab->max_size) {
        printf("Error in generic_table.c/table_remove_at: tab->actual_size > tab->max_size, wrong usage of the struct\n");
        return -8;
    }

    p_data[index] = tab->delete_data(p_data[index]);
    
    if (p_data[index] != NULL) {
        printf("Error in generic_table.c/table_remove_at: p_data[index] != NULL delete function should return NULL\n");
        return -9;
    }

    for (size_t i = index; i<actual_size-1; i++) {
        p_data[i] = p_data[i+1];
    }
    p_data[actual_size-1] = NULL;

    tab->actual_size--;
    return 1;   
}

void table_printf(table_t tab) {

    if (tab == NULL) {
        printf("\nNothing to print, tab is NULL\n");

    }
    else if (tab->print_data == NULL) {
        printf("Error in generic_table.c/table_printf: Print_data is NULL, while tab is not MAJOR BUG\n");
    }
    else {
        void** p_data = tab->data;
        assert(p_data != NULL);

        if (p_data == NULL) {
            printf("\nError in generic_table.c/table_printf: Tab is not NULL but tab->data is NULL, MAJOR BUG\n");
        }
        else {
            printf("Table = { ");
            printf("Tab->max_size = %zu, tab->actual_size = %zu \t", tab->max_size, tab->actual_size);
            printf("\nTab->data = [");
            size_t actual_size = tab->actual_size;
            for (size_t i = 0; i<actual_size; i++) {
                printf("Tab[%zu] = ", i);
                tab->print_data(p_data[i]);
                printf("\t");     
            }
            printf("] ");
            printf("}\n");


        }
    }
}

table_t table_delete(table_t tab) {

    assert(tab != NULL);
    void** p_data = tab->data;
    assert(p_data != NULL);

    size_t actual_size = tab->actual_size;
    assert(actual_size <= tab->max_size);

    if (tab->delete_data == NULL) {
        printf("Error in generic_table.c/table_delete: Print_data is NULL, while tab is not MAJOR BUG\n");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i<actual_size; i++) {
        if (p_data[i] != NULL) {
            for (size_t j = i+1; j<actual_size; j++) {
                if (p_data[i] == p_data[j]) {
                    p_data[j] = NULL;
                }
            }
            assert(p_data[i] != NULL);
            assert(tab != NULL);
            assert(tab->data != NULL);
            p_data[i] = tab->delete_data(p_data[i]);
        }
        assert(p_data[i] == NULL);
    }
    free(tab->data);
    free(tab);
    return NULL;
}

int table_initialize_i(table_t tab, size_t index, void* val) {

    if (tab == NULL) {
        printf("Error in generic_table.c/table_initialize_i: tab = NULL\n");
        return -1;
    }

    if (val == NULL) {
        printf("Error in generic_table.c/table_initialize_i: val = NULL\n");
        return -2;
    }

    if (tab->max_size <= index) {
        printf("Error in generic_table.c/table_initialize_i: tab->max_size <= index\n");
        return -3;
    }

    if (tab->data == NULL) {
        printf("Error in generic_table.c/table_initialize_i: tab = NULL\n");
        return -4;
    }

    if ((tab->data)[index] != NULL) {
        printf("Error in generic_table.c/table_initialize_i: (tab->data)[index] != NULL, initialisize must only be used on non-initialised val\n");
        return -5;
    }

    (tab->data)[index] = val;
    return 1; 
}