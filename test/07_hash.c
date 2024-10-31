#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "hash_table.h"

#include <string.h>

#include "list.h"
#include "cell.h"
#include "cell_wf.h"

void print_str(char* s) {
    printf("str = %s", s);
}

void print_key(char* key) {
    printf("key = %d", *key);
}

void cell_print_wrapper(cell_t cell) {
    cell_print(cell, (void(*)(void*))print_str, (void(*)(void*))print_key);
}


char* delete_str(char* str) {

    if (str == NULL) {
        return NULL;
    }

    free(str);
    str = NULL;
    return str;
}

char* delete_key(char* key) {

    if (key == NULL) {
        return NULL;
    }
    free(key);
 
    key = NULL;
    return key;
}

int compare_str(char* s1, char* s2) {
    
    if (s1 == NULL) {
        printf("Error in 05_cell.c/compare_str: s1 == NULL");
        return -1;
    }

    if (s2 == NULL) {
        printf("Error in 05_cell.c/compare_str: s2 == NULL");
        return -2;
    }

    int rst = strcmp(s1, s2);
    return (rst == 0);
}

int compare_key(char* key1, char* key2) {

    if (key1 == NULL) {
        printf("Error in 05_cell.c/compare_key: key1 == NULL");
        return -1;
    }

    if (key2 == NULL) {
        printf("Error in 05_cell.c/compare_key: key2 == NULL");
        return -2;
    }

    int rst = strcmp(key1, key2);
    return (rst == 0);
}

static size_t hash_string(char* str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;  // hash * 33 + c
    }

    return hash;
}

int test_hash_new() {
    
    hash_t hash;
    fprintf(stderr, "\n## Test of the hash_new function\n");

    fprintf(stderr, "<= Test : We try invalids parameters, must return errors\n");

    hash = hash_new(0, (size_t(*)(void*))hash_string, (void* (*)(void*))delete_key, (void*(*)(void*))delete_str,
    (int(*)(void*, void*))compare_key, (int (*)(void* , void* ))compare_str, (void (*)(void*))print_key, (void (*)(void*))print_str);
    assert(hash == NULL);
    
    hash = hash_new(10, (size_t(*)(void*))NULL, (void* (*)(void*))delete_key, (void*(*)(void*))delete_str,
    (int(*)(void*, void*))compare_key, (int (*)(void*, void* ))compare_str, (void (*)(void*))print_key, (void (*)(void*))print_str);
    assert(hash == NULL);
    
    hash = hash_new(10, (size_t(*)(void*))hash_string, (void* (*)(void*))NULL, (void*(*)(void*))delete_str,
    (int(*)(void*, void*))compare_key, (int (*)(void*, void* ))compare_str, (void (*)(void*))print_key, (void (*)(void*))print_str);
    assert(hash == NULL);
    hash = hash_new(10, (size_t(*)(void*))hash_string, (void* (*)(void*))delete_key, (void*(*)(void*))NULL,
    (int(*)(void*, void*))compare_key, (int (*)(void*, void* ))compare_str, (void (*)(void*))print_key, (void (*)(void*))print_str);
    assert(hash == NULL);
    
    hash = hash_new(10, (size_t(*)(void*))hash_string, (void* (*)(void*))delete_key, (void*(*)(void*))delete_str,
    (int(*)(void*, void*))NULL, (int (*)(void* , void* ))compare_str, (void (*)(void*))print_key, (void (*)(void*))print_str);
    assert(hash == NULL);
    
    hash = hash_new(10, (size_t(*)(void*))hash_string, (void* (*)(void*))delete_key, (void*(*)(void*))delete_str,
    (int(*)(void*, void*))compare_key, (int (*)(void*, void* ))NULL, (void (*)(void*))print_key, (void (*)(void*))print_str);
    assert(hash == NULL);

    hash = hash_new(10, (size_t(*)(void*))hash_string, (void* (*)(void*))delete_key, (void*(*)(void*))delete_str,
    (int(*)(void*, void*))compare_key, (int (*)(void*, void*))compare_str, (void (*)(void*))NULL, (void (*)(void*))print_str);
    assert(hash == NULL);

    hash = hash_new(10, (size_t(*)(void*))hash_string, (void* (*)(void*))delete_key, (void*(*)(void*))delete_str,
    (int(*)(void*, void*))compare_key, (int (*)(void*, void*))compare_str, (void (*)(void*))print_key, (void (*)(void*))NULL);
    assert(hash == NULL);
    
    fprintf(stderr, "=> Test passed with success\n");

    fprintf(stderr, "<= Test : We try valid parameters, must return not errors\n");

    hash = hash_new(10, (size_t(*)(void*))hash_string, (void* (*)(void*))delete_key, (void*(*)(void*))delete_str,
    (int(*)(void*, void*))compare_key, (int (*)(void* , void*))compare_str, (void (*)(void*))print_key, (void (*)(void*))print_str);
    assert(hash != NULL);

    assert(hash->size == 10);
    assert(hash->hachage == (size_t(*)(void*))hash_string);
    assert(hash->delete_key == (void* (*)(void*))delete_key);
    assert(hash->delete_data == (void* (*)(void*))delete_str);
    assert(hash->compare_key == (int (*)(void*, void* ))compare_key);
    assert(hash->compare_data == (int (*)(void*, void* ))compare_str);
    assert(hash->print_data == (void (*)(void*))print_str);
    assert(hash->print_key == (void (*)(void*))print_key);
    assert(hash->data != NULL);
    
    hash = hash_delete(hash);
    assert(hash == NULL);
    fprintf(stderr, "=> Test passed with success\n");
    return 1;
}

hash_t hash_new_wrapper() {
    
    hash_t hash = hash_new(10, (size_t(*)(void*))hash_string, (void* (*)(void*))delete_key, (void*(*)(void*))delete_str,
    (int(*)(void*, void*))compare_key, (int (*)(void* , void*))compare_str, (void (*)(void*))print_key, (void (*)(void*))print_str);
    assert(hash != NULL);

    return hash;
}

char* crea_data(char* str, size_t size) {

    char* str_new = malloc(sizeof(char) * (size + 1));
    assert(str_new != NULL);

    strncpy(str_new, str, size);

    str_new[size] = '\0';

    return str_new;
}

int test_hash_put() {

    fprintf(stderr, "\n## Test of the hash_put function\n");

    hash_t tab = hash_new_wrapper();
    char* data = crea_data("abcde", 5);

    char* key = crea_data("abcde", 5);

    fprintf(stderr, "<= Test : We try invalids parameters, must return errors\n");
    
    int rst = hash_put((void*)NULL, (void*)data, (hash_t)tab);
    assert(rst == -2);
    
    rst = hash_put((void*)key, (void*)NULL, (hash_t)tab);
    assert(rst == -3);

    rst = hash_put((void*)key, (void*)data, (hash_t)NULL);
    assert(rst == -1);


    fprintf(stderr, "=> Test passed with success\n");

    fprintf(stderr, "<= Test : We try valid parameters, must return not errors\n");
    
    rst = hash_put(key, data, tab);
    assert(rst == 1);

    size_t hashcode = hash_string(key);
    hashcode = hashcode%(tab->size);

    printf("hashcode = %zu\n", hashcode);
    vect_t p_vec = tab->data;
    assert(p_vec != NULL);
    void** p_vec_data = p_vec->data;
    assert(p_vec_data != NULL);

    list_t p_list = p_vec_data[hashcode];
    assert(p_list != NULL);

    link_t p_link = p_list->data;
    assert(p_link != NULL);

    cell_wf_t p_cell_wf = p_link->data;
    assert(p_cell_wf != NULL);

    cell_t p_cell = p_cell_wf->cell;
    assert(p_cell != NULL);

    char* cell_data = p_cell->data;
    assert(cell_data != NULL);

    char* cell_key = p_cell->key;
    assert(cell_key != NULL);

    int rst1 = compare_key(cell_key, key);
    int rst2 = compare_key(cell_data, data);

    assert(rst1 == 1 && rst2 == 1);

    tab = hash_delete(tab);
    assert(tab == NULL);

    fprintf(stderr, "=> Test passed with success\n");
    return 1;
}

int test_hash_get_value() {

    fprintf(stderr, "\n## Test of the hash_get_value function\n");

    hash_t table = hash_new_wrapper();
    
    char* data = crea_data("abcde", 5);
    char* key = crea_data("abcde", 5);
    int rst = hash_put(key, data, table);
    assert(rst == 1);

    cell_t cell;
    fprintf(stderr, "<= Test : We try invalids parameters, must return errors\n");

    cell = hash_get_value((void*)NULL, table);
    assert(cell == NULL);
    cell = hash_get_value((void*)key, NULL);
    assert(cell == NULL);

    fprintf(stderr, "=> Test passed with success\n");

    fprintf(stderr, "<= Test : We try valid parameters, must return not errors\n");

    hash_print(table);

    char* key2 = crea_data("abcde", 5);

    cell = hash_get_value((void*)key2, table);
    assert(cell != NULL);
    
    rst = compare_key(key, key2);
    assert(rst == 1);

    key2[2] = 'z';
    cell = hash_get_value((void*)key2, table);
    assert(cell == NULL);

    free(key2);
    key2 = NULL;
    table = hash_delete(table);
    assert(table == NULL);

    fprintf(stderr, "=> Test passed with success\n");
    return 1;
}


int test_hash_remove_key() {

    fprintf(stderr, "\n## Test of the hash_remove_key function\n");

    hash_t table = hash_new_wrapper();
    
    char* key = crea_data("abcde", 5);
    char* data = crea_data("abcde", 5);

    int rst = hash_put(key, data, table);
    assert(rst == 1);

    fprintf(stderr, "<= Test : We try invalids parameters, must return errors\n");

    rst =  hash_remove_key((void*)NULL, table);
    assert(rst == -2);

    rst =  hash_remove_key((void*)key, NULL);
    assert(rst == -1);

    fprintf(stderr, "=> Test passed with success\n");

    fprintf(stderr, "<= Test : We try valid parameters, must return not errors\n");

    char* key2 = crea_data("abcde", 5);
    assert(key2 != NULL);

    rst =  hash_remove_key((void*)key2, table);
    assert(rst == 1);

    key2[3] = 'r';
    rst =  hash_remove_key((void*)key2, table);
    assert(rst == 0);

    free(key2);
    key2 = NULL;
    table = hash_delete(table);
    assert(table == NULL);

    fprintf(stderr, "=> Test passed with success\n");
    return 1;
}

int test_hash_print() {

    fprintf(stderr, "\n## Test of the hash_print function\n");

    hash_t table = hash_new_wrapper();
    
    char* key = crea_data("abcde", 5);
    char* data = crea_data("abcde", 5);

    int rst = hash_put(key, data, table);
    assert(rst == 1);

    fprintf(stderr, "<= Test : We try invalids parameters, must return errors\n");

    hash_print(NULL);

    fprintf(stderr, "=> Test passed with success\n");

    fprintf(stderr, "<= Test : We try valid parameters, must return not errors\n");

    hash_print(table);

    table = hash_delete(table);
    assert(table == NULL);

    fprintf(stderr, "=> Test passed with success\n");
    return 1;
}

int test_hash_delete() {

    fprintf(stderr, "\n## Test of the hash_delete function\n");

    fprintf(stderr, "<= Test : We try invalids parameters, must return errors\n");

    hash_t table = hash_delete((hash_t)NULL);
    assert(table == NULL);

    fprintf(stderr, "=> Test passed with success\n");

    fprintf(stderr, "<= Test : We try valid parameters, must return not errors\n");

    table = hash_new_wrapper();
    
    char* key = crea_data("abcde", 5);
    char* data = crea_data("abcde", 5);

    int rst = hash_put(key, data, table);
    assert(rst == 1);

    table = hash_delete(table);
    assert(table == NULL);

    fprintf(stderr, "=> Test passed with success\n");
    return 1;
}

int test_hash_indice() {

    fprintf(stderr, "\n## Test of the hash_indice function\n");

    fprintf(stderr, "<= Test : We try invalids parameters, must return errors\n");

    hash_t table = hash_new_wrapper();
    
    char* key = crea_data("abcde", 5);
    char* data = crea_data("abcde", 5);

    int rst = hash_put(key, data, table);
    assert(rst == 1);

    size_t i = hash_indice(NULL, table);
    assert(i == table->size);
    
    i = hash_indice(key, NULL);
    assert(i == (size_t)-1);

    fprintf(stderr, "=> Test passed with success\n");

    fprintf(stderr, "<= Test : We try valid parameters, must return not errors\n");

    i = hash_indice(key, table);
    assert(i != table->size);
    
    size_t hash = table->hachage(key);
    hash = hash%(table->size);

    assert(i == hash);

    vect_t v_data = table->data;
    void** p_vect_data = v_data->data;
    assert(p_vect_data != NULL);
    list_t p_l = p_vect_data[i];
    assert(p_l != NULL);
    link_t p_link = p_l->data;
    assert(p_link != NULL);
    cell_wf_t cell_wf = p_link->data;
    assert(cell_wf != NULL);
    cell_t cell = cell_wf->cell;
    assert(cell != NULL);
    assert(cell->data == data);
    assert(cell->key == key);

    table = hash_delete(table);
    assert(table == NULL);

    fprintf(stderr, "=> Test passed with success\n");
    return 1;
}

static void generate_random_string(char *str, size_t min_length, size_t max_length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    size_t charset_size = sizeof(charset) - 1; // Exclude the null terminator

    // Generate a random length between min_length and max_length
    size_t length = min_length + rand() % (max_length - min_length + 1);

    for (size_t i = 0; i < length; i++) {
        int key = rand() % charset_size;
        str[i] = charset[key];
    }
    str[length] = '\0'; // Null-terminate the string
}

static int test_random() {

    fprintf(stderr, "\n## Test of the test_random function\n");

    fprintf(stderr, "<= Test : We try valid parameters, must return not errors\n");

    hash_t table = hash_new_wrapper();

    for (int i = 0; i<1000; i++) {
        char* key = malloc(21* sizeof(char));
        char* data = malloc(21* sizeof(char));
        generate_random_string(key, 10, 20);
        generate_random_string(data, 10, 20);
        int rst = hash_put(key, data, table);
        assert(rst == 1);
    }

    table = hash_delete(table);
    assert(table == NULL);

    fprintf(stderr, "=> Test passed with success\n");
    return 1;
}

int test_() {

    fprintf(stderr, "\n## Test of the  function\n");

    fprintf(stderr, "<= Test : We try invalids parameters, must return errors\n");

    fprintf(stderr, "=> Test passed with success\n");

    fprintf(stderr, "<= Test : We try valid parameters, must return not errors\n");

    fprintf(stderr, "=> Test passed with success\n");
    return 1;
}

int main() {

    test_hash_new();
    test_hash_put();
    test_hash_get_value();
    test_hash_remove_key();
    test_hash_print();
    test_hash_delete();
    test_hash_indice();
    test_random();

    fprintf(stderr, "Tests of file 07_hash.c passed with success\n");
    return EXIT_SUCCESS;
}