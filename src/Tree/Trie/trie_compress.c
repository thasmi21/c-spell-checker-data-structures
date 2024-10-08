#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "cell.h"
#include "hash_table.h"  
#include "vector.h"
#include "tree_trie.h"
#include "key.h"
#include "trie_compress.h"

#define ERR(msg) printf("Error in trie_compress.c/%s: %s\n", __func__, msg)

int add_v_key_chars_trie(trie_t trie, vect_t v_key) {
    if (trie == NULL) {
        ERR("trie = NULL");
        return -1;
    }

    if (v_key == NULL) {
        ERR("v_key = NULL");
        return -2;
    }

    int rst;
    for (int i = 0; i < ASIZE; i++) {

        if ((trie->sons)[i] != NULL) {
            rst = make_add_char('V', v_key); //add value ref
            if (rst != 1) {
                ERR("Make_add_char V failed");
                return -3;
            }

            if (i == ASIZE - 1) {
                rst = make_add_char('0', v_key);
                if (rst != 1) {
                    ERR("Make_add_char 0 failed");
                    return -4;
                }
            }
            else {
                char c = 'a' + i;
                rst = make_add_char(c, v_key);
                if (rst != 1) {
                ERR("Make_add_char char c failed");
                return -5;
                }
            }

            rst = make_add_char('S', v_key); //add sons ref
            if (rst != 1) {
            ERR("Make_add_char S failed");
            return -6;
            }

            rst =  add_v_key_chars_trie((trie->sons)[i], v_key);
            if (rst != 1) {
            ERR("add_v_key_chars_trie sons[i] failed");
            return -7;
            }
        }
    }

    rst = make_add_char('E', v_key); //exiting ref
    if (rst != 1) {
        ERR("Make_add_char E failed");
        return -8;
    }
    return 1;
}

trie_t trie_compress(trie_t trie, hash_t h_tab) {
    
    if(trie == NULL) {
        ERR("trie = NULL");
        return NULL;
    }

    if (h_tab == NULL) {   
        ERR("h_tab = NULL");
        return trie;
    }

    for (int i = 0; i < ASIZE; i++) {

        if ((trie->sons)[i] != NULL) {
            (trie->sons)[i] = trie_compress((trie->sons)[i], h_tab);
            if ((trie->sons)[i] == NULL) {
                ERR("In case, (trie->sons)[i] != NULL, rst != 1, trie_compress failed");
                return trie;
            }
        }
    }

    trie_t trie_bis = (trie_t)tree_in_hash_find((void*)trie, h_tab, (int (*)(void *, vect_t))add_v_key_chars_trie);
    if (trie_bis == NULL) {
        int rst = tree_add_in_hash(trie, h_tab, (int (*)(void *, vect_t))add_v_key_chars_trie);
        if (rst != 1) {
            ERR("In case, trie_bis == NULL, rst != 1, trie_add_in_hash failed");
            return trie;
        }
        return trie;
    }
    else {

        trie_bis->nb_of_parents = trie_bis->nb_of_parents + trie->nb_of_parents;
        trie = trie_compressed_delete(trie);
        if (trie != NULL) {
            ERR("In case, else, trie != NULL, trie_compressed_delete failed");
            return trie;
        }

        return trie_bis;
    }
}

trie_t trie_compressor(trie_t trie) {

    if (trie == NULL) {
        ERR("trie = NULL");
        return NULL;
    }

    trie_t trie_compressed = (trie_t)tree_compressor((void*)trie, (void* (*)(void*, hash_t))trie_compress, (void(*)(void*))trie_print2);
    
    if (trie_compressed != NULL) {
        ERR("trie_compressed = NULL");
        return trie;
    }

    return trie_compressed;
}

trie_t trie_compressed_delete(trie_t trie) {

    if (trie == NULL) {
        ERR("trie = NULL");
        return NULL;
    }

    for (int i = 0; i < ASIZE; i++) {
        
        trie_t* p_son = trie->sons;
        if (p_son[i] != NULL) {

            if ( (p_son[i])->nb_of_parents == 0 ) {
                ERR("MAJOR BUG, trie->sons->nb_of_parents == 0");
                return trie;
            }

            if ( (p_son[i])->nb_of_parents != 1 ) {
                ((p_son[i])->nb_of_parents)--;
                p_son[i] = NULL;
            }
            else {
                p_son[i] =  trie_compressed_delete(p_son[i]);
                if (p_son[i] != NULL) {
                    ERR("In case, trie->sons[i] != NULL else, trie->sons[i] != NULL, trie_compressed_delete failed");
                    return p_son[i];
                }
            }
        }

    }

    free(trie);
    trie = NULL;
    return trie;
}