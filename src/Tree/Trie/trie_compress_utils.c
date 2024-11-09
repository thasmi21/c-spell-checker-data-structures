#include <stdlib.h>
#include <stdio.h>

#include "tree_trie.h"
#include "dico_utils.h"
#include "add_find_dico.h"
#include "trie_compress.h"

#define ERR(msg) printf("Error in patricia_compress.c/%s: %s\n", __func__, msg)

static void* trie_add_word_reverse(char* str, trie_t trie) {
    int rst = trie_add_word(trie, str);
    free(str);
    if (rst <= 0) {
        trie_delete(trie);
        return NULL;
    }
    else {
        return trie;
    }
}

trie_t trie_compressed_controler(FILE* fp) {
    
    if (fp == NULL) {
        ERR("fp == NULL");
    }

    trie_t trie = trie_new();

    trie = add_dico_from_file(fp, (void*)trie, (void* (*)(char*, void*))trie_add_word_reverse, -1);
    if (trie == NULL) {
        ERR("Add_dico_fom_file failed");
        return NULL;
    }

    trie = trie_compressor(trie);
    if (trie == NULL) {
        ERR("trie compressor failed");
        return trie;
    }
    return trie;
}

int trie_compressed_find(char* key, trie_t dico) {
    
    if (dico == NULL) {
        ERR("dico failed");
        return -1;
    }

    if (key == NULL) {
        ERR("key failed");
        return -2;
    }

    int rst = trie_find_word(dico, key);
    if (rst < 0) {
        ERR("Trie_find error");
        return -3;
    }

    if (rst == 0) {
        return 0;
    }
    else {
        return 1;
    }
}

trie_t trie_compressed_dico_delete(trie_t dico) {
    
    dico = trie_compressed_delete(dico);
    if (dico != NULL) {
        ERR("trie_compressed_delete failed");
        return dico;
    }    
    
    return NULL;  // Returning NULL to indicate delete success
}