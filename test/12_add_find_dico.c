#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h> 
#include "hash_table.h"
#include "add_find_dico.h"

#define ENTERING() fprintf(stderr, "\n## Enterring in %s function\n", __func__);
#define VALID()    fprintf(stderr, "<= Test : We try valid parameters, must return not errors\n");
#define INVALID()  fprintf(stderr, "<= Test : We try invalids parameters, must return errors\n");
#define SUCCESS()  fprintf(stderr, "=> Test passed with success\n");
#define EXIT()     fprintf(stderr, "Tests of file %s passed with success\n", __FILE__); return EXIT_SUCCESS;

#define ERR(msg) fprintf(stderr, "Error in 12_add_find_dico.c: %s\n", msg)


int test_() {

    ENTERING();

    INVALID();

    SUCCESS();

    VALID();

    SUCCESS();
    return 1;
}

static int str_compare(char *s1, char* s2) {

    int rst = (strcmp(s1, s2) + 1);
   return rst;
}

static void print_str(char* s) {
    printf("%s", s);
}

static size_t hash_string(char* str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;  // hash * 33 + c
    }

    return hash;
}

static char* delete_str(char* str) {

    if (str == NULL) {
        return NULL;
    }
    free(str);
 
    str = NULL;
   return str;
}

static void* hash_put_wrapper(char* str, hash_t h_tab) {

    int rst = hash_put(str, (void*)0x1, h_tab);
    if (rst <= 0) {
        ERR("hash_put failed");
        return NULL;
    }
    else {
        return h_tab;
    }
}

int test_create_using_dico_hash_table() {

    ENTERING();

    VALID();


    FILE* fp = fopen("./dico_txt/dico1.txt", "r");
    if (fp == NULL) {
        ERR("Failed to open the dictionary file");
        return -1;
    }

    printf("delete_str = %p\n", delete_str);
    hash_t h_tab = hash_new(10, (size_t (*)(void *))hash_string, (void *(*)(void *))delete_str, (void *(*)(void *))0x1,
    (int (*)(void *, void *))str_compare, (int (*)(void *, void *))0x1, (void (*)(void *))print_str, (void (*)(void *))0x1);
    //0X1 IS FOR USELLESS FUNCTION, BUT NULL IS INVALID (will not code them just for fun, the best code to debug is no code)

    if (h_tab == NULL) {
        ERR("Hash_new failed");
        return -2;
    }


    h_tab = add_dico_from_file(fp, (void*)h_tab, (void* (*)(char*, void*))hash_put_wrapper);
    assert(h_tab != NULL);
    if (h_tab == NULL) {
        ERR("Add_dico_fom_file failed");
        return -3;
    }

    printf("BEGIN FIND\n");
    char key[] = "a";
    cell_t cell = hash_get_value(key, h_tab);
    if (cell == NULL) {

        return 0;
    }
    else {
        return 1;
    }

    printf("BEGIN FREE\n");
    h_tab = hash_delete(h_tab);
    assert(h_tab == NULL);
    fclose(fp);

    SUCCESS();
    return 1;
}

int main() {

    test_create_using_dico_hash_table();
    EXIT();
}