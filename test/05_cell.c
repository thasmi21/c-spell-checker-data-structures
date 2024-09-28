#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "../include/cell.h"

void print_str(char* s) {
    printf("str = %s", s);
}

void print_int_key(int* key) {
    printf("key = %d", *key);
}

void cell_print_wrapper(cell_t cell) {
    cell_print(cell, (void(*)(void*))print_str, (void(*)(void*))print_int_key);
}


char* delete_str(char* str) {

    if (str == NULL) {
        return NULL;
    }

    free(str);
    str = NULL;
    return str;
}

int* delete_int_key(int* key) {

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

int compare_int_key(int* key1, int* key2) {

    if (key1 == NULL) {
        printf("Error in 05_cell.c/compare_int_key: key1 == NULL");
        return -1;
    }

    if (key2 == NULL) {
        printf("Error in 05_cell.c/compare_int_key: key2 == NULL");
        return -2;
    }

    return (*key1 == *key2); 
}

size_t hash_string(char* str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;  // hash * 33 + c
    }

    return hash;
}

cell_t cell_maker() {
    int* p_key = malloc(sizeof(int));
    *p_key = 1;
    char* data = malloc(5 * sizeof(char));
    assert(data != NULL);
    
    data[0] = 'a';
    data[1] = 'b';
    data[2] = 'c';
    data[3] = 'd';
    data[4] = '\0';

    
    size_t hashcode = hash_string(data);

    cell_t cell = cell_new((void*)p_key, (void*)data, hashcode);
    assert(cell != NULL);

    return cell;
}



int test_cell_new() {

    fprintf(stderr, "\n## Test of the cell_new function\n");

    fprintf(stderr, "<= Test : We try invalids parameters, must return errors\n");

    int* p_key = malloc(sizeof(int));
    *p_key = 1;
    char* data = malloc(5*sizeof(char));
    assert(data != NULL);
    data[0] = 'a';
    data[1] = 'b';
    data[2] = 'c';
    data[3] = 'd';
    data[4] = '\0';

    size_t hashcode = hash_string(data);

    cell_t cell = cell_new((void*)NULL, (void*)data, hashcode);
    assert(cell == NULL);

    cell = cell_new((void*)p_key, (void*)NULL, hashcode);
    assert(cell == NULL);

    fprintf(stderr, "=> Test passed with success\n");

    fprintf(stderr, "<= Test : We try valid parameters, must return not errors\n");

    cell = cell_new((void*)p_key, (void*)data, hashcode);
    assert(cell != NULL);

    int cell_key = *(int*)(cell->key);
    assert(cell_key == 1);

    char* cell_data = (char*)(cell->data);
    assert(cell_data[0] == 'a');
    assert(cell_data[1] == 'b');
    assert(cell_data[2] == 'c');
    assert(cell_data[3] == 'd');

    assert(cell->hashcode == hashcode);

    cell = cell_delete(cell, (void*(*)(void*))delete_str, (void*(*)(void*))delete_int_key);
    assert(cell == NULL);

    fprintf(stderr, "=> Test passed with success\n");
    return 1;
}

int test_cell_print() {

    fprintf(stderr, "\n##   Test of the cell_print function\n");

    cell_t cell = cell_maker();
    assert(cell != NULL);

    fprintf(stderr, "<= Test : We try invalids parameters, must return errors\n");

    cell_print(NULL, (void(*)(void*))print_str, (void(*)(void*))print_int_key);
    cell_print(cell, (void(*)(void*))NULL, (void(*)(void*))print_int_key);
    cell_print(cell, (void(*)(void*))print_str, (void(*)(void*))NULL);

    fprintf(stderr, "=> Test passed with success\n");

    fprintf(stderr, "<= Test : We try valid parameters, must return not errors\n");

    cell_print(cell, (void(*)(void*))print_str, (void(*)(void*))print_int_key);

    cell = cell_delete(cell, (void*(*)(void*))delete_str, (void*(*)(void*))delete_int_key);

    fprintf(stderr, "=> Test passed with success\n");
    return 1;
}

int test_cell_delete() {

    fprintf(stderr, "\n## Test of the cell_delete function\n");

    cell_t cell = cell_maker();
    assert(cell != NULL);

    fprintf(stderr, "<= Test : We try invalids parameters, must return errors\n");
    
    cell = cell_delete(cell, (void*(*)(void*))NULL, (void*(*)(void*))delete_int_key);
    cell = cell_delete(cell, (void*(*)(void*))delete_str, (void*(*)(void*))NULL);

    fprintf(stderr, "=> Test passed with success\n");

    fprintf(stderr, "<= Test : We try valid parameters, must return not errors\n");

    cell = cell_delete(cell, (void*(*)(void*))delete_str, (void*(*)(void*))delete_int_key);

    fprintf(stderr, "=> Test passed with success\n");
    return 1;
}

int test_cell_compare() {

    fprintf(stderr, "\n## Test of the cell_compare function\n");

    cell_t cell1 = cell_maker();
    assert(cell1 != NULL);

    cell_t cell2 = cell_maker();
    assert(cell2 != NULL);

    fprintf(stderr, "<= Test : We try invalids parameters, must return errors\n");

    int rst = cell_compare(NULL, cell2, (int(*)(void*, void*))compare_str, (int(*)(void*, void*))compare_int_key);
    assert(rst == -1);

    rst = cell_compare(cell1, NULL, (int(*)(void*, void*))compare_str, (int(*)(void*, void*))compare_int_key);
    assert(rst == -2);    
    
    rst = cell_compare(cell1, cell2, (int(*)(void*, void*))NULL, (int(*)(void*, void*))compare_int_key);
    assert(rst == -3);    
    
    rst = cell_compare(cell1, cell2, (int(*)(void*, void*))compare_str, (int(*)(void*, void*))NULL);
    assert(rst == -4);

    fprintf(stderr, "=> Test passed with success\n");

    fprintf(stderr, "<= Test : We try valid parameters, must return not errors\n");

    rst = cell_compare(cell1, cell2, (int(*)(void*, void*))compare_str, (int(*)(void*, void*))compare_int_key);
    assert(rst == 1);

    *(int*)(cell1->key) = 78;

    rst = cell_compare(cell1, cell2, (int(*)(void*, void*))compare_str, (int(*)(void*, void*))compare_int_key);
    assert(rst == 0);

    *(int*)(cell1->key) = 1;
    ((char*)(cell1->data))[2] = 'z';

    rst = cell_compare(cell1, cell2, (int(*)(void*, void*))compare_str, (int(*)(void*, void*))compare_int_key);
    assert(rst == 0);

    cell1 = cell_delete(cell1, (void*(*)(void*))delete_str, (void*(*)(void*))delete_int_key);
    assert(cell1 == NULL);

    cell2 = cell_delete(cell2, (void*(*)(void*))delete_str, (void*(*)(void*))delete_int_key);
    assert(cell2 == NULL);

    fprintf(stderr, "=> Test passed with success\n");
    return 1;
}

int test_cell_compare_key() {

    fprintf(stderr, "\n## Test of the cell_compare_key function\n");

    cell_t cell1 = cell_maker();
    assert(cell1 != NULL);

    cell_t cell2 = cell_maker();
    assert(cell2 != NULL);

    fprintf(stderr, "<= Test : We try invalids parameters, must return errors\n");

    int rst = cell_compare_key(NULL, cell2, (int(*)(void*, void*))compare_int_key);
    assert(rst == -1);

    rst = cell_compare_key(cell1, NULL, (int(*)(void*, void*))compare_int_key);
    assert(rst == -2);    
    
    rst = cell_compare_key(cell1, cell2, (int(*)(void*, void*))NULL);
    assert(rst == -3);

    fprintf(stderr, "=> Test passed with success\n");

    fprintf(stderr, "<= Test : We try valid parameters, must return not errors\n");

    rst = cell_compare_key(cell1, cell2, (int(*)(void*, void*))compare_int_key);
    assert(rst == 1);

    *(int*)(cell1->key) = 78;

    rst = cell_compare_key(cell1, cell2, (int(*)(void*, void*))compare_int_key);
    assert(rst == 0);

    cell1 = cell_delete(cell1, (void*(*)(void*))delete_str, (void*(*)(void*))delete_int_key);
    assert(cell1 == NULL);

    cell2 = cell_delete(cell2, (void*(*)(void*))delete_str, (void*(*)(void*))delete_int_key);
    assert(cell2 == NULL);

    fprintf(stderr, "=> Test passed with success\n");
    return 1;
}




int main() {

    test_cell_new();
    test_cell_print();
    test_cell_delete();
    test_cell_compare();
    test_cell_compare_key();

    fprintf(stderr, "Tests of file 05_cell.c passed with success\n");
    return EXIT_SUCCESS;
}

//#define ERROR_MSG(msg) printf("Error in %s: %s\n", __func__, msg)
