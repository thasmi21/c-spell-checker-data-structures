#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "tree_trie.h"

#define ERR(msg) printf("Error in tree_trie.c/%s: %s\n", __func__, msg)

trie_t trie_new() {

    trie_t trie;
    trie = malloc(sizeof(*trie));
    
    if (trie == NULL) {
        ERR("Malloc failed");
        return NULL;
    }

    trie->nb_of_parents = 1;
    
    for (int i = 0; i<ASIZE; i++) {
        (trie->sons)[i] = NULL;
    }
    return trie;
}

int trie_add_word(trie_t trie, char* str) {

    if (trie == NULL) {
        ERR("Tree = NULL");
        return -1;
    }

    if (str == NULL) {
        ERR("Str = NULL");
        return -2;
    }

    //if (trie->sons == NULL) {
    //   ERR("Tree->sons = NULL");
    //    return -3;
    //}

    trie_t p_trie = trie;
    trie_t* sons = trie->sons;
    char* p_char = str;
    char c = *p_char;
    while (c != '\0') {
        int indice = c - 0x61;
        if (indice <0 || indice >= 27) {
            ERR("Invalid char do not add");
            printf("c = %c in str = %s, code will continue but but adding the modulo char\n", c, str);
            if (indice < 0) {
                indice = -indice;
            }
            indice = indice%26;
        }

        if (sons == NULL) {
            ERR("sons is NULL");
            return -5;
        }

        if (sons[indice] == NULL) {

            sons[indice] = trie_new();

            if (sons[indice] == NULL) {
                ERR("Son[indice] == NULL, trie_new() failed");
                return -4;
            }
        }

        p_trie = sons[indice];
        sons = p_trie->sons;
        if (sons == NULL) {
            ERR("New Sons[indice] = NULL, getting trie->sons failed");
            return -5;
        }

        p_char++;

        c = *p_char;

    }

    if (sons[ASIZE - 1] == NULL) {
        sons[ASIZE - 1] = trie_new();

        if (sons[ASIZE - 1] == NULL) {
            ERR("Son[ASIZE - 1] == NULL, trie_new() failed FOR \0");
            return -6;
        }
    }
    return 1;
}

int trie_find_word(trie_t trie, char* str) {
    
    if (trie == NULL) {
        ERR("Tree = NULL");
        return -1;
    }

    if (str == NULL) {
        ERR("Str = NULL");
        return -2;
    }

    //if (trie->sons == NULL) {
    //    ERR("Tree->sons = NULL");
    //    return -3;
    //}

    trie_t p_trie = trie;
    trie_t* sons = trie->sons;
    char* p_char = str;
    char c = *p_char;
    while (c != '\0') {

        int indice = c - 0x61;
        if (sons[indice] == NULL) {
            return 0;
        }
        p_trie = sons[indice];
        sons = p_trie->sons;
        if (sons == NULL) {
            ERR("New Sons[indice] = NULL, getting trie->sons failed");
            return -5;
        }

        p_char++;
        c = *p_char;
    }

    if (sons[ASIZE - 1] == NULL) {
        return 0;
    }

    return 1;
}

trie_t trie_delete(trie_t trie) {

    if (trie == NULL) {
        ERR("Tree = NULL");
        return NULL;
    }

    //if (trie->sons == NULL) {
    //    ERR("Tree->sons = NULL");
    //    return trie;
    //}

    trie_t p_trie = NULL;
    trie_t* sons = trie->sons;
    for (int i = 0; i<ASIZE; i++) {
        
        int sons_i_exist = (sons[i] != NULL);
        if (sons_i_exist) {
            p_trie = trie_delete(sons[i]);
            if (p_trie != NULL) {
                ERR("trie_delete failed");
                return trie;
            }
        }
    }
    free(trie);
    trie = NULL;
    return NULL;
}

void trie_print(trie_t trie, size_t index) {

    if (trie == NULL) {
        return;
    }
    for (int i = 0; i < ASIZE; i++) {
        trie_t p_son = (trie->sons)[i];
        if (p_son != NULL) {

            char c = 'a' + i;
            
            for (size_t j = 0; j < index; j++) {
                printf("| - ");
            }

            if (i == 26) {
                //printf("0, %p\n", trie);
                printf("0\n");
            }
            else {
                //printf("%c, %p\n", c, trie);
                printf("%c\n", c);
            }
            trie_print(p_son, index + 1);
        }
    }
}


void trie_print2(trie_t trie) {
    trie_print(trie, 0);
}

static void trie_print_test(trie_t trie, size_t index) {

    if (trie == NULL) {
        return;
    }
    for (int i = 0; i < ASIZE; i++) {
        trie_t p_son = (trie->sons)[i];
        if (p_son != NULL) {

            char c = 'a' + i;
            
            for (size_t j = 0; j < index; j++) {
                printf("| - ");
            }

            if (i == 26) {
                printf("0, %p\n", trie);
                //printf("0\n");
            }
            else {
                printf("%c, %p\n", c, trie);
                //printf("%c\n", c);
            }
            trie_print_test(p_son, index + 1);
        }
    }
}

void trie_print_test2(trie_t trie) {
    trie_print_test(trie, 0);
}
