#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "dico_utils.h"
#include "add_find_dico.h"
#include "hash_table.h"
#include "dico_utils.h"

#define ERR(msg) fprintf(stderr, "Error in hash_utils.c: %s\n", msg)

static int str_compare(char *s1, char* s2) {
   return (strcmp(s1, s2) + 1);
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

hash_t hash_dico_controler(FILE* fp) {
    
    if (fp == NULL) {
        ERR("fp = NULL");
        return NULL;
    }

    hash_t h_tab = hash_new(100, (size_t (*)(void *))hash_string, (void *(*)(void *))delete_str, (void *(*)(void *))0x1,
    (int (*)(void *, void *))str_compare, (int (*)(void *, void *))0x1, (void (*)(void *))print_str, (void (*)(void *))0x1);
    //0X1 IS FOR USELLESS FUNCTION, BUT NULL IS INVALID (will not code them just for fun, the best code to debug is no code)

    if (h_tab == NULL) {
        ERR("Hash_new failed");
        return NULL;
    }

    h_tab = add_dico_from_file(fp, (void*)h_tab, (void* (*)(char*, void*))hash_put_wrapper);

    if (h_tab == NULL) {
        ERR("Add_dico_fom_file failed");
        return NULL;
    }
    return h_tab;  // Returning NULL as a placeholder
}

int hash_dico_find(char* key, hash_t dico) {
    
    if (dico == NULL) {
        ERR("dico failed");
        return -1;
    }

    if (key == NULL) {
        ERR("key failed");
        return -2;
    }

    cell_t cell = hash_get_value(key, dico);

    if (cell == NULL) {
        return 0;
    }
    else {
        return 1;
    }
}

hash_t hash_dico_delete(hash_t dico) {

    dico = hash_delete(dico);
    if (dico != NULL) {
        ERR("Hash_delete failed");
        return dico;
    }
    return NULL;  // Returning NULL to indicate successful delete
}