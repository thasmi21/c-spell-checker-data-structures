#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "../include/generic_table.h"

static void print_double(double* d) {

    printf("%f", *d);
}

static double* delete_double(double* d) {

    assert(d != NULL);
    free(d);
    
    d = NULL;
    return d;
}

static int equal_double(double* d1, double* d2) {

    assert(d1 != NULL && d2 != NULL);

    return (*d1 == *d2);
}

static int test_table_new() {

    fprintf(stderr, "## Test of the table_new function\n");

    fprintf(stderr, "<= Test : We try to create a new table and test its parameters\n");
    

    table_t tab;
    tab = table_new(0, (void (*)(void*))print_double, (void* (*)(void*))delete_double, (int (*)(void*, void*))equal_double);

    assert(tab == NULL);

    tab = table_new(5, (void (*)(void *))NULL, 
                   (void (*))delete_double, 
                   (int (*)(void *, void *))equal_double);
    assert(tab == NULL);

    tab = table_new(4, (void (*)(void *))print_double, 
                   (void (*))NULL, 
                   (int (*)(void *, void *))equal_double);
    assert(tab == NULL);

    tab = table_new(4, (void (*)(void *))print_double, 
                   (void (*))delete_double, 
                   (int (*)(void *, void *))NULL);
    assert(tab == NULL);

    tab = table_new(10, (void (*)(void *))print_double, 
                   (void (*))delete_double, 
                   (int (*)(void *, void *))equal_double);

    assert(tab != NULL && "table_new returned NULL when expected a valid table");
    assert(tab->data != NULL);
    assert(tab->actual_size == 0);
    assert(tab->max_size == 10);
    assert(tab->delete_data != NULL);
    assert(tab->print_data != NULL);
    assert(tab->equal_data != NULL);

    tab = table_delete(tab);
    assert(tab == NULL);

    fprintf(stderr, "=> Test passed with success\n");
    return 1;
}

static int test_table_append() {

    fprintf(stderr, "## Test of the table_append function\n");

    fprintf(stderr, "<= Test : We try to append a new element to a table and test its parameters\n");
    
    table_t tab;
    tab = table_new(2, (void (*)(void *))print_double, 
                   (void (*))delete_double, 
                   (int (*)(void *, void *))equal_double);

    double* p0;
    p0 = malloc(sizeof(double));
    assert(p0 != NULL);
    *p0 = 2.0;

    int rst = table_append(p0, NULL);
    assert(rst == -1);

    rst = table_append(NULL, tab);
    assert(rst == -4);

    rst = table_append(p0, tab);
    assert(rst == 1);

    //printf("tab->actual_size = %d\n", tab->actual_size);
    assert(tab->actual_size == 1);

    double val0 = *(double*)((tab->data)[0]);
    assert(val0 == 2.0);

    double* p1;
    p1 = malloc(sizeof(double));
    assert(p1 != NULL);
    *p1 = 3.0;
    
    rst = table_append(p1, tab);
    assert(rst == 1);
    assert(tab->actual_size == 2);
    assert(*(double*)((tab->data)[1]) == 3.0);
    
    fprintf(stderr, "=> Test passed with success\n");

    fprintf(stderr, "<= Test : We try to append a new element to a table while it is full\n");
    
    double* p2;
    p2 = malloc(sizeof(double));
    *p2 = 4.4;
    
    rst = table_append(p2, tab);
    assert(rst == -3 && "Test of insertion when table is full failed");

    p2 = delete_double(p2);
    assert(p2 == NULL);
    fprintf(stderr, "=> Test passed with success\n");
    
    fprintf(stderr, "<= Test : We try to free it\n");
    tab = table_delete(tab);
    fprintf(stderr, "=> Test passed with success\n");
    return 1;
}

static int test_table_insert_at() {

    fprintf(stderr, "## Test of the table_insert_at function\n");
    
    fprintf(stderr, "<= Test : We try to insert a new element to a table and test its parameters\n");
    
    table_t tab;
    tab = table_new(10, (void (*)(void *))print_double, 
                   (void (*))delete_double, 
                   (int (*)(void *, void *))equal_double);

    double* p0;
    p0 = malloc(sizeof(double));
    *p0 = 2.0;
    int rst = table_append(p0, tab);
    assert(rst == 1);

    double* p1;
    p1 = malloc(sizeof(double));
    *p1 = 3.0;
    rst =table_append(p1, tab);
    assert(rst == 1);


    double* p2;
    p2 = malloc(sizeof(double));
    *p2 = 4.4;
    //printf("tab->actual_size = %zu\n", tab->actual_size);
    rst = table_insert_at(p2, 1, NULL);
    assert(rst == -1);
    rst = table_insert_at(p2, -1, tab);
    assert(rst == -5);
    rst = table_insert_at(p2, 5, tab);
    assert(rst == -5);
    rst = table_insert_at(NULL, 1, tab);
    assert(rst == -7);
    
    rst = table_insert_at(p2, 1, tab);
    assert(rst > 0);
    //printf("tab->actual_size = %zu\n", tab->actual_size);
    assert(tab->actual_size == 3);
    assert(*(double*)((tab->data)[0]) == 2.0);
    assert(*(double*)((tab->data)[1]) == 4.4);
    assert(*(double*)((tab->data)[2]) == 3.0);
    
    tab = table_delete(tab);
    fprintf(stderr, "=> Test passed with success\n");
    return 1;
}

static int test_remove_at() {

    fprintf(stderr, "## Test of the table_remove_at function\n");

    fprintf(stderr, "<= Test : We try to remove elements of a table and test its parameters\n");
    
    table_t tab;
    tab = table_new(10, (void (*)(void *))print_double, 
                   (void (*))delete_double, 
                   (int (*)(void *, void *))equal_double);

    double* p0;
    p0 = malloc(sizeof(double));
    *p0 = 2.0;
    int rst = table_append(p0, tab);
    assert(rst == 1);

    double* p1;
    p1 = malloc(sizeof(double));
    *p1 = 3.0;
    table_append(p1, tab);

    double* p2;
    p2 = malloc(sizeof(double));
    *p2 = 4.4;
    table_append(p2, tab);

    printf("3 elements were appened succesfully, now trying to remove them\n");
    rst = table_remove_at(1, NULL);
    assert(rst == -1);
    rst = table_remove_at(-1, tab);
    assert(rst == -6);
    rst = table_remove_at(5, tab);
    assert(rst == -6);

    rst = table_remove_at(1, tab);
    assert(rst == 1);
    assert(tab->actual_size == 2);
    assert(*(double*)((tab->data)[0]) == 2.0);
    assert(*(double*)((tab->data)[1]) == 4.4);
    assert((tab->data)[2] == NULL);

    table_remove_at(0, tab);
    assert(rst == 1);
    assert(tab->actual_size == 1);
    assert(*(double*)((tab->data)[0]) == 4.4);
    assert((tab->data)[1] == NULL);
    assert((tab->data)[2] == NULL);
    
    table_remove_at(0, tab);
    assert(rst == 1);

    rst = table_remove_at(0, tab);
    assert(rst == -5);
    
    tab = table_delete(tab);
    fprintf(stderr, "=> Test passed with success\n");
    return 1;
}

static int test_table_printf() {

    fprintf(stderr, "## Test of the table_insert_at function\n");

    fprintf(stderr, "<= Test : We try to print elements of a table NULL, should return an error\n");

    table_printf(NULL);

    fprintf(stderr, "=> Test passed with success\n");

    fprintf(stderr, "<= Test : We try to print elements of a table with 3 elements of value 2, 3, 4.4\n");

    table_t tab;
    tab = table_new(10, (void (*)(void *))print_double, 
                   (void (*))delete_double, 
                   (int (*)(void *, void *))equal_double);

    table_printf(tab);

    double* p0;
    p0 = malloc(sizeof(double));
    *p0 = 2.0;
    table_append(p0, tab);

    double* p1;
    p1 = malloc(sizeof(double));
    *p1 = 3.0;
    table_append(p1, tab);

    double* p2;
    p2 = malloc(sizeof(double));
    *p2 = 4.4;
    table_append(p2, tab);

    table_printf(tab);

    tab = table_delete(tab);
    fprintf(stderr, "=> Test passed with success\n");
    return 1;
}

static int test_table_initialize_i() {

    fprintf(stderr, "\n## Test of the table_initialize_i function\n");

    fprintf(stderr, "<= Test : We try valid parameters, must return not errors\n");

    table_t tab;
    tab = table_new(5, (void (*)(void *))print_double, 
                   (void (*))delete_double, 
                   (int (*)(void *, void *))equal_double);


    table_printf(tab);

    double* p3;
    p3 = malloc(sizeof(double));
    *p3 = 78;
    table_append(p3, tab);

    table_initialize_i(tab, 3, p3);

    assert(tab != NULL);
    assert(tab->data != NULL);

    double d =  *(double*)((tab->data)[3]);
    assert(d == 78);
    table_printf(tab);

    tab = table_delete(tab);
    assert(tab == NULL);

    fprintf(stderr, "=> Test passed with success\n");
    return 1;
}

static table_t crea_table() {

    table_t tab;
    tab = table_new(10, (void (*)(void *))print_double, 
                   (void (*))delete_double, 
                   (int (*)(void *, void *))equal_double);
    assert(tab != NULL);

    double* p0;
    p0 = malloc(sizeof(double));
    assert(p0 != NULL);
    *p0 = 2.0;
    int rst = table_append(p0, tab);
    assert(rst == 1);

    double* p1;
    p1 = malloc(sizeof(double));
    assert(p0 != NULL);
    *p1 = 3.0;
    table_append(p1, tab);
    assert(tab != NULL);

    double* p2;
    p2 = malloc(sizeof(double));
    *p2 = 4.4;
    table_append(p2, tab);
    assert(tab != NULL);

    return tab;
}

static int test_table_is_equal() {

    fprintf(stderr, "\n## Test of the table_is_equal function\n");

    table_t tab1 = NULL;
    table_t tab2 = NULL;

    tab1 = crea_table();
    tab2 = crea_table();

    fprintf(stderr, "<= Test : We try invalids parameters, must return errors\n");

    int rst = table_is_equal(NULL, tab2);
    assert(rst == -1);
    rst = table_is_equal(tab1, NULL);
    assert(rst == -2);

    fprintf(stderr, "=> Test passed with success\n");

    fprintf(stderr, "<= Test : We try valid parameters, must return not errors\n");

    rst = table_is_equal(tab1, tab2);
    assert(rst == 1);

    *(double*)((tab1->data)[1]) = 2.1;

    rst = table_is_equal(tab1, tab2);
    assert(rst == 0);

    tab1 = table_delete(tab1);
    assert(tab1 == NULL);

    tab2 = table_delete(tab2);
    assert(tab2 == NULL);

    fprintf(stderr, "=> Test passed with success\n");

    
    return 1;
}

int main() {
    test_table_new();
    test_table_append();
    test_table_insert_at();
    test_remove_at();
    test_table_printf();
    test_table_is_equal();
    test_table_initialize_i();
    
    fprintf(stderr, "Tests of file 01_generic_table.c passed with success\n");
    return EXIT_SUCCESS;
}   