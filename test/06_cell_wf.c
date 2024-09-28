#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "../include/cell.h"
#include "../include/cell_wf.h"

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

cell_wf_t cell_wf_maker() {

    cell_t cell = cell_maker();
    assert(cell != NULL);

    cell_wf_t cell_wf = cell_wf_new2(cell, (void(*)(void*))print_str, (void(*)(void*))print_int_key,
     (void*(*)(void*))delete_str, (void*(*)(void*))delete_int_key, (int(*)(void*, void*))compare_str, (int(*)(void*, void*))compare_int_key);
    assert(cell_wf != NULL);
    
    return cell_wf;
}

int test_cell_wf_proto() {

    fprintf(stderr, "\n## Test of the cell_wf_proto function\n");

    fprintf(stderr, "<= Test : We try invalids parameters, must return errors\n");

    fprintf(stderr, "=> Test passed with success\n");

    fprintf(stderr, "<= Test : We try valid parameters, must return not errors\n");

    fprintf(stderr, "=> Test passed with success\n");
    return 1;
}


int test_cell_wf_new() {
    
    cell_t cell = cell_maker();
    assert(cell != NULL);

    fprintf(stderr, "\n## Test of the cell_wf_new function\n");

    fprintf(stderr, "<= Test : We try invalids parameters, must return errors\n");
    
    cell_wf_t cell_wf = cell_wf_new2(NULL, (void(*)(void*))print_str, (void(*)(void*))print_int_key,
    (void*(*)(void*))delete_str, (void*(*)(void*))delete_int_key, (int(*)(void*, void*))compare_str, (int(*)(void*, void*))compare_int_key);
    assert(cell_wf == NULL);

    cell_wf = cell_wf_new2(cell, (void(*)(void*))NULL, (void(*)(void*))print_int_key,
    (void*(*)(void*))delete_str, (void*(*)(void*))delete_int_key, (int(*)(void*, void*))compare_str, (int(*)(void*, void*))compare_int_key);
    assert(cell_wf == NULL);
    
    cell_wf = cell_wf_new2(cell, (void(*)(void*))print_str, (void(*)(void*))NULL,
    (void*(*)(void*))delete_str, (void*(*)(void*))delete_int_key, (int(*)(void*, void*))compare_str, (int(*)(void*, void*))compare_int_key);
    assert(cell_wf == NULL);
    
    cell_wf = cell_wf_new2(cell, (void(*)(void*))print_str, (void(*)(void*))print_int_key,
    (void*(*)(void*))NULL, (void*(*)(void*))delete_int_key, (int(*)(void*, void*))compare_str, (int(*)(void*, void*))compare_int_key);
    assert(cell_wf == NULL);
    
    cell_wf = cell_wf_new2(cell, (void(*)(void*))print_str, (void(*)(void*))print_int_key,
    (void*(*)(void*))delete_str, (void*(*)(void*))NULL, (int(*)(void*, void*))compare_str, (int(*)(void*, void*))compare_int_key);
    assert(cell_wf == NULL);
    
    cell_wf = cell_wf_new2(cell, (void(*)(void*))print_str, (void(*)(void*))print_int_key,
    (void*(*)(void*))delete_str, (void*(*)(void*))delete_int_key, (int(*)(void*, void*))NULL, (int(*)(void*, void*))compare_int_key);
    assert(cell_wf == NULL);
    
    cell_wf = cell_wf_new2(cell, (void(*)(void*))print_str, (void(*)(void*))print_int_key,
    (void*(*)(void*))delete_str, (void*(*)(void*))delete_int_key, (int(*)(void*, void*))compare_str, (int(*)(void*, void*))NULL);
    assert(cell_wf == NULL);

    fprintf(stderr, "=> Test passed with success\n");

    fprintf(stderr, "<= Test : We try valid parameters, must return not errors\n");

    cell_wf = cell_wf_new2(cell, (void(*)(void*))print_str, (void(*)(void*))print_int_key,
     (void*(*)(void*))delete_str, (void*(*)(void*))delete_int_key, (int(*)(void*, void*))compare_str, (int(*)(void*, void*))compare_int_key);
    assert(cell_wf != NULL);
    assert(cell_wf->cell);
    assert(cell_wf->cell->key == cell->key);
    assert(cell_wf->cell->data == cell->data);
    assert(cell_wf->cell->hashcode == cell->hashcode);
    assert(cell_wf->print_data == (void(*)(void*))print_str);
    assert(cell_wf->print_key == (void(*)(void*))print_int_key);
    assert(cell_wf->compare_data == (int(*)(void*, void*))compare_str);
    assert(cell_wf->compare_key == (int(*)(void*, void*))compare_int_key);
    assert(cell_wf->delete_data == (void*(*)(void*))delete_str);
    assert(cell_wf->delete_key == (void*(*)(void*))delete_int_key);

    cell_wf = cell_wf_delete(cell_wf);
    assert(cell_wf == NULL);

    fprintf(stderr, "=> Test passed with success\n");
    return 1;
}

int test_cell_wf_print() {
    
    fprintf(stderr, "\n## Test of the cell_wf_print function\n");

    cell_wf_t cell_wf = cell_wf_maker();
    assert(cell_wf != NULL);

    fprintf(stderr, "<= Test : We try invalids parameters, must return errors\n");

    cell_wf_print(NULL);

    fprintf(stderr, "=> Test passed with success\n");

    fprintf(stderr, "<= Test : We try valid parameters, must return not errors\n");

    cell_wf_print(cell_wf);

    cell_wf = cell_wf_delete(cell_wf);
    assert(cell_wf == NULL);


    fprintf(stderr, "=> Test passed with success\n");
    return 1;

}

int test_cell_wf_delete() {

    fprintf(stderr, "\n## Test of the cell_wf_delete function\n");

    cell_wf_t cell_wf = cell_wf_maker();
    assert(cell_wf != NULL);

    fprintf(stderr, "<= Test : We try invalids parameters, must return errors\n");

    cell_wf_t cell_wf_invalid = cell_wf_delete(NULL);
    assert(cell_wf_invalid == NULL);

    fprintf(stderr, "=> Test passed with success\n");

    fprintf(stderr, "<= Test : We try valid parameters, must return not errors\n");

    cell_wf = cell_wf_delete(cell_wf);
    assert(cell_wf == NULL);

    fprintf(stderr, "=> Test passed with success\n");
    return 1;

}

int test_cell_wf_compare() {

    fprintf(stderr, "\n## Test of the cell_wf_compare function\n");

    cell_wf_t cell_wf1 = cell_wf_maker();
    assert(cell_wf1 != NULL);

    cell_wf_t cell_wf2 = cell_wf_maker();
    assert(cell_wf2 != NULL);

    fprintf(stderr, "<= Test : We try invalids parameters, must return errors\n");
    
    int rst = cell_wf_compare((cell_wf_t)NULL, cell_wf2, (int (*)(void*, void*))NULL);
    assert(rst == -1);
    rst = cell_wf_compare(cell_wf1, (cell_wf_t)NULL, (int (*)(void*, void*))NULL);
    assert(rst == -2);

    fprintf(stderr, "=> Test passed with success\n");

    fprintf(stderr, "<= Test : We try valid parameters, must return not errors\n");

    rst = cell_wf_compare(cell_wf1, cell_wf2, (int (*)(void*, void*))NULL);
    assert(rst == 1);

    *(int*)(cell_wf1->cell->key) = 69;

    rst = cell_wf_compare(cell_wf1, cell_wf2, (int (*)(void*, void*))NULL);
    assert(rst == 0);    

    *(int*)(cell_wf1->cell->key) = 1;
    ((char*)(cell_wf1->cell->data))[0] = 'z';

    rst = cell_wf_compare(cell_wf1, cell_wf2, (int (*)(void*, void*))NULL);
    assert(rst == 0); 

    cell_wf1 = cell_wf_delete(cell_wf1);
    assert(cell_wf1 == NULL);
    cell_wf2 = cell_wf_delete(cell_wf2);
    assert(cell_wf2 == NULL);


    fprintf(stderr, "=> Test passed with success\n");
    return 1;
}

int test_cell_wf_compare_key() {

    fprintf(stderr, "\n## Test of the cell_wf_compare_key function\n");

    cell_wf_t cell_wf1 = cell_wf_maker();
    assert(cell_wf1 != NULL);

    cell_wf_t cell_wf2 = cell_wf_maker();
    assert(cell_wf2 != NULL);

    fprintf(stderr, "<= Test : We try invalids parameters, must return errors\n");
    
    int rst = cell_wf_compare_key((cell_wf_t)NULL, cell_wf2, (int (*)(void*, void*))NULL);
    assert(rst == -1);
    rst = cell_wf_compare_key(cell_wf1, (cell_wf_t)NULL, (int (*)(void*, void*))NULL);
    assert(rst == -2);

    fprintf(stderr, "=> Test passed with success\n");

    fprintf(stderr, "<= Test : We try valid parameters, must return not errors\n");

    rst = cell_wf_compare_key(cell_wf1, cell_wf2, (int (*)(void*, void*))NULL);
    assert(rst == 1);

    *(int*)(cell_wf1->cell->key) = 69;

    rst = cell_wf_compare_key(cell_wf1, cell_wf2, (int (*)(void*, void*))NULL);
    assert(rst == 0);    

    cell_wf1 = cell_wf_delete(cell_wf1);
    assert(cell_wf1 == NULL);
    cell_wf2 = cell_wf_delete(cell_wf2);
    assert(cell_wf2 == NULL);

    fprintf(stderr, "=> Test passed with success\n");
    return 1;
}

int main() {

    test_cell_wf_new();
    test_cell_wf_print();
    test_cell_wf_delete();
    test_cell_wf_compare();
    test_cell_wf_compare_key();

    fprintf(stderr, "Tests of file 06_cell_wf.c passed with success\n");
    return EXIT_SUCCESS;
}