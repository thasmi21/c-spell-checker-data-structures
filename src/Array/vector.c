#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "vector.h"
#include "generic_table.h"

#define ERR(msg) fprintf(stderr, "Error in vector.c: %s\n", msg)

vect_t vect_new(size_t n,void (*print_data)(void*), void* (*delete_data)(void*),int (*equal_data)(void*,void*)) {

    vect_t vec;
    vec = (vect_t)table_new(n, print_data, delete_data, equal_data);
    
    if (vec == NULL) {
        printf("Error in vector.c/vect_new: Memory allocation of vec_new failed\n");
        return NULL;
    }

    return vec;
}

int vect_append(void* element, vect_t vec) {

    if (vec == NULL) {
        printf("Error in vector.c/vect_append: Vec is NULL\n");
        return -1;
    }

    if (vec->data == NULL) {
        printf("Error in generic.c/vec_append: vec->data is NULL malloc failed\n");
        free(vec);
        return -2;
    }

    if (vec->actual_size == vec->max_size) {
        vec->data = realloc(vec->data,  2 * (vec->max_size) * sizeof(element));

        for (size_t i = vec->max_size; i <  2 * (vec->max_size); i++) {
            (vec->data)[i] = NULL;
        }
        if (vec->data == NULL) {
            return -10;
        }
        vec->max_size = 2 * (vec->max_size);
    }

    int rst = table_append(element, (table_t)vec);
    return rst;
}

void vect_printf(vect_t vec) {
    table_printf((table_t)vec);
}

vect_t vect_delete(vect_t vec) {
    ERR("lol");
    vec = table_delete((table_t)vec);
    assert(vec == NULL);
    return vec;
}

int vect_find(void* element, vect_t vec) {

    assert(element != NULL);
    assert(vec != NULL);
    assert(vec->data != NULL);
    assert(vec->equal_data != NULL);

    size_t max_size = vec->max_size;
    for (size_t i = 0; i<max_size; i++) {
        void* p_i = (vec->data)[i];
        if (p_i != NULL) {
            int rst = vec->equal_data(element, p_i);

            if (rst < 0) {
                printf("Error in generic.c/vect_find: vec->equal_data failed\n");
                return -2;
            }
            if (rst == 1) {
                return i;
            }
        }
    }
    return -1;
}

int vect_lookup(void* element, vect_t vec, int (*equality_test)(void*,void*)) {

    assert(element != NULL);
    assert(vec != NULL);
    assert(vec->data != NULL);
    assert(equality_test != NULL);
    
    for (size_t i = 0; i<vec->actual_size; i++) {

        void* p_i = (vec->data)[i];
        assert(p_i != NULL);
        if (equality_test(element, p_i)) {
            return i;
        }
    }
    return -1;
}

int vect_remove_at(size_t index, vect_t vec) {

    int rst = table_remove_at(index, (table_t)vec);

    if (rst < 0) return rst;

    if (vec->actual_size < (vec->max_size) / 3) {

        size_t size_element = sizeof( (vec->data)[0] );
        vec->data = realloc(vec->data, (vec->max_size) / 2 * size_element);
        vec->max_size = (vec->max_size) / 2;
    }
    return rst;
}

int vect_is_equal(vect_t tab1, vect_t tab2) {
    return table_is_equal((table_t)tab1, (table_t)tab2);
}