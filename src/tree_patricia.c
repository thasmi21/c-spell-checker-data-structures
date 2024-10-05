#include <stdio.h>
#include <stdlib.h>

#include "../include/tree_patricia.h"

#define ERR(msg) printf("Error in tree_patricia.c/%s: %s\n", __func__, msg)

radix_t radix_new(char c, radix_t brother) {
    
    radix_t radix; 
    radix = malloc(sizeof(*radix));

    if (radix == NULL) {
        ERR("Malloc failed");
        return NULL;
    }

    radix->value = c;
    radix->sons = NULL;

    radix->nb_of_parents = 1;

    //TO make compiler happy 
    if (brother == NULL) {
        radix->brothers = NULL;
    }
    else {
        radix->brothers = brother;
    }

    return radix;
}

int radix_add_word(radix_t radix, char* str) {

    if (radix == NULL) {
        ERR("Radix = NULL");
        return -1;
    }

    if (str == NULL) {
        ERR("Str = NULL");
        return -2;
    }
    
    if (*str == '\0' && radix->value == '\0') {
        return 1;
    }

    int rst;
    if ((int)(*str) < (int)(radix->value)) {

        radix->brothers = radix_new(radix->value, radix->brothers);
        radix->brothers->sons = radix->sons;
        radix->sons = NULL;
        if (radix->brothers == NULL) {
            ERR("In case, int)(*str) < (int)(radix->value), Radix_nex failed, radix->brother = NULL");
            return -7;
        }
        radix->value = *str;

        rst = radix_add_word(radix, str);
    }
    else if (*str == radix->value) {
        if (radix->sons == NULL) {
            char new_char = *(str + 1);
            radix->sons = radix_new(new_char, NULL);

            if (radix->sons == NULL) {
                ERR("In case, radix->value = *str, radix_new failed");
                return -4;
            }
        }
        rst = radix_add_word(radix->sons, str+1);
    }
    else {
        if (radix->brothers == NULL) {
            radix->brothers = radix_new(*str, NULL);
            if (radix->brothers == NULL) {
                ERR("Radix brother add new \0 failed");
                return -5;
            }

        }
        rst = radix_add_word(radix->brothers, str);
    }
    
    if (rst <= 0 || rst > 1) {
        ERR("radix_add_word failed, rst < 0");
        return -6;
    }

    return 1;
}

int radix_find(radix_t radix, char* str) {

    if (radix == NULL) {
        ERR("Radix = NULL");
        return -1;
    }
    if (str == NULL) {
        ERR("Str = NULL");
        return -2;
    }
    if (*str == '\0' && radix->value == '\0') {
        return 1;

    }
    if (*str == '\0' && radix->brothers == NULL) {
        return 0;
    }
    if ((int)(*str) < (int)(radix->value)) {
        return 0;
    }
    
    int rst;
    if (*str == radix->value) {
        if (radix->sons == NULL) {
            return 0;
        }
        rst = radix_find(radix->sons, str+1);
    }
    else {
        if (radix->brothers == NULL) {
            return 0;
        }
        rst = radix_find(radix->brothers, str);
    }
    
    if (rst < 0 || rst > 1) {
        ERR("radix_add_word failed, rst < 0");
        return -6;
    }
    if (rst) {
        return 1;
    }
    else {
        return 0;
    }
}

radix_t radix_delete(radix_t radix) {

    if (radix == NULL) {
        return NULL;
    }
    
    radix->sons = radix_delete(radix->sons);
    if (radix->sons != NULL) {
        ERR("Radix delete son failed");
        return radix;
    }
    radix->brothers = radix_delete(radix->brothers);
    if (radix->brothers != NULL) {
        ERR("Radix delete brother failed");
        return radix;
    }

    free(radix);
    radix = NULL;
    return NULL;
}

void radix_print(radix_t radix, size_t index) {
    
    if (radix == NULL) {
        return;
    }

    for (size_t j = 0; j < index; j++) {
        printf("| - ");
    }

    if (radix->value == '\0') {
        //printf("0, %p\n", radix);
        printf("0\n");


    }
    else {
        //printf("%c, %p\n", radix->value, radix);
        printf("%c\n", radix->value);

    }

    radix_print(radix->sons, index + 1);
    radix_print(radix->brothers, index);

    return;
}

//JUST A WRAPPER
void radix_print2(radix_t radix) {
    radix_print(radix, 0);
}