
#include <stdlib.h>
#include <stdio.h>

#include "tree_patricia.h"
#include "dico_utils.h"
#include "add_find_dico.h"

#define ERR(msg) printf("Error in patricia_utils.c/%s: %s\n", __func__, msg)

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

radix_t tree_patricia_controler(FILE* fp) {

    if (fp == NULL) {
        ERR("fp = NULL");
        return NULL;
    }

    radix_t radix = radix_new('\0', NULL);

    radix = add_dico_from_file(fp, (void*)radix, (void* (*)(char*, void*))patrica_add_word_reverse, -1);
    if (radix == NULL) {
        ERR("Add_dico_fom_file failed");
        return NULL;
    }

    return radix;
}

int tree_patricia_find(char* key, radix_t dico) {

    if (dico == NULL) {
        ERR("dico failed");
        return -1;
    }

    if (key == NULL) {
        ERR("key failed");
        return -2;
    }
    int rst = radix_find(dico, key);
    if (rst < 0) {
        ERR("tree_patricia_find error");
        return -3;
    }

    if (rst == 0) {
        return 0;
    }
    else {
        return 1;
    }
    return 0;  // Returning 0 to indicate "not found"
}

radix_t tree_patricia_dico_delete(radix_t dico) {

    dico = radix_delete(dico);
    if (dico != NULL) {
        ERR("radix_delete failed");
        return dico;
    }
    
    return NULL;  // Returning NULL to indicate delete success
}