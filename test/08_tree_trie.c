#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h> 

#include "../include/tree_trie.h"

int test_tree_new() {

    fprintf(stderr, "\n## Test of the tree_new() function\n");

    fprintf(stderr, "<= Test : We try valid parameters, must return not errors\n");

    tree_t tree = tree_new();
    assert(tree != NULL);
    
    for (int i = 0; i < ASIZE; i++) {
        tree_t p_son = (tree->sons)[i];
        assert(p_son == NULL);
    }

    tree_print(tree, 0);

    tree = tree_delete(tree);
    assert(tree == NULL);


    fprintf(stderr, "=> Test passed with success\n");
    return 1;
}

int test_tree_add_word() {

    fprintf(stderr, "\n## Test of the tree_add_word function\n");

    tree_t tree = tree_new();
    assert(tree != NULL);

    fprintf(stderr, "<= Test : We try invalids parameters, must return errors\n");

    int rst = tree_add_word(NULL, "abcd");
    assert(rst == -1);

    rst = tree_add_word(tree, NULL);
    assert(rst == -2);

    fprintf(stderr, "=> Test passed with success\n");

    fprintf(stderr, "<= Test : We try valid parameters, must return not errors\n");
    
    rst = tree_add_word(tree, "abcd");
    assert(rst == 1);

    tree_t* p_sons = tree->sons;
    for (int i = 1; i < ASIZE; i++) {
        if (i == 0) {
            assert(p_sons[i] != NULL);
        }
        else {
            assert(p_sons[i] == NULL);
        }
    }

    p_sons = p_sons[0]->sons;
    for (int i = 0; i < ASIZE; i++) {
        if (i == 1) {
            assert(p_sons[i] != NULL);
        }
        else {
            assert(p_sons[i] == NULL);
        }
    }

    p_sons = p_sons[1]->sons;
    for (int i = 0; i < ASIZE; i++) {
        if (i == 2) {
            assert(p_sons[i] != NULL);
        }
        else {
            assert(p_sons[i] == NULL);
        }
    }

    p_sons = p_sons[2]->sons;
    for (int i = 0; i < ASIZE; i++) {
        if (i == 3) {
            assert(p_sons[i] != NULL);
        }
        else {
            assert(p_sons[i] == NULL);
        }
    }

    tree_print(tree, 0);

    rst = tree_add_word(tree, "abcd");
    assert(rst == 1);

    rst = tree_add_word(tree, "abce");
    assert(rst == 1);

    rst = tree_add_word(tree, "bbcd");
    assert(rst == 1);

    rst = tree_add_word(tree, "ab");
    assert(rst == 1);
    tree_print(tree, 0);


    tree = tree_delete(tree);
    assert(tree == NULL);

    fprintf(stderr, "=> Test passed with success\n");
    return 1;
}

int test_tree_find_word() {

    tree_t tree = tree_new();
    assert(tree != NULL);

    int rst = tree_add_word(tree, "abcd");
    assert(rst == 1);

    fprintf(stderr, "\n## Test of the tree_find_tree function\n");

    fprintf(stderr, "<= Test : We try invalids parameters, must return errors\n");

    rst = tree_find_word(NULL, "abc");
    assert(rst == -1);

    rst = tree_find_word(tree, NULL);
    assert(rst == -2);

    fprintf(stderr, "=> Test passed with success\n");

    fprintf(stderr, "<= Test : We try valid parameters, must return not errors\n");

    rst = tree_find_word(tree, "abcd");
    assert(rst == 1 && "abcd must be found");    
    
    rst = tree_find_word(tree, "abc");
        printf("rst = %d\n", rst);

    assert(rst == 0 && "abc must not be found");

    rst = tree_find_word(tree, "abce");
    assert(rst == 0 && "abce must not be found");

    rst = tree_find_word(tree, "abcde");
    assert(rst == 0  && "abcde must not be found");

    tree = tree_delete(tree);
    assert(tree == NULL);

    fprintf(stderr, "=> Test passed with success\n");
    return 1;
}

int test_tree_delete() {

    fprintf(stderr, "\n## Test of the tree_delete function\n");

    fprintf(stderr, "<= Test : We try invalids parameters, must return errors\n");

    tree_t tree = tree_delete(NULL);
    assert(tree == NULL);

    fprintf(stderr, "=> Test passed with success\n");

    fprintf(stderr, "<= Test : We try valid parameters, must return not errors\n");

    tree = tree_new();
    assert(tree != NULL);

    int rst = tree_add_word(tree, "abcd");
    assert(rst == 1);

    tree = tree_delete(tree);
    assert(tree == NULL);

    fprintf(stderr, "=> Test passed with success\n");
    return 1;
}

int test_tree_print() {

    fprintf(stderr, "\n## Test of the tree_print function\n");

    fprintf(stderr, "<= Test : We try invalids parameters, must return errors\n");

    tree_print(NULL, 0);

    fprintf(stderr, "=> Test passed with success\n");

    tree_t tree = tree_new();
    assert(tree != NULL);

    int rst = tree_add_word(tree, "abcd");
    assert(rst == 1);

    tree_print(NULL, 0);

    tree = tree_delete(tree);
    assert(tree == NULL);

    fprintf(stderr, "<= Test : We try valid parameters, must return not errors\n");

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

    test_tree_new();
    test_tree_add_word();
    test_tree_find_word();
    test_tree_delete();
    test_tree_print();

    fprintf(stderr, "Tests of file 08_tree_trie.c passed with success\n");
    return EXIT_SUCCESS;
}