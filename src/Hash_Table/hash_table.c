#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#include "hash_table.h"
#include "vector.h"
#include "list.h"
#include "cell_wf.h"
#include "cell.h"

#define ERR(msg) fprintf(stderr, "Error in hash_table.c : %s\n", msg)

int compare_wrapper(cell_wf_t c1, cell_wf_t c2) {
    return cell_wf_compare_key(c1, c2, (void*)0x1);
}

hash_t hash_new(size_t n, size_t (*hachage)(void * ),
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

    table->data = vect_new(n, (void(*)(void *))list_printf, (void *(*)(void *))list_delete, (int(*)(void*, void*))list_is_equal);
    if (table->data == NULL) {
        printf("Error in hash_table.c/hash_new: malloc vec =  table->data failed\n");
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
        p_data[i] = list_new((void (*)(void *))cell_wf_print, (void *(*)(void *))cell_wf_delete, (int (*)(void *, void *)) compare_wrapper);
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

cell_wf_t cell_wf_wrapper(void* key, void* data, hash_t table) {

    if (table == NULL) {
        printf("Error in hash_table.c/cell_wf_wrapper: table is NULL\n");
    }

    size_t hashcode = table->hachage(key);
    
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
    
    size_t hashcode = table->hachage(key);
    size_t indice = hashcode%(table->size);

    cell_wf_t p_cell_wf = cell_wf_wrapper(key, data, table);
    assert(p_cell_wf != NULL);

    if (p_cell_wf == NULL) {
        printf("Error in hash_table.c/hash_put: cell__wf_new() failed\n");
        return -5;
    }

    vect_t p_vec = table->data;

    if (p_vec == NULL) {
        printf("Error in hash_table.c/hash_put: table->data is NULL\n");
        return -6;
    }

    void** p_data = p_vec->data;

    if (p_data == NULL) {
        printf("Error in hash_table.c/hash_put: void** p_data = vec->data = hash_table->data->data = NULL\n");
        return -7;
    }

    list_t p_list = p_data[indice];

    if (p_list == NULL) {
        printf("Error in hash_table.c/hash_put: p_list == NULL\n");
        return -8;
    }

    p_list = list_add_first(p_list, p_cell_wf);
    if (p_list == NULL) {
        printf("Error in hash_table.c/hash_put: p_list = NULL, list_add_first failed\n");
        return -8;
    }

    (table->total_number)++;
    return 1;
}

cell_t hash_get_value(void* key, hash_t table) {

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

    void** p_vec_data = p_vec->data; 

    if (p_vec_data == NULL) {
        printf("Error in hash_table.c/hash_get_value: p_vec_data = vec->data is NULL\n");
        return NULL;
    }


    list_t p_list = NULL;
    link_t link = NULL;

    size_t hashcode = table->hachage(key);
    size_t indice = hashcode%(table->size);

    p_list = p_vec_data[indice];
    if(p_list == NULL) {
        printf("Error in hash_table.c/hash_get_value: p_list == NULL\n");
        return NULL;
    }

    //I am just checking for key, first so data has no importance that why i use random value (0x1) could not be NULL,
    //Because it is a security is cell_new so compoare data doesnt fail
    //This adress is out of bound on purpose so no pointer could never equal to it


    cell_wf_t p_cell_wf = cell_wf_wrapper(key, (void*)0x1, table);
    
    if (p_cell_wf == NULL) {
        printf("Error in hash_table.c/hash_get_value: p_cell_wf = NULL, cell_wf_wrapper failed\n");
        return NULL;
    }

    link = list_find(p_list, p_cell_wf);

    if (link != NULL) {
        cell_wf_t cell_wf2 = (cell_wf_t)link->data;
        free(p_cell_wf->cell);
        free(p_cell_wf);  
        p_cell_wf = NULL;  
        return cell_wf2->cell;
    }

    free(p_cell_wf->cell);
    free(p_cell_wf);
    p_cell_wf = NULL;
    return NULL;
}

int hash_remove_key(void* key, hash_t table) {

    if (table == NULL) {
        printf("Error in hash_table.c/hash_remove_key: table is NULL\n");
        return -1;
    }

    if (key == NULL) {
        printf("Error in hash_table.c/hash_remove_key: key is NULL\n");
        return -2;
    }

    vect_t p_vec = table->data;
    if (p_vec == NULL) {
        printf("Error in hash_table.c/hash_remove_key: table->data is NULL\n");
        return -3;
    }

    void** p_vec_data = p_vec->data; 

    if (p_vec_data == NULL) {
        printf("Error in hash_table.c/hash_remove_key: p_vec_data = vec->data is NULL\n");
        return -4;
    }

    list_t p_list = NULL;
    link_t link = NULL;

    size_t indice = table->hachage(key)%(table->size);
    p_list = p_vec_data[indice];

    if(p_list == NULL) {
        printf("Error in hash_table.c/hash_remove_key: p_list == NULL\n");
        return -5;
    }

    //I am just checking for key, first so data has no importance that why i use random value (0x1) could not be NULL,
    //Because it is a security is cell_new so compoare data doesnt fail
    //This adress is out of bound on purpose so no pointer could never equal to it
    cell_wf_t p_cell_wf = cell_wf_wrapper(key, (void*)0x1, table);
    
    if (p_cell_wf == NULL) {
        printf("Error in hash_table.c/hash_remove_key: p_cell_wf = NULL, cell_wf_wrapper failed\n");
        free(p_cell_wf->cell);
        free(p_cell_wf);  
        p_cell_wf = NULL;  
        return -6;
    }

    link = list_find(p_list, p_cell_wf);

    if (link == NULL) {
        printf("Error in hash_table.c/hash_remove_key: link = NULL, list_find_failed maybe the key isnt_t in the hash\n");
        free(p_cell_wf->cell);
        free(p_cell_wf);  
        p_cell_wf = NULL;  
        return 0;
    }
    
    p_list = list_link_remove(p_list, link);

    if (p_list == NULL) {
        printf("Error in hash_table.c/hash_remove_key: rst <= 0, list_link_remove failed\n");
        free(p_cell_wf->cell);
        free(p_cell_wf);  
        p_cell_wf = NULL;  
        return -7; 
    }

    free(p_cell_wf->cell);
    free(p_cell_wf);
    p_cell_wf = NULL;
    return 1;
}

void hash_print(hash_t table) {

    if (table == NULL) {
        printf("Error in hash_table.c/hash_print: table is NULL\n");
        return;
    }

    vect_t p_vec = table->data;
    if (p_vec == NULL) {
        printf("Error in hash_table.c/hash_print: table->data is NULL\n");
        return;
    }

    printf("Hash_table = {\n");
    printf("hash_table->size = %zu, hash_table->total_number = %zu, hash_table->data = ", table->size, table->total_number);
    vect_printf(table->data);
    printf("}\n");
}

size_t hash_indice(void* key, hash_t table) {

    if (table == NULL) {
        printf("Error in hash_table.c/hash_indice: table is NULL\n");
        return (size_t)-1;
    }

    size_t size = table->size;
    if (key == NULL) {
        printf("Error in hash_table.c/hash_indice: key is NULL\n");
        return size;
    }

    if (table->hachage == NULL) {
        printf("Error in hash_table.c/hash_indice: table->hachage is NULL\n");
        return size;
    }

    size_t hash = table->hachage(key);
    size_t indice = hash%size;
    return indice;
}

int hash_new_length(int sens, hash_t table) {

    if (sens != 1 && sens != -1) {
        ERR("Sens must be -1 or 1");
        return -1;
    }

    if (table == NULL) {
        ERR("Hash_table is NULL");
        return -2;
    }

    size_t size = table->size;

    if (table->data == NULL) {
        ERR("table->data = NULL");
        return -3;
    }

    vect_t p_vect = table->data;
    list_t* p_data = (list_t*)p_vect->data;

    if (sens == 1) {
        size_t new_size = 2 * size;
        table->data = realloc(table->data, sizeof(*(table->data)) * new_size);
        table->size = new_size;

        if (table->data == NULL) {
            ERR("Realoc failed");
            return -4;
        }

        link_t link = NULL;
        for (size_t i = 0; i < size; i++) {

            if (p_data[i] == NULL) {
                continue;
            }
            
            link = list_first(p_data[i]);
            if (link == NULL) {
                ERR("list_first failed");
                return -5;
            }

            cell_wf_t cell_wf = link->data;
            if (cell_wf == NULL) {
                ERR("cell_wf = NULL");
                return -6;
            }

            cell_t cell = cell_wf->cell;
            if (cell == NULL) {
                ERR("cell = NULL");
                return -7;
            }
            
            char* key = (char*)cell->key;
            if (key == NULL) {
                ERR("key = NULL");
                return -8;
            }

            size_t hash = table->hachage(key);
            size_t indice = hash%new_size;
            p_data[indice] = list_add_first(p_data[indice], cell_wf);
            p_data[i] = list_del_first(p_data[i]);

        }


    }
    return 1;
}

