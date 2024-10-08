#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h> 

#include "tree_trie.h"

int test_trie_new() {

    fprintf(stderr, "\n## Test of the trie_new() function\n");

    fprintf(stderr, "<= Test : We try valid parameters, must return not errors\n");

    trie_t trie = trie_new();
    assert(trie != NULL);
    
    for (int i = 0; i < ASIZE; i++) {
        trie_t p_son = (trie->sons)[i];
        assert(p_son == NULL);
    }

    trie_print(trie, 0);

    trie = trie_delete(trie);
    assert(trie == NULL);


    fprintf(stderr, "=> Test passed with success\n");
    return 1;
}

int test_trie_add_word() {

    fprintf(stderr, "\n## Test of the trie_add_word function\n");

    trie_t trie = trie_new();
    assert(trie != NULL);

    fprintf(stderr, "<= Test : We try invalids parameters, must return errors\n");

    int rst = trie_add_word(NULL, "abcd");
    assert(rst == -1);

    rst = trie_add_word(trie, NULL);
    assert(rst == -2);

    fprintf(stderr, "=> Test passed with success\n");

    fprintf(stderr, "<= Test : We try valid parameters, must return not errors\n");
    
    rst = trie_add_word(trie, "abcd");
    assert(rst == 1);

    trie_t* p_sons = trie->sons;
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

    trie_print(trie, 0);

    rst = trie_add_word(trie, "abcd");
    assert(rst == 1);

    rst = trie_add_word(trie, "abce");
    assert(rst == 1);

    rst = trie_add_word(trie, "bbcd");
    assert(rst == 1);

    rst = trie_add_word(trie, "ab");
    assert(rst == 1);
    trie_print(trie, 0);


    trie = trie_delete(trie);
    assert(trie == NULL);

    fprintf(stderr, "=> Test passed with success\n");
    return 1;
}

int test_trie_find_word() {

    trie_t trie = trie_new();
    assert(trie != NULL);

    int rst = trie_add_word(trie, "abcd");
    assert(rst == 1);

    fprintf(stderr, "\n## Test of the trie_find_trie function\n");

    fprintf(stderr, "<= Test : We try invalids parameters, must return errors\n");

    rst = trie_find_word(NULL, "abc");
    assert(rst == -1);

    rst = trie_find_word(trie, NULL);
    assert(rst == -2);

    fprintf(stderr, "=> Test passed with success\n");

    fprintf(stderr, "<= Test : We try valid parameters, must return not errors\n");

    rst = trie_find_word(trie, "abcd");
    assert(rst == 1 && "abcd must be found");    
    
    rst = trie_find_word(trie, "abc");
        printf("rst = %d\n", rst);

    assert(rst == 0 && "abc must not be found");

    rst = trie_find_word(trie, "abce");
    assert(rst == 0 && "abce must not be found");

    rst = trie_find_word(trie, "abcde");
    assert(rst == 0  && "abcde must not be found");

    trie = trie_delete(trie);
    assert(trie == NULL);

    fprintf(stderr, "=> Test passed with success\n");
    return 1;
}

int test_trie_delete() {

    fprintf(stderr, "\n## Test of the trie_delete function\n");

    fprintf(stderr, "<= Test : We try invalids parameters, must return errors\n");

    trie_t trie = trie_delete(NULL);
    assert(trie == NULL);

    fprintf(stderr, "=> Test passed with success\n");

    fprintf(stderr, "<= Test : We try valid parameters, must return not errors\n");

    trie = trie_new();
    assert(trie != NULL);

    int rst = trie_add_word(trie, "abcd");
    assert(rst == 1);

    trie = trie_delete(trie);
    assert(trie == NULL);

    fprintf(stderr, "=> Test passed with success\n");
    return 1;
}

int test_trie_print() {

    fprintf(stderr, "\n## Test of the trie_print function\n");

    fprintf(stderr, "<= Test : We try invalids parameters, must return errors\n");

    trie_print(NULL, 0);

    fprintf(stderr, "=> Test passed with success\n");

    trie_t trie = trie_new();
    assert(trie != NULL);

    int rst = trie_add_word(trie, "abcd");
    assert(rst == 1);

    trie_print(NULL, 0);

    trie = trie_delete(trie);
    assert(trie == NULL);

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

    test_trie_new();
    test_trie_add_word();
    test_trie_delete();
    test_trie_print();
    test_trie_find_word();

    fprintf(stderr, "Tests of file 08_tree_trie.c passed with success\n");
    return EXIT_SUCCESS;
}