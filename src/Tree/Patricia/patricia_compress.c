#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "cell.h"
#include "hash_table.h"  
#include "tree_patricia.h"
#include "vector.h"
#include "patricia_compress.h"
#include "key.h"


#define ERR(msg) printf("Error in patricia_compress.c/%s: %s\n", __func__, msg)

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

char* make_key_radix(radix_t radix) {
    
    if (radix == NULL) {
        ERR("radix = NULL");
        return NULL;
    }

    char* str_key = make_key(radix, (int (*)(void *, vect_t))add_v_key_char);
    if (str_key == NULL) {
        ERR("str_key = NULL");
        return NULL;
    }

    return str_key;
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

    int rst = tree_add_in_hash((void*)radix, h_tab, (int (*)(void *, vect_t))add_v_key_char);
    if (rst != 1) {
        ERR("rst != 1, hash_put failed");
        return -3;
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
    //radix_print2(radix);
    radix_t radix_bis = (radix_t)tree_in_hash_find((void*)radix, h_tab, (int (*)(void *, vect_t))add_v_key_char);
    return radix_bis;
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
            return NULL;
        }
    }

    if (radix->brothers != NULL) {
        radix->brothers = patricia_compress(radix->brothers, h_tab);
        if (radix->brothers == NULL) {
            ERR("In case, radix->brothers != NULL, rst != 1, patricia_compress failed");
            return NULL;
        }
    }

    radix_t radix_bis = radix_in_hash_find(radix, h_tab);
    if (radix_bis == NULL) {
        int rst = radix_add_in_hash(radix, h_tab);
        if (rst != 1) {
            ERR("In case, radix_bis == NULL, rst != 1, radix_add_in_hash failed");
            return NULL;
        }
        return radix;
    }
    else {

        radix_bis->nb_of_parents = radix_bis->nb_of_parents + radix->nb_of_parents;
        radix = patricia_compressed_delete(radix);
        if (radix != NULL) {
            ERR("In case, else, radix != NULL, patricia_compressed_delete failed");
            return NULL;
        }

        return radix_bis;
    }
} 


hash_t hash_patricia_new(size_t n) {

    hash_t h_tab = hash_tree_new(n, (void (*)(void *))radix_print2);

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

    radix_t radix_compressed = (radix_t)tree_compressor((void*)radix, (void* (*)(void*, hash_t))patricia_compress, (void(*)(void*))radix_print2);
    
    if (radix_compressed == NULL) {
        ERR("radix_compressed == NULL");
        return radix;
    }

    return radix_compressed;
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