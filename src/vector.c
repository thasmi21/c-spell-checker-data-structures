#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "../include/vector.h"
#include "../include/generic_table.h"

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
    vec = table_delete((table_t)vec);
    assert(vec == NULL);
    return vec;
}

int vect_find(void* element, vect_t vec) {

    assert(element != NULL);
    assert(vec != NULL);
    assert(vec->data != NULL);
    assert(vec->equal_data != NULL);
    for (size_t i = 0; i<vec->actual_size; i++) {

        void* p_i = (vec->data)[i];
        assert(p_i != NULL);
        if (vec->equal_data(element, p_i)) {
            return i;
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