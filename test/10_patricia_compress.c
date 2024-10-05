#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h> 

#include "../include/cell.h"
#include "../include/hash_table.h"
#include "../include/tree_patricia.h"
#include "../include/vector.h"
#include "../include/patricia_compress.h"

#define ENTERING() fprintf(stderr, "\n## Enterring in %s function\n", __func__);
#define VALID()    fprintf(stderr, "<= Test : We try valid parameters, must return not errors\n");
#define INVALID()  fprintf(stderr, "<= Test : We try invalids parameters, must return errors\n");
#define SUCCESS()  fprintf(stderr, "=> Test passed with success\n");
#define EXIT()     fprintf(stderr, "Tests of file %s passed with success\n", __FILE__); return EXIT_SUCCESS;

int test_proto() {

    ENTERING();

    INVALID();

    SUCCESS();

    VALID();

    SUCCESS();
    return 1;
}

static int test_v_key_new() {

    ENTERING();

    VALID();
    
    vect_t v_key = v_key_new();
    assert(v_key != NULL);
    assert(v_key->max_size != 0);
    assert(v_key->actual_size == 0);
    assert(v_key->delete_data != NULL);
    assert(v_key->print_data != NULL);
    assert(v_key->equal_data != NULL);

    v_key = vect_delete(v_key);
    assert(v_key == NULL);
    SUCCESS();
    return 1;
}


static int test_make_add_char() {

    ENTERING();

    vect_t v_key = v_key_new();
    assert(v_key != NULL);

    INVALID();
    
    int rst = make_add_char('a', NULL);
    assert(rst == -2);

    SUCCESS();

    VALID();
    
    rst = make_add_char('a', v_key);
    assert(v_key != NULL);
    assert(v_key->actual_size == 1);
    assert(v_key->data != NULL);
    assert((v_key->data)[0] != NULL);
    assert((v_key->data)[1] == NULL);
    assert(*(char*)((v_key->data)[0]) == 'a');

    v_key = vect_delete(v_key);
    assert(v_key == NULL);
    SUCCESS();
    return 1;
}

static radix_t radix_maker() {

    radix_t radix = radix_new('\0', NULL);
    assert(radix != NULL);

    int rst = radix_add_word(radix, "a");
    assert(rst == 1);

    rst = radix_add_word(radix, "cdfe");
    assert(rst == 1);

    rst = radix_add_word(radix, "cdef");
    assert(rst == 1);

    radix_print(radix, 0);

    return radix;
}

static int test_add_v_key_char() {

    ENTERING();

    radix_t radix = radix_maker();
    assert(radix != NULL);
    vect_t v_key = v_key_new();
    assert(v_key != NULL);

    INVALID();
    
    int rst = add_v_key_char(NULL, v_key);
    assert(rst == -1);
    rst = add_v_key_char(radix, NULL);
    assert(rst == -2);

    SUCCESS();

    VALID();

    rst = add_v_key_char(radix, v_key);
    assert(rst == 1);
    assert(v_key != NULL);
    assert(v_key->data != NULL);
    char** p_data = (char**)v_key->data;
    assert(*(p_data[0]) == 'V');
    assert(*(p_data[1]) == '\0');
    assert(*(p_data[2]) == 'S');
    assert(*(p_data[3]) == 'B');
    assert(*(p_data[4]) == 'V');
    assert(*(p_data[5]) == 'a');
    assert(*(p_data[6]) == 'S');
    assert(*(p_data[7]) == 'V');
    assert(*(p_data[8]) == '\0');
    assert(*(p_data[9]) == 'S');
    assert(*(p_data[10]) == 'B');
    assert(*(p_data[11]) == 'B');
    assert(*(p_data[12]) == 'V');
    assert(*(p_data[13]) == 'c');
    assert(*(p_data[14]) == 'S');
    assert(*(p_data[15]) == 'V');
    assert(*(p_data[16]) == 'd');
    //Could test further but 40 asserts...

    vect_printf(v_key);

    v_key = vect_delete(v_key);
    assert(v_key == NULL);
    radix = radix_delete(radix);
    assert(radix == NULL);
    
    SUCCESS();
    return 1;
}

static int test_make_char_key() {

    ENTERING();

    radix_t radix = radix_maker();
    assert(radix != NULL);
    vect_t v_key = v_key_new();
    assert(v_key != NULL);

    int rst = add_v_key_char(radix, v_key);
    assert(rst == 1);

    INVALID();

    char* str_key =  make_char_key(NULL);
    assert(str_key == NULL);

    SUCCESS();

    VALID();

    str_key =  make_char_key(v_key);
    assert(str_key != NULL);
    assert(str_key[0] == 'V');
    assert(str_key[1] == '0');
    assert(str_key[2] == 'S');
    assert(str_key[3] == 'B');
    assert(str_key[4] == 'V');
    assert(str_key[5] == 'a');
    assert(str_key[6] == 'S');
    assert(str_key[7] == 'V');
    assert(str_key[8] == '0');
    assert(str_key[9] == 'S');
    assert(str_key[10] == 'B');
    assert(str_key[11] == 'B');
    assert(str_key[12] == 'V');
    assert(str_key[13] == 'c');
    assert(str_key[14] == 'S');
    assert(str_key[15] == 'V');
    assert(str_key[16] == 'd');    

    printf("Str = %s\n", str_key);

    free(str_key);
    v_key = vect_delete(v_key);
    assert(v_key == NULL);

    radix = radix_delete(radix);
    assert(radix == NULL);
    
    SUCCESS();
    return 1;
}

static int test_make_key() {

    ENTERING();

    radix_t radix = radix_maker();
    assert(radix != NULL);

    INVALID();

    char* str_key = make_key(NULL);
    assert(str_key == NULL);

    SUCCESS();

    VALID();

    str_key = make_key(radix);
    assert(str_key != NULL);
    assert(str_key[0] == 'V');
    assert(str_key[1] == '0');
    assert(str_key[2] == 'S');
    assert(str_key[3] == 'B');
    assert(str_key[4] == 'V');
    assert(str_key[5] == 'a');
    assert(str_key[6] == 'S');
    assert(str_key[7] == 'V');
    assert(str_key[8] == '0');
    assert(str_key[9] == 'S');
    assert(str_key[10] == 'B');
    assert(str_key[11] == 'B');
    assert(str_key[12] == 'V');
    assert(str_key[13] == 'c');
    assert(str_key[14] == 'S');
    assert(str_key[15] == 'V');
    assert(str_key[16] == 'd');    

    printf("Str = %s\n", str_key);
    free(str_key);
    radix = radix_delete(radix);
    assert(radix == NULL);
    
    SUCCESS();
    
    return 1;
}

static int test_radix_add_in_hash() {

    ENTERING();

    radix_t radix = radix_maker();
    assert(radix != NULL);

    hash_t h_tab = hash_patricia_new(75);
    assert(h_tab != NULL);
    INVALID();

    int rst = radix_add_in_hash(NULL, h_tab);
    assert(rst == -1);
    
    rst = radix_add_in_hash(radix, NULL);
    assert(rst == -2);
    
    SUCCESS();

    //radix_print2(radix);
    rst = radix_add_in_hash(radix, h_tab);
    assert(rst == 1);

    char* key = make_key(radix);
    cell_t cell =hash_get_value(key, h_tab);  
    assert(cell != NULL);
    assert(cell->data == radix);
    assert(strcmp(cell->key,key) == 0);

    free(key);
    radix = radix_delete(radix);
    assert(radix == NULL);

    h_tab = hash_delete(h_tab);
    assert(h_tab == NULL);
    VALID();
    
    SUCCESS();
    return 1;
}

static int test_radix_in_hash_find() {

    ENTERING();

    hash_t h_tab = hash_patricia_new(75);
    assert(h_tab != NULL);

    radix_t radix = radix_maker();
    assert(radix != NULL);

    int rst = radix_add_in_hash(radix, h_tab);
    assert(rst == 1);

    INVALID();
    
    radix_t radix_find = radix_in_hash_find(NULL, h_tab);
    assert(radix_find == NULL);

    radix_find = radix_in_hash_find(radix, NULL);
    assert(radix_find == NULL);
    
    SUCCESS();

    VALID();

    radix_find = radix_in_hash_find(radix, h_tab);
    assert(radix_find == radix);
    
    rst = radix_add_word(radix, "Zdef");
    assert(rst == 1);

    radix_find = radix_in_hash_find(radix, h_tab);
    assert(radix_find == NULL);

    radix = radix_delete(radix);
    assert(radix == NULL);

    h_tab = hash_delete(h_tab);
    assert(h_tab == NULL);
    
    SUCCESS();
    return 1;
}

hash_t hash_maker() {

    hash_t h_tab = hash_patricia_new(75);
    assert(h_tab != NULL);

    radix_t radix = radix_maker();
    assert(radix != NULL);

    int rst = radix_add_in_hash(radix, h_tab);
    assert(rst == 1);

    return h_tab;
}

int test_patricia_compress() {

    ENTERING();

    hash_t h_tab = hash_patricia_new(75);
    assert(h_tab != NULL);

    radix_t radix = radix_maker();
    assert(radix != NULL);

    INVALID();

    radix_t compressed_radix = patricia_compress(NULL, h_tab);
    assert(compressed_radix == NULL);

    compressed_radix = patricia_compress(radix, NULL);
    assert(radix == compressed_radix);

    SUCCESS();

    VALID();
    compressed_radix = patricia_compress(radix, h_tab);
    assert(radix == compressed_radix);

    printf("compressed = %p\n", compressed_radix);
    radix_print2(compressed_radix);

    VALID();

    radix = patricia_compressed_delete(radix);
    assert(radix == NULL);
    h_tab = hash_delete(h_tab);
    assert(h_tab == NULL);
    SUCCESS();
    return 1;
}

int test_patricia_compressor() {

    ENTERING();

    radix_t radix = radix_maker();
    assert(radix != NULL);

    INVALID();

    radix_t tmp_radix = patricia_compressor(NULL);
    assert(tmp_radix == NULL);

    SUCCESS();

    radix = patricia_compressor(radix);
    assert(radix != NULL);

    VALID();

    radix = patricia_compressed_delete(radix);
    assert(radix == NULL);
    SUCCESS();
    return 1;
}

int test_() {

    ENTERING();

    INVALID();

    SUCCESS();

    VALID();

    SUCCESS();
    return 1;
}
int main() {

    test_v_key_new();
    test_make_add_char();
    test_add_v_key_char();
    test_make_char_key();
    test_make_key();
    test_radix_add_in_hash();
    test_radix_in_hash_find();
    test_patricia_compress();
    test_patricia_compressor();

    EXIT();
}