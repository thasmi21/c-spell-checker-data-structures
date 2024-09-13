
#include <stdio.h>


typedef struct {

    void** data;
    size_t max_size;
    size_t actual_size;

    void (*print_data)(void*, FILE*);
    void* (*delete_data)(void*);
    int (*equal_data)(void*, void*);
} *table_t;

//n doit etre >0 partout

table_t table_new(int n, void (*print_data)(void*, FILE*), void* (*delete_data)(void*), int (*equal_data)(void*, void*));

table_t table_delete(table_t tab);

void table_printf(table_t tab);

int table_append(void* val, table_t tab);

//Cette fonction ne peux que inserer un element dans le tableau existant
int table_insert_at(void* val, int index, table_t tab);

//This function can only remove in the existing tab
int table_remove_at(int index, table_t tab);