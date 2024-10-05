#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <../include/cell.h>
#include <../include/hash_table.h>  
#include <../include/tree_patricia.h>
#include <../include/vector.h>
#include <../include/patricia_compress.h>

#define ERR(msg) printf("Error in patricia_compress.c/%s: %s\n", __func__, msg)

static void print_char(char* c) {
    printf("%c", *c);
}

static void print_str(char* s) {
    printf("%s", s);
}


static char* delete_char(char* c) {

    if (c == NULL) {
        return NULL;
    }
    free(c);
 
    c = NULL;
    return c;
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

static char* char_make(char c) {

    char* p_char;
    p_char = malloc(sizeof(char));
    if (p_char == NULL) {
        ERR("p_char is NULL, vect_new failed");
        return NULL;
    }

    *p_char = c;
    return p_char;
}

static size_t hash_string(char* str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;  // hash * 33 + c
    }

    return hash;
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

int add_v_key_char(radix_t radix, vect_t v_key) {
    if (radix == NULL) {
        ERR("radix = NULL");
        return -1;
    }
    if (v_key == NULL) {
        ERR("v_key = NULL");
        return -2;
    }
    int rst = make_add_char('V', v_key); //add value ref
    if (rst != 1) {
        ERR("Make_add_char V failed");
        return -3;
    }
    rst = make_add_char(radix->value, v_key);
    if (rst != 1) {
        ERR("Make_add_char radix->value failed");
        return -4;
    }
    
    rst = make_add_char('S', v_key); //add sons ref
    if (rst != 1) {
        ERR("Make_add_char S failed");
        return -5;
    }
    if (radix->sons != NULL) {
        rst = add_v_key_char(radix->sons, v_key);
        if (rst != 1) {
            ERR("add_v_key_char sons failed");
            return -6;
        }
    }
    
    rst = make_add_char('B', v_key); //add brothers ref
    if (rst != 1) {
        ERR("Make_add_char B failed");
        return -7;
    }
    if (radix->brothers != NULL) {
        rst = add_v_key_char(radix->brothers, v_key);
        if (rst != 1) {
            ERR("add_v_key_char brothers failed");
            return -8;
        }
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

char* make_key(radix_t radix) {
    
    if (radix == NULL) {
        ERR("radix = NULL");
        return NULL;
    }

    vect_t v_key = v_key_new();
    if (v_key == NULL) {
        ERR("v_key->data = NULL, v_key_new failed");
        return NULL;
    }

    int rst = add_v_key_char(radix, v_key);
    if (rst != 1) {
        v_key = vect_delete(v_key);
        if(v_key != NULL) {
            ERR("vect_delete failed");
        }
        ERR("rst != 1, add_v_key_char failed");
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

int radix_add_in_hash(radix_t radix, hash_t h_tab) {

    if (radix == NULL) {
        ERR("radix = NULL");
        return -1;
    }

    if (h_tab == NULL) {
        ERR("h_tab = NULL");
        return -2;
    }

    char* str_key = make_key(radix);
    if (str_key == NULL) {
        ERR("str_key == NULL, make_key failed");
        return -3;
    }

    int rst = hash_put(str_key, radix, h_tab);
    if (rst != 1) {
        free(str_key);
        str_key = NULL;
        ERR("rst != 1, hash_put failed");
        return -4;
    }
    return 1;
}

radix_t radix_in_hash_find(radix_t radix, hash_t h_tab) {

    if (radix == NULL) {
        ERR("radix is NULL");
        return NULL;
    }

    if (h_tab == NULL) {
        ERR("h_tab is NULL");
        return NULL;
    }

    char* str_key = make_key(radix);
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
    return (radix_t)cell->data;
}

radix_t patricia_compress(radix_t radix, hash_t h_tab) {
    if(radix == NULL) {
        ERR("radix = NULL");
        return NULL;
    }

    if (h_tab == NULL) {   
        ERR("h_tab = NULL");
        return radix;
    }

    if (radix->sons != NULL) {

        radix->sons = patricia_compress(radix->sons, h_tab);
        if (radix->sons == NULL) {
            ERR("In case,radix->sons != NULL, rst != 1, patricia_compress failed");
            return radix;
        }
    }

    if (radix->brothers != NULL) {
        radix->brothers = patricia_compress(radix->brothers, h_tab);
        if (radix->brothers == NULL) {
            ERR("In case, radix->brothers != NULL, rst != 1, patricia_compress failed");
            return radix;
        }
    }

    radix_t radix_bis = radix_in_hash_find(radix, h_tab);
    if (radix_bis == NULL) {
        int rst = radix_add_in_hash(radix, h_tab);
        if (rst != 1) {
            ERR("In case, radix_bis == NULL, rst != 1, radix_add_in_hash failed");
            return radix;
        }
        return radix;
    }
    else {

        radix_bis->nb_of_parents = radix_bis->nb_of_parents + radix->nb_of_parents;
        radix = patricia_compressed_delete(radix);
        if (radix != NULL) {
            ERR("In case, else, radix != NULL, patricia_compressed_delete failed");
            return radix;
        }

        return radix_bis;
    }
} 


hash_t hash_patricia_new(size_t n) {

    hash_t h_tab = hash_new(n, (size_t (*)(void *))hash_string, (void *(*)(void *))delete_char, (void *(*)(void *))0x1,
     (int (*)(void *, void *))str_compare, (int (*)(void *, void *))0x1, (void (*)(void *))print_str, (void (*)(void *))radix_print2);
    //0X1 IS FOR USELLESS FUNCTION, BUT NULL IS INVALID (will not code them just for fun, the best code to debug is no code)

    if (h_tab == NULL) {
        ERR("Hash_new failed");
        return NULL;
    }
    return h_tab;
} 

radix_t patricia_compressor(radix_t radix) {
    

    if (radix == NULL) {
        ERR("radix = NULL");
        return NULL;
    }

    hash_t h_tab = hash_patricia_new(100);
    
    if (h_tab == NULL) {
        ERR("hash_patricia_new failed");
        return NULL;
    }

    if (h_tab == NULL) {
        ERR("hash_new failed");
        return radix;
    }

    radix = patricia_compress(radix, h_tab);

    if (radix == NULL) {
        ERR("patricia_compress failed");
        return radix;
    }

    h_tab = hash_delete(h_tab);

    if (h_tab != NULL) {
        ERR("hash delete failed");
        return radix;
    }

    return radix;
}

radix_t patricia_compressed_delete(radix_t radix) {

    if (radix == NULL) {
        ERR("radix = NULL");
        return NULL;
    }

    if (radix->sons != NULL) {

        if (radix->sons->nb_of_parents == 0) {
            ERR("MAJOR BUG, radix->sons->nb_of_parents == 0");
            return radix;
        }
        if (radix->sons->nb_of_parents != 1) {
            (radix->sons->nb_of_parents)--;
            radix->sons = NULL;
        }
        else{
            radix->sons =  patricia_compressed_delete(radix->sons);
            if (radix->sons != NULL) {
                ERR("In case, radix->sons != NULL else, radix->sons != NULL, patricia_compressed_delete failed");
                return radix->sons;
            }
        }
    }
    if (radix->brothers != NULL) {

        if (radix->brothers->nb_of_parents == 0) {
            ERR("MAJOR BUG, radix->brothers->nb_of_parents == 0");
            return radix;
        }

        if (radix->brothers->nb_of_parents != 1) {
            (radix->brothers->nb_of_parents)--;
            radix->brothers = NULL;
        }
        else{
            radix->brothers =  patricia_compressed_delete(radix->brothers);
            if (radix->brothers != NULL) {
                ERR("In case, radix->brothers != NULL else, radix->brothers != NULL, patricia_compressed_delete failed");
                return radix->brothers;
            }
        }
    }
    
    if (radix->sons != NULL || radix->brothers != NULL) {
        ERR("patricia_compressed_delete failed getting family to NULL before freeing the node");
        return radix;
    }

    free(radix);
    radix = NULL;
    return radix;
}