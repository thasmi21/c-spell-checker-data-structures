#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h> 
#include "tree_patricia.h"
#include "add_find_dico.h"
#include "patricia_compress.h"

#define ENTERING() fprintf(stderr, "\n## Enterring in %s function\n", __func__);
#define VALID()    fprintf(stderr, "<= Test : We try valid parameters, must return not errors\n");
#define INVALID()  fprintf(stderr, "<= Test : We try invalids parameters, must return errors\n");
#define SUCCESS()  fprintf(stderr, "=> Test passed with success\n");
#define EXIT()     fprintf(stderr, "Tests of file %s passed with success\n", __FILE__); return EXIT_SUCCESS;

#define ERR(msg) fprintf(stderr, "Error in 14_add_find_ttp.c: %s\n", msg)

int test_() {

    ENTERING();

    INVALID();

    SUCCESS();

    VALID();

    SUCCESS();
    return 1;
}

// static int str_compare(char *s1, char* s2) {

//     int rst = (strcmp(s1, s2) + 1);
//    return rst;
// }

// static void print_str(char* s) {
//     printf("%s", s);
// }

// static char* delete_str(char* str) {

//     if (str == NULL) {
//         return NULL;
//     }
//     free(str);
 
//     str = NULL;
//    return str;
// }

static void* patrica_add_word_reverse(char* str, radix_t radix) {

    int rst = radix_add_word(radix, str);
    free(str);
    if (rst <= 0) {
        radix_delete(radix);
        ERR("rst <= 0");
        return NULL;
    }
    else {
        return radix;
    }
}

int test_create_using_dico_tp_table() {

    ENTERING();

    VALID();


    FILE* fp = fopen("./dico_txt/dico1.txt", "r");
    if (fp == NULL) {
        ERR("Failed to open the dictionary file");
        return -1;
    }

    radix_t radix = radix_new('\0', NULL);

    if (radix == NULL) {
        ERR("radix_new failed");
        return -2;
    }

    radix = (radix_t)add_dico_from_file(fp, (void*)radix, (void* (*)(char*, void*))patrica_add_word_reverse, 2000);
    assert(radix != NULL);
    if (radix == NULL) {
        ERR("Add_dico_fom_file failed");
        return -3;
    }

    printf("BEGIN COMPRESS");
    radix = patricia_compressor(radix);
    if (radix == NULL) {
        ERR("radix_compressor failed");
        return -4;
    }
    printf("END COMPRESS");

    int rst = radix_find(radix, "a");
    assert(rst == 1);
    printf("a found\n");

    rst = radix_find(radix, "azertyp");
    assert(rst == 0);
    printf("azertyp not found (is not in there)\n");

    radix = patricia_compressed_delete(radix);
    assert(radix == NULL);
    fclose(fp);

    SUCCESS();
    return 1;
}

int main() {

    test_create_using_dico_tp_table();
    EXIT();
}