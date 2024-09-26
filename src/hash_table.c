#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "../include/hash_table.h"
#include "../include/vector.h"
#include "../include/list.h"
#include "../include/cell.h"

hash_t hash_new(size_t n, int (*hachage)(void * ),void* (*delete_key)(void*),void* (*delete_data)(void*),int (*compare_key)(void* e1, void* e2),void (*print_key)(void*),void (*print_data)(void*)) {

    if (n == 0) {
        printf("Error in hash_table.c/hash_new: n must be > 0\n");
        return NULL;
    }

    if (hachage == NULL) {
        printf("Error in hash_table.c/hash_new: fhachage must not be NULL\n");
        return NULL;
    }

    if (delete_key == NULL) {
        printf("Error in hash_table.c/hash_new: delete_key must not be NULL\n");
        return NULL;
    }

    if (delete_data == NULL) {
        printf("Error in hash_table.c/hash_new: delete_data must not be NULL\n");
        return NULL;
    }

    if (compare_key == NULL) {
        printf("Error in hash_table.c/hash_new: compare_key must not be NULL\n");
        return NULL;
    }

    if (print_key == NULL) {
        printf("Error in hash_table.c/hash_new: print_key must not be NULL\n");
        return NULL;
    }

    if (print_data == NULL) {
        printf("Error in hash_table.c/hash_new: print_data must not be NULL\n");
        return NULL;
    }

    hash_t table;
    table = malloc(sizeof(*table));
    
    if (table == NULL) {
        printf("Error in hash_table.c/hash_new: malloc table failed\n");
        return NULL;
    }

    table->total_number = 0;
    table->size = n;

    table->hachage = hachage;

    table->delete_key = delete_key;
    table->delete_data = delete_data;
    table->compare_key = compare_key;
    table->print_key = print_key;
    table->print_data = print_data;


    table->data = vect_new(n, (void(*)(void *))list_printf, (void *(*)(void *))list_delete, NULL);
    
    if (table->data) {
        printf("Error in hash_table.c/hash_new: malloc table->data failed\n");
        return NULL;
    }
    
    for (size_t i = 0; i<n; i++) {
        ((table->data)->data)[i] = list_new((void (*)(void *))cell_print, (void *(*)(void *))cell_delete, (int (*)(void *, void *)) compare_cell);
    }

    return table;
}

hash_t hash_delete(hash_t table) {

    if (table == NULL) {
        return NULL;
    }

    table->data = vect_delete(table->data);
    assert(table->data == NULL);

    free(table);
    table = NULL;
    return table;
}

int hash_put(void* key, void* data, hash_t table) {

    int hashcode = table->hachage(key);
    int indice = hashcode%(table->size);

    cell_t p_cell = cell_new(key, data, hashcode);

    if (p_cell == NULL) {
        printf("Error in hash_table.c/hash_put: cell_new() failed\n");
        return -1;
    }

    vect_t p_vec = table->data;
    list_t* p_data = (list_t*)p_vec->data;
    p_data[indice] = list_add_first(p_data[indice], p_cell);

    if (p_data[indice] == NULL) {
        printf("Error in hash_table.c/hash_put: list_add_first failed\n");
        return -2;
    }

    (table->total_number)++;
    return 1;
}

//void* hash_get_value(void* key, hash_t table) {}