#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h> 

#include "../include/tree_patricia.h"

int test_radix_new() {

    fprintf(stderr, "\n## Test of the radix_new function\n");

    radix_t radix;

    fprintf(stderr, "<= Test : We try valid parameters, must return not errors\n");


    radix = radix_new('a', (radix_t)NULL);
    assert(radix != (radix_t)NULL);
    assert(radix->value == 'a');
    assert(radix->brothers == NULL);
    assert(radix->sons == NULL);

    radix = radix_new('b', radix);
    assert(radix != (radix_t)NULL);
    assert(radix->value == 'b');
    assert(radix->brothers != NULL);
    radix_t brother = radix->brothers;
    char value = brother->value;
    assert((int)value == (int)'a');
    assert(radix->sons == NULL);

    radix->sons = radix_new('c', NULL);
    assert(radix != NULL);
    assert(radix->value == 'b');
    assert(radix->brothers != NULL);
    assert(radix->brothers->value == 'a');
    assert(radix->sons != NULL);
    assert(radix->sons->value == 'c');

    radix = radix_delete(radix);
    assert(radix == NULL);
    
    fprintf(stderr, "=> Test passed with success\n");
    return 1;
}

int test_radix_add_word() {

    fprintf(stderr, "\n## Test of the radix_add_word function\n");

    radix_t radix = radix_new('a', NULL);

    fprintf(stderr, "<= Test : We try invalids parameters, must return errors\n");

    int rst = radix_add_word(NULL, "abc");
    assert(rst == -1);

    rst = radix_add_word(radix, NULL);
    assert(rst == -2);

    fprintf(stderr, "=> Test passed with success\n");

    rst = radix_add_word(radix, "ab");
    assert(rst == 1);
    assert(radix != NULL);
    assert(radix->value == 'a');
    assert(radix->brothers == NULL);
    assert(radix->sons != NULL);
    assert(radix->sons->value == 'b');
    assert(radix->sons->brothers == NULL);
    assert(radix->sons->sons != NULL);
    assert(radix->sons->sons->value == '\0');
    assert(radix->sons->sons->brothers == NULL);
    assert(radix->sons->sons->sons == NULL);

    rst = radix_add_word(radix, "cdef");
    assert(rst == 1);
    rst = radix_add_word(radix, "a");
    assert(rst == 1);

    rst = radix_add_word(radix, "\0");
    assert(rst == 1);

    rst = radix_add_word(radix, "cdfe");
    assert(rst == 1);

    radix_print(radix, 0);
    fprintf(stderr, "<= Test : We try valid parameters, must return not errors\n");
    
    radix = radix_delete(radix);
    assert(radix == NULL);
    
    fprintf(stderr, "=> Test passed with success\n");
    return 1;
}

int test_radix_print() {
    fprintf(stderr, "\n## Test of the radix_print function\n");

    radix_t radix = radix_new('a', NULL);
    assert(radix != NULL);

    int rst = radix_add_word(radix, "cdef");
    assert(rst == 1);
    rst = radix_add_word(radix, "a");
    assert(rst == 1);

    rst = radix_add_word(radix, "\0");
    assert(rst == 1);

    rst = radix_add_word(radix, "cdfe");
    assert(rst == 1);

    fprintf(stderr, "<= Test : We try invalids parameters, must return errors\n");

    radix_print((radix_t)NULL, 0);

    fprintf(stderr, "=> Test passed with success\n");

    fprintf(stderr, "<= Test : We try valid parameters, must return not errors\n");

    radix_print(radix, 0);
    
    radix = radix_delete(radix);
    assert(radix == NULL);
    
    fprintf(stderr, "=> Test passed with success\n");
    return 1;
}

int test_radix_delete() {

    fprintf(stderr, "\n## Test of the  function\n");

    fprintf(stderr, "<= Test : We try valid parameters, must return not errors\n");

    radix_t radix = radix_new('a', NULL);
    assert(radix != NULL);

    int rst = radix_add_word(radix, "cdef");
    assert(rst == 1);
    rst = radix_add_word(radix, "a");
    assert(rst == 1);

    rst = radix_add_word(radix, "\0");
    assert(rst == 1);

    rst = radix_add_word(radix, "cdfe");
    assert(rst == 1);

    radix = radix_delete(radix);
    assert(radix == NULL);

    fprintf(stderr, "=> Test passed with success\n");
    return 1;
}


int test_radix_find() {

    fprintf(stderr, "\n## Test of the radix_print function\n");

    radix_t radix = radix_new('\0', NULL);
    assert(radix != NULL);

    int rst = radix_add_word(radix, "cdfe");
    assert(rst == 1);
    rst = radix_add_word(radix, "a");
    assert(rst == 1);

    rst = radix_add_word(radix, "\0");
    assert(rst == 1);

    rst = radix_add_word(radix, "cdef");
    assert(rst == 1);

    radix_print(radix, 0);

    fprintf(stderr, "<= Test : We try invalids parameters, must return errors\n");

    rst = radix_find(NULL, "a");
    assert(rst == -1);
    rst = radix_find(radix, NULL);
    assert(rst == -2);

    fprintf(stderr, "=> Test passed with success\n");

    fprintf(stderr, "<= Test : We try valid parameters, must return not errors\n");

    rst = radix_find(radix, "a");
    assert(rst == 1);

    rst = radix_find(radix, "b");
    assert(rst == 0);

    rst = radix_find(radix, "cd");
    assert(rst == 0);

    rst = radix_find(radix, "cde");
    assert(rst == 0);

    rst = radix_find(radix, "cdea");
    assert(rst == 0);
    
    rst = radix_find(radix, "cdef");
    assert(rst == 1);

    radix = radix_delete(radix);
    assert(radix == NULL);

    fprintf(stderr, "=> Test passed with success\n");
    return 1;
}

int main() {
    test_radix_new();
    test_radix_add_word();
    test_radix_print();
    test_radix_delete();
    test_radix_find();

    fprintf(stderr, "Tests of file 09_tree_patricia.c passed with success\n");
    return EXIT_SUCCESS;
}