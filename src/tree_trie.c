#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../include/tree_trie.h"

#define ERR(msg) printf("Error in tree_trie.c/%s: %s\n", __func__, msg)

tree_t tree_new() {

    tree_t tree;
    tree = malloc(sizeof(*tree));
    
    if (tree == NULL) {
        ERR("Malloc failed");
        return NULL;
    }

    tree->nb_of_parents = 1;
    
    for (int i = 0; i<ASIZE; i++) {
        (tree->sons)[i] = NULL;
    }
    return tree;
}

int tree_add_word(tree_t tree, char* str) {

    if (tree == NULL) {
        ERR("Tree = NULL");
        return -1;
    }

    if (str == NULL) {
        ERR("Str = NULL");
        return -2;
    }

    //if (tree->sons == NULL) {
    //   ERR("Tree->sons = NULL");
    //    return -3;
    //}

    tree_t p_tree = tree;
    tree_t* sons = tree->sons;
    char* p_char = str;
    char c = *p_char;
    while (c != '\0') {

        int indice = c - 0x61;
        if (sons[indice] == NULL) {
            sons[indice] = tree_new();

            if (sons[indice] == NULL) {
                ERR("Son[indice] == NULL, tree_new() failed");
                return -4;
            }
        }
        p_tree = sons[indice];
        sons = p_tree->sons;
        if (sons == NULL) {
            ERR("New Sons[indice] = NULL, getting tree->sons failed");
            return -5;
        }

        p_char++;
        c = *p_char;
    }

    if (sons[ASIZE - 1] == NULL) {
        sons[ASIZE - 1] = tree_new();

        if (sons[ASIZE - 1] == NULL) {
            ERR("Son[ASIZE - 1] == NULL, tree_new() failed FOR \0");
            return -6;
        }
    }
    return 1;
}

int tree_find_word(tree_t tree, char* str) {
    
    if (tree == NULL) {
        ERR("Tree = NULL");
        return -1;
    }

    if (str == NULL) {
        ERR("Str = NULL");
        return -2;
    }

    //if (tree->sons == NULL) {
    //    ERR("Tree->sons = NULL");
    //    return -3;
    //}

    tree_t p_tree = tree;
    tree_t* sons = tree->sons;
    char* p_char = str;
    char c = *p_char;
    while (c != '\0') {

        int indice = c - 0x61;
        if (sons[indice] == NULL) {
            return 0;
        }
        p_tree = sons[indice];
        sons = p_tree->sons;
        if (sons == NULL) {
            ERR("New Sons[indice] = NULL, getting tree->sons failed");
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

tree_t tree_delete(tree_t tree) {

    if (tree == NULL) {
        ERR("Tree = NULL");
        return NULL;
    }

    //if (tree->sons == NULL) {
    //    ERR("Tree->sons = NULL");
    //    return tree;
    //}

    tree_t p_tree = NULL;
    tree_t* sons = tree->sons;
    for (int i = 0; i<ASIZE; i++) {
        
        int sons_i_exist = (sons[i] != NULL);
        if (sons_i_exist) {
            p_tree = tree_delete(sons[i]);
            if (p_tree != NULL) {
                ERR("tree_delete failed");
                return tree;
            }
        }
    }
    free(tree);
    tree = NULL;
    return NULL;
}

void tree_print(tree_t tree, size_t index) {

    if (tree == NULL) {
        return;
    }
    for (int i = 0; i < ASIZE; i++) {
        tree_t p_son = (tree->sons)[i];
        if (p_son != NULL) {

            char c = 'a' + i;
            
            for (size_t j = 0; j < index; j++) {
                printf("| - ");
            }

            if (i == 26) {
                printf("0\n");
            }
            else {
                printf("%c\n", c);
            }
            tree_print(p_son, index + 1);
        }
    }
}