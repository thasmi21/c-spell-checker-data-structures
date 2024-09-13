#include <stdio.h>

#include "../include/generic_tab.h"

table_t table_new(int n, void (*print_data)(void*, FILE*), void* (*delete_data)(void*), int (*equal_data)(void*, void*)) {

    assert(n>0);
    assert(*print_data != NULL);
    assert(*delete_data != NULL);
    assert(*equal_data != NULL);
    
    table_t table = malloc(sizeof(*table));
    assert(table != NULL);

    table->data = malloc(n * sizeof(*(table->data)));
    assert(table->data != NULL);
    
    table->max_size = n;
    table->actual_size = 0;
    table->print_data = print_data;
    table->delete_data = delete_data;
    table->equal_data = equal_data;

    return table;
}

table_t table_delete(table_t tab) {

    assert(tab != NULL);


}

int table_append(void* val, table_t tab) {

    assert(tab != NULL);

    void** p_data = tab->data;
    assert(p_data != NULL);
    assert(tab->actual_size < tab->max_size);

    int new_index = tab->actual_size++;
    p_data[new_index] = val;

    tab->actual_size++;

    return 1;
}

/*
*/
int table_insert_at(void* val, int index, table_t tab) {

    assert(tab != NULL);

    void** p_data = tab->data;
    assert(p_data != NULL);
    assert(index >= 0);
    assert(index <= tab->actual_size);
    assert(tab->actual_size < tab->max_size);
    
    assert(sizeof(*val) == sizeof( *(p_data[index]) ));

    for (int i = tab->actual_size; i>index; i--) {
        p_data[i] = p_data[i-1];
    }

    p_data[index] = val;

    tab->actual_size++;

    return 1;
}

int table_remove_at(int index, table_t tab) {

    assert(tab != NULL);

    void** p_data = tab->data;
    assert(p_data != NULL);
    assert(index >= 0);
    assert(index <= tab->actual_size);
    assert(tab->actual_size > 0);
    
    
    void* p_val_index = p_data[index];
    assert(p_val_index != NULL);

    for (int i = tab->actual_size; i>index; i--) {
        p_data[i-1] = p_data[i];
    }

    p_data[tab->actual_size];
    tab->actual_size--;

    return 1;   
}
