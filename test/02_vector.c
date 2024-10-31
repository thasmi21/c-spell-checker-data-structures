#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"

static void print_char(char* c) {

    printf("%c", *c);
}

static char* delete_char(char* c) {

    assert(c != NULL);
    free(c);
    
    c = NULL;
    return c;
}

static int equal_char(char* c1, char* c2) {

    assert(c1 != NULL && c2 != NULL);

    return (*c1 == *c2);
}

//Test if ascci value are same parity
static int equal_char2(char* c1, char* c2) {

    assert(c1 != NULL && c2 != NULL);

    int i1 = (*c1 - 0x61)%2;
    int i2 = (*c2 - 0x61)%2;
    return (i1 == i2);
}

static int test_vect_new() {

    fprintf(stderr, "\n## Test of the vect_new function\n");

    fprintf(stderr, "<= Test : We try to create a new vect and test its parameters\n");
    

    vect_t vec;
    vec = vect_new(0, (void (*)(void *))print_char, 
                   (void (*))delete_char, 
                   (int (*)(void *, void *))equal_char);
    
    assert(vec == NULL);

    vec = vect_new(5, (void (*)(void *))NULL, 
                   (void (*))delete_char, 
                   (int (*)(void *, void *))equal_char);
    assert(vec == NULL);

    vec = vect_new(4, (void (*)(void *))print_char, 
                   (void (*))NULL, 
                   (int (*)(void *, void *))equal_char);
    assert(vec == NULL);

    vec = vect_new(4, (void (*)(void *))print_char, 
                   (void (*))delete_char, 
                   (int (*)(void *, void *))NULL);
    assert(vec == NULL);

    vec = vect_new(10, (void (*)(void *))print_char, 
                   (void (*))delete_char, 
                   (int (*)(void *, void *))equal_char);

    assert(vec != NULL && "vect_new returned NULL when expected a valid vect");
    assert(vec->data != NULL);
    assert(vec->actual_size == 0);
    assert(vec->max_size == 10);
    assert(vec->delete_data != NULL);
    assert(vec->print_data != NULL);
    assert(vec->equal_data != NULL);

    vec = vect_delete(vec);
    assert(vec == NULL);

    fprintf(stderr, "=> Test passed with success\n");
    return 1;
}

static int test_vect_append() {

    fprintf(stderr, "\n## Test of the vect_append function\n");

    fprintf(stderr, "<= Test : We try to append a new element to a vect and test its parameters\n");
    
    vect_t vec;
    vec = vect_new(2, (void (*)(void *))print_char, 
                   (void (*))delete_char, 
                   (int (*)(void *, void *))equal_char);

    char* p0;
    p0 = malloc(sizeof(char));
    assert(p0 != NULL);
    *p0 = 'a';
    int rst = vect_append(p0, vec);
    assert(rst == 1);

    //printf("vec->actual_size = %d\n", vec->actual_size);
    assert(vec->actual_size == 1);

    char val0 = *(char*)((vec->data)[0]);
    assert(val0 == 'a');

    char* p1;
    p1 = malloc(sizeof(char));
    assert(p1 != NULL);
    *p1 = 'b';
    rst = vect_append(p1, vec);
    assert(rst == 1);

    char* p2;
    p2 = malloc(sizeof(char));
    assert(p2 != NULL);
    *p2 = 'c';
    rst = vect_append(p2, vec);
    assert(rst == 1);

    assert(vec->max_size == 4);    
    assert(vec->actual_size == 3);
    assert(*(char*)((vec->data)[2]) == 'c');
    
    fprintf(stderr, "=> Test passed with success\n");

    fprintf(stderr, "<= Test : We try to delete a vect\n");

    vec = vect_delete(vec);
    assert(vec == NULL);

    fprintf(stderr, "=> Test passed with success\n");

    return 1;
}

static int test_vect_printf() {

    fprintf(stderr, "\n## Test of the vect_printf function\n");

    fprintf(stderr, "<= Test : We try to append printf a vect\n");

    vect_t vec;
    vec = vect_new(2, (void (*)(void *))print_char, 
                   (void (*))delete_char, 
                   (int (*)(void *, void *))equal_char);

    char* p0;
    p0 = malloc(sizeof(char));
    assert(p0 != NULL);
    *p0 = 'a';
    int rst = vect_append(p0, vec);
    assert(rst == 1);

    char* p1;
    p1 = malloc(sizeof(char));
    assert(p1 != NULL);
    *p1 = 'b';
    rst = vect_append(p1, vec);
    assert(rst == 1);

    vect_printf(vec);

    vec = vect_delete(vec);
    assert(vec == NULL);
    
    fprintf(stderr, "=> Test passed with success\n");

    return 1;
}

static int test_vect_find() {

    fprintf(stderr, "\n## Test of the vect_find function\n");

    fprintf(stderr, "<= Test : We try to append find some char in the vect\n");

    vect_t vec;
    vec = vect_new(2, (void (*)(void *))print_char, 
                   (void (*))delete_char, 
                   (int (*)(void *, void *))equal_char);

    char* p0 = malloc(sizeof(char));
    assert(p0 != NULL);
    *p0 = 'a';
    int rst = vect_append(p0, vec);
    assert(rst == 1);

    char* p1 = malloc(sizeof(char));
    assert(p1 != NULL);
    *p1 = 'b';
    rst = vect_append(p1, vec);
    assert(rst == 1);

    char* p2 = malloc(sizeof(char));
    assert(p2 != NULL);
    *p2 = 'c';
    rst = vect_append(p2, vec);
    assert(rst == 1);

    char* p3 = malloc(sizeof(char));
    assert(p3 != NULL);
    *p3 = 'a';

    vect_printf(vec);
    rst = vect_find(p3, vec);
    assert(rst == 0 && "a not found in place 0");

    *p3 = 'c';
    assert(vect_find(p3, vec) == 2 && "c not found in place 2");

    *p3 = 'd';
    assert(vect_find(p3, vec) == -1 && "d is not in in but found in");
    free(p3);

    vec = vect_delete(vec);
    fprintf(stderr, "=> Test passed with success\n");

    return 1;
}

static int test_vect_lookup() {

    fprintf(stderr, "\n## Test of the vect_lookup function\n");

    fprintf(stderr, "<= Test : We try to find char using a different equal to\n");

    vect_t vec;
    vec = vect_new(2, (void (*)(void *))print_char, 
                   (void (*))delete_char, 
                   (int (*)(void *, void *))equal_char);

    char* p0 = malloc(sizeof(char));
    assert(p0 != NULL);
    *p0 = 'a';
    int rst = vect_append(p0, vec);
    assert(rst == 1);

    char* p1 = malloc(sizeof(char));
    assert(p1 != NULL);
    *p1 = 'b';
    rst = vect_append(p1, vec);
    assert(rst == 1);

    char* p2 = malloc(sizeof(char));
    assert(p2 != NULL);
    *p2 = 'c';
    rst = vect_append(p2, vec);
    assert(rst == 1);

    char* p3 = malloc(sizeof(char));
    assert(p3 != NULL);
    *p3 = 'a';

    assert(vect_lookup(p3, vec, (int (*)(void *, void *))equal_char2) == 0 && "a must be equal to a");

    *p3 = 'c';
    assert(vect_lookup(p3, vec, (int (*)(void *, void *))equal_char2) == 0 && "c must be equal to a");

    *p3 = 'd';
    assert(vect_lookup(p3, vec, (int (*)(void *, void *))equal_char2) == 1 && "d must be equal to b");

    free(p3);
    vec = vect_delete(vec);

    fprintf(stderr, "=> Test passed with success\n");
    return 1;
}

static int test_remove_at() {

    fprintf(stderr, "\n## Test of the vect_remove_at function\n");

    fprintf(stderr, "<= Test : We try to remove elements of a vect and test its parameters\n");
    
    vect_t vec;
    vec = vect_new(10, (void (*)(void *))print_char, 
                   (void (*))delete_char, 
                   (int (*)(void *, void *))equal_char);

    char* p0 = malloc(sizeof(char));
    assert(p0 != NULL);
    *p0 = 'a';
    int rst = vect_append(p0, vec);
    assert(rst == 1);

    char* p1 = malloc(sizeof(char));
    assert(p1 != NULL);
    *p1 = 'b';
    rst = vect_append(p1, vec);
    assert(rst == 1);

    char* p2 = malloc(sizeof(char));
    assert(p2 != NULL);
    *p2 = 'c';
    rst = vect_append(p2, vec);
    assert(rst == 1);

    fprintf(stderr, "<= Test : We try to remove elements of a vect with invalid parameters, should return errors\n");


    rst = vect_remove_at(1, NULL);
    assert(rst == -1);
    rst = vect_remove_at(-1, vec);
    assert(rst == -6);
    rst = vect_remove_at(5, vec);
    assert(rst == -6);
    
    fprintf(stderr, "=> Test passed with success\n");

    fprintf(stderr, "<= Test : We try to remove elements of a vect with valid parameters\n");

    rst = vect_remove_at(1, vec);
    assert(rst == 1);
    assert(vec->actual_size == 2);
    assert(vec->max_size == 5);
    assert(*(char*)((vec->data)[0]) == 'a');
    assert(*(char*)((vec->data)[1]) == 'c');
    assert((vec->data)[2] == NULL);

    vect_remove_at(0, vec);
    assert(rst == 1);
    assert(vec->max_size == 5);
    assert(vec->actual_size == 1);
    assert(*(char*)((vec->data)[0]) == 'c');
    assert((vec->data)[1] == NULL);
    assert((vec->data)[2] == NULL);
    
    vect_remove_at(0, vec);
    assert(rst == 1);
    assert(vec->max_size == 2);
    rst = vect_remove_at(0, vec);
    assert(rst == -5);
    
    vec = vect_delete(vec);
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

static void print_str(char* s) {
    printf("str = %s", s);
}


static char* delete_str(char* str) {

    if (str == NULL) {
        return NULL;
    }

    free(str);
    str = NULL;
    return str;
}

static int compare_str(char* s1, char* s2) {
    
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

static int test_random() {

    fprintf(stderr, "\n## Test of the test_random function\n");

    fprintf(stderr, "<= Test : We try valid parameters, must return not errors\n");

    vect_t vec = vect_new(10, (void (*)(void *))print_str, 
                   (void (*))delete_str, 
                   (int (*)(void *, void *))compare_str);


    for (int i = 0; i<100; i++) {
        char* data = malloc(21* sizeof(char));
        generate_random_string(data, 10, 20);
        int rst = vect_append(data, vec);
        assert(rst == 1);

    }

    vec = vect_delete(vec);
    assert(vec == NULL);

    fprintf(stderr, "=> Test passed with success\n");
    return 1;
}

int main() {
    test_vect_new();
    test_vect_append();
    test_vect_printf();
    test_vect_find();
    test_vect_lookup();
    test_remove_at();
    test_random();

    fprintf(stderr, "Tests of file 02_vector.c passed with success\n");
    return EXIT_SUCCESS;
}