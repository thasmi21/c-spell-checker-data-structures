#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h> 

#include "cell.h"
#include "hash_table.h"
#include "tree_trie.h"
#include "vector.h"
#include "trie_compress.h"
#include "key.h"

#define ENTERING() fprintf(stderr, "\n## Enterring in %s function\n", __func__);
#define VALID()    fprintf(stderr, "<= Test : We try valid parameters, must return not errors\n");
#define INVALID()  fprintf(stderr, "<= Test : We try invalids parameters, must return errors\n");
#define SUCCESS()  fprintf(stderr, "=> Test passed with success\n");
#define EXIT()     fprintf(stderr, "Tests of file %s passed with success\n", __FILE__); return EXIT_SUCCESS;

int test_() {

    ENTERING();

    INVALID();

    SUCCESS();

    VALID();

    SUCCESS();
    return 1;
}

int test_add_v_key_chars_trie() {

    ENTERING();

    vect_t v_key = v_key_new();

    trie_t trie = trie_new();
    assert(trie != NULL);

    int rst = trie_add_word(trie, "abcd");
    assert(rst == 1);   

    rst = trie_add_word(trie, "abde");
    assert(rst == 1);

    rst = trie_add_word(trie, "bbcd");
    assert(rst == 1);

    //trie_print2(trie);

    rst = add_v_key_chars_trie(NULL, v_key);
    assert(rst == -1);

    rst = add_v_key_chars_trie(trie, NULL);
    assert(rst == -2);

    INVALID();

    SUCCESS();

    rst = add_v_key_chars_trie(trie, v_key);
        vect_printf(v_key);

    printf("\nrst = %d\n", rst);
    assert(rst == 1);
    assert(v_key != NULL);
    assert(v_key->data != NULL);
    char** v_data = (char**)v_key->data;
    assert(*(v_data[0]) == 'V');
    assert(*(v_data[1]) == 'a');
    assert(*(v_data[2]) == 'S');
    assert(*(v_data[3]) == 'V');
    assert(*(v_data[4]) == 'b');
    assert(*(v_data[5]) == 'S');
    assert(*(v_data[6]) == 'V');
    assert(*(v_data[7]) == 'c');
    assert(*(v_data[8]) == 'S');
    assert(*(v_data[9]) == 'V');
    assert(*(v_data[10]) == 'd');
    assert(*(v_data[11]) == 'S');
    assert(*(v_data[12]) == 'V');
    assert(*(v_data[13]) == '0');
    assert(*(v_data[14]) == 'S');
    assert(*(v_data[15]) == 'E');
    assert(*(v_data[16]) == 'E');
    assert(*(v_data[17]) == 'E');

    vect_printf(v_key);
    VALID();

    trie = trie_delete(trie);
    assert(trie == NULL);

    v_key = vect_delete(v_key);
    assert(v_key == NULL);

    SUCCESS();
    return 1;
}

int test_trie_compress() {

    ENTERING();

    trie_t trie = trie_new();
    assert(trie != NULL);

    int rst = trie_add_word(trie, "abcd");
    assert(rst == 1);

    rst = trie_add_word(trie, "abde");
    assert(rst == 1);

    rst = trie_add_word(trie, "bbcd");
    assert(rst == 1);

    hash_t h_tab = hash_tree_new(20, (void (*)(void *))trie_print2);
    assert(h_tab != NULL);

    INVALID();

    trie_t compressed_trie = trie_compress(NULL, h_tab);
    assert(compressed_trie == NULL);

    compressed_trie = trie_compress(trie, NULL);
    assert(compressed_trie == trie);

    SUCCESS();

    VALID();

    compressed_trie = trie_compress(trie, h_tab);
    assert(compressed_trie == trie);

    trie_print2(compressed_trie);

    compressed_trie = trie_compressed_delete(compressed_trie);
    assert(compressed_trie == NULL);

    h_tab = hash_delete(h_tab);
    assert(h_tab == NULL);

    SUCCESS();
    return 1;
}
int test_trie_compressor() {

    ENTERING();

    trie_t trie = trie_new();
    assert(trie != NULL);

    int rst = trie_add_word(trie, "abcd");
    assert(rst == 1);

    rst = trie_add_word(trie, "abde");
    assert(rst == 1);

    rst = trie_add_word(trie, "bbcd");
    assert(rst == 1);

    INVALID();

    trie_t compressed_trie = trie_compressor(NULL);
    assert(compressed_trie == NULL);

    SUCCESS();

    compressed_trie = trie_compressor(trie);
    assert(compressed_trie != NULL);

    trie_print_test2(compressed_trie);

    VALID();

    compressed_trie = trie_compressed_delete(compressed_trie);
    assert(compressed_trie == NULL);

    SUCCESS();
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

    trie_t trie = trie_new();
    assert(trie != NULL);

    for (int i = 0; i<10000; i++) {
        char* data = malloc(21* sizeof(char));
        generate_random_string(data, 10, 20);
        int rst = trie_add_word(trie, data);
        assert(rst == 1);
        free(data);
    }

    trie_t compressed_trie = trie_compressor(trie);
    assert(compressed_trie != NULL);

    compressed_trie = trie_compressed_delete(compressed_trie);
    assert(compressed_trie == NULL);

    fprintf(stderr, "=> Test passed with success\n");
    return 1;
}

int main() {

    test_add_v_key_chars_trie();
    test_trie_compress();
    test_trie_compressor();
    test_random();
    EXIT();
}