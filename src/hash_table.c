#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "../include/hash_table.h"
#include "../include/vector.h"
#include "../include/list.h"
#include "../include/cell_wf.h"
#include "../include/cell.h"

hash_t hash_new(size_t n, int (*hachage)(void * ),
    void* (*delete_key)(void*), void* (*delete_data)(void*),
    int (*compare_key)(void* e1, void* e2), int (*compare_data)(void* e1, void* e2),
    void (*print_key)(void*), void (*print_data)(void*)) {

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

    if (compare_data == NULL) {
        printf("Error in hash_table.c/hash_new: compare_data must not be NULL\n");
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
    table->compare_data = compare_data;
    table->print_key = print_key;
    table->print_data = print_data;

    table->data = vect_new(n, (void(*)(void *))list_printf, (void *(*)(void *))list_delete, NULL);
    
    if (table->data == NULL) {
        printf("Error in hash_table.c/hash_new: malloc table->data failed\n");
        return NULL;
    }

    vect_t p_vec = table->data;
    if (p_vec == NULL) {
        printf("Error in hash_table.c/hash_new: table->data is NULL\n");
        return NULL;
    }

    list_t* p_data = (list_t*)p_vec->data;

    if (p_data == NULL) {
        printf("Error in hash_table.c/hash_new: list_t* p_data = table->data->data = NULL\n");
        return NULL;
    }

    for (size_t i = 0; i<n; i++) { //Do not use this function in list
        p_data[i] = list_new((void (*)(void *))cell_wf_print, (void *(*)(void *))cell_wf_delete, (int (*)(void *, void *)) cell_wf_compare_key);
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

cell_wf_t cell_wf_wrapper(void* key, void* data, size_t hashcode, hash_t table) {

    if (table == NULL) {
        printf("Error in hash_table.c/cell_wrapper: table is NULL\n");
    }

    cell_wf_t cell_wf = cell_wf_new(key, data, hashcode, 
        table->print_data, table->print_key, table->delete_data, table->delete_key,
        table->compare_data, table->compare_key);

    return cell_wf;
}

int hash_put(void* key, void* data, hash_t table) {

    if (table == NULL) {
        printf("Error in hash_table.c/hash_put: table is NULL\n");
        return -1;
    }

    if (key == NULL) {
        printf("Error in hash_table.c/hash_put: key is NULL\n");
        return -2;
    }

    if (data == NULL) {
        printf("Error in hash_table.c/hash_put: data is NULL\n");
        return -3;
    }

    if (table->hachage == NULL) {
        printf("Error in hash_table.c/hash_put: hachage is NULL\n");
        return -4;
    }
    
    int hashcode = table->hachage(key);
    int indice = hashcode%(table->size);

    cell_t p_cell = cell_new(key, data, hashcode);

    if (p_cell == NULL) {
        printf("Error in hash_table.c/hash_put: cell_new() failed\n");
        return -5;
    }

    vect_t p_vec = table->data;

    if (p_vec == NULL) {
        printf("Error in hash_table.c/hash_put: table->data is NULL\n");
        return -6;
    }

    list_t* p_data = (list_t*)p_vec->data;

    if (p_data == NULL) {
        printf("Error in hash_table.c/hash_put: list_t* p_data = table->data->data = NULL\n");
        return -7;
    }

    p_data[indice] = list_add_first(p_data[indice], p_cell);

    if (p_data[indice] == NULL) {
        printf("Error in hash_table.c/hash_put: list_add_first failed\n");
        return -8;
    }

    (table->total_number)++;
    return 1;
}

void* hash_get_value(void* key, hash_t table) {

    if (table == NULL) {
        printf("Error in hash_table.c/hash_get_value: table is NULL\n");
        return NULL;
    }

    if (key == NULL) {
        printf("Error in hash_table.c/hash_get_value: key is NULL\n");
        return NULL;
    }

    vect_t p_vec = table->data;
    if (p_vec == NULL) {
        printf("Error in hash_table.c/hash_get_value: table->data is NULL\n");
        return NULL;
    }

    size_t vec_size = p_vec->max_size;
    list_t* p_list = (list_t*)p_vec->data; 

    link_t link = NULL;
    for (size_t i = 0; i < vec_size; i++) {

        if(p_list[i] == NULL) {
            printf("Error in hash_table.c/hash_get_value: p_list[%zu] == NULL\n", i);
            return NULL;
        }

        list_t list = p_list[i];
        link = list_find(list, key);

        if (link != NULL) {
            cell_wf_t cell_wf = (cell_wf_t)link->data;
            return cell_wf->cell;
        }
    }

    return NULL;
}

void hash_remove_key(void* key, hash_t table) {

    if (table == NULL) {
        printf("Error in hash_table.c/hash_remove_key: table is NULL\n");
    }

    if (key == NULL) {
        printf("Error in hash_table.c/hash_remove_key: key is NULL\n");
        return;
    }

    vect_t p_vec = table->data;
    if (p_vec == NULL) {
        printf("Error in hash_table.c/hash_remove_key: table->data is NULL\n");
        return;
    }

    size_t vec_size = p_vec->max_size;
    list_t* p_list = (list_t*)p_vec->data; 

    link_t link = NULL;
    for (size_t i = 0; i < vec_size; i++) {

        if(p_list[i] == NULL) {
            printf("Error in hash_table.c/hash_remove_key: p_list[%zu] == NULL\n", i);
            return;
        }

        list_t list = p_list[i];
        link = list_find(list, key);

        if (link != NULL) {
            list_link_remove(list, link);
        }
    }

    return;
}

void hash_print(hash_t table) {

    if (table == NULL) {
        printf("Error in hash_table.c/hash_print: table is NULL\n");
    }

    vect_t p_vec = table->data;
    if (p_vec == NULL) {
        printf("Error in hash_table.c/hash_print: table->data is NULL\n");
        return;
    }

    printf("Hash_table = {\n");
    printf("table->size = %zu, table->table_number = %zu\n", table->size, table->total_number);
    vect_printf(table->data);
    printf("}\n");
}