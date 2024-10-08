#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <../include/cell.h>
#include <../include/hash_table.h>  
#include <../include/vector.h>
#include <../include/key.h>

#define ERR(msg) printf("Error in key.c/%s: %s\n", __func__, msg)

static void print_char(char* c) {
    printf("%c", *c);
}

static int equal_char(char* c1, char* c2) {

    if (c1 == NULL) {
        if (c2 == NULL) {
            return 1;
        }
        return 0;
    }

    return (*c1 == *c2);
}

static char* delete_char(char* c) {

    if (c == NULL) {
        return NULL;
    }
    free(c);
 
    c = NULL;
    return c;
}

char* char_make(char c) {

    char* p_char;
    p_char = malloc(sizeof(char));
    if (p_char == NULL) {
        ERR("p_char is NULL, vect_new failed");
        return NULL;
    }

    *p_char = c;
    return p_char;
}

vect_t v_key_new() {
    
    vect_t v_key = vect_new(5, (void(*)(void*))print_char, (void*(*)(void*))delete_char, (int(*)(void*,void*))equal_char);
    if (v_key == NULL) {
        ERR("v_key is NULL, vect_new failed");
        return NULL;
    }
    return v_key;
}


int make_add_char(char c, vect_t v_key) {
    char* p_charV = char_make(c);
    if (p_charV == NULL) {
        free(p_charV);
        ERR("char_make failed");
        return -1;
    }
    int rst = vect_append(p_charV, v_key);
    if (rst != 1) {
        free(p_charV);
        ERR("vect_append failed");
        return -2;
    }
    return 1;
}

char* make_char_key(vect_t v_key) {
    
    if (v_key == NULL) {
        ERR("v_key = NULL");
        return NULL;
    }

    if (v_key->data == NULL) {
        ERR("v_key->data = NULL");
        return NULL;
    }
    size_t n = v_key->actual_size;

    if (n == 0) {
        ERR("n = 0");
        return NULL;
    }
    char* str_key = malloc(sizeof(char) * (n + 1));

    if (str_key == NULL) {
        ERR("Str_key = NULL, malloc failed");
        return NULL;
    }

    for (size_t i = 0; i < n; i++) {
        char* p_c = (char*)(v_key->data)[i];

        if (p_c == NULL) {
            ERR("p_c = NULL");
            free(str_key);
            str_key = NULL;
            return NULL;
        }

        if (*p_c == '\0') {
            str_key[i] = '0';
        }
        else {
            str_key[i] = *p_c;
        }
    }

    str_key[n] = '\0';
    return str_key;
}


char* make_key(void* tree, int(*make_v_key)(void*, vect_t) ) {
    
    if (tree == NULL) {
        ERR("tree = NULL");
        return NULL;
    }

    vect_t v_key = v_key_new();
    if (v_key == NULL) {
        ERR("v_key->data = NULL, v_key_new failed");
        return NULL;
    }

    int rst = make_v_key(tree, v_key);
    if (rst != 1) {
        v_key = vect_delete(v_key);
        if(v_key != NULL) {
            ERR("vect_delete failed");
        }
        ERR("rst != 1, make_v_key failed");
        return NULL;
    }

    char* str_key = make_char_key(v_key);
    if (str_key == NULL) {
        v_key = vect_delete(v_key);
        if(v_key != NULL) {
            ERR("vect_delete failed");
        }
        ERR("str_key = NULL");
        return NULL;
    }

    v_key = vect_delete(v_key);
    if (v_key != NULL) {
        free(str_key);
        str_key = NULL;
        ERR("v_key != NULL vect_delete failed");
        return NULL;
    }

    return str_key;
}

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

hash_t hash_tree_new(size_t n, void(*print_tree)(void*)) {

    hash_t h_tab = hash_new(n, (size_t (*)(void *))hash_string, (void *(*)(void *))delete_char, (void *(*)(void *))0x1,
     (int (*)(void *, void *))str_compare, (int (*)(void *, void *))0x1, (void (*)(void *))print_str, print_tree);
    //0X1 IS FOR USELLESS FUNCTION, BUT NULL IS INVALID (will not code them just for fun, the best code to debug is no code)

    if (h_tab == NULL) {
        ERR("Hash_new failed");
        return NULL;
    }
    return h_tab;
} 

int tree_add_in_hash(void* tree, hash_t h_tab, int(*make_v_key)(void*, vect_t)) {

    if (tree == NULL) {
        ERR("tree = NULL");
        return -1;
    }

    if (h_tab == NULL) {
        ERR("h_tab = NULL");
        return -2;
    }

    char* str_key = make_key(tree, make_v_key);
    if (str_key == NULL) {
        ERR("str_key == NULL, make_key failed");
        return -3;
    }

    int rst = hash_put(str_key, tree, h_tab);
    if (rst != 1) {
        free(str_key);
        str_key = NULL;
        ERR("rst != 1, hash_put failed");
        return -4;
    }
    return 1;
}

void* tree_in_hash_find(void* tree, hash_t h_tab, int (*add_v_key_chars)(void *, vect_t)) {

    if (tree == NULL) {
        ERR("tree is NULL");
        return NULL;
    }

    if (h_tab == NULL) {
        ERR("h_tab is NULL");
        return NULL;
    }

    char* str_key = make_key(tree, add_v_key_chars);
    if (str_key == NULL) {
        ERR("str_key == NULL, make_key failed");
        return NULL;
    }
    
    cell_t cell = hash_get_value(str_key, h_tab);
    if (cell == NULL) {
        free(str_key);
        str_key = NULL;
        return NULL;
    }

    free(str_key);
    str_key = NULL;

    if (cell->data == NULL) {
        ERR("Cell->data = NULL, should not be NULL");
        return NULL;
    }
    return cell->data;
}

void* tree_compressor(void* tree, void* (*tree_compress)(void*, hash_t), void(*tree_print)(void*)) {

    if (tree == NULL) {
        ERR("tree = NULL");
        return NULL;
    }

    hash_t h_tab = hash_tree_new(100, tree_print);
    
    if (h_tab == NULL) {
        ERR("hash_tree_new failed");
        return NULL;
    }

    if (h_tab == NULL) {
        ERR("hash_new failed");
        return tree;
    }

    tree = tree_compress(tree, h_tab);

    if (tree == NULL) {
        ERR("tree_compress failed");
        return tree;
    }

    h_tab = hash_delete(h_tab);

    if (h_tab != NULL) {
        ERR("hash delete failed");
        return tree;
    }

    return tree;
}