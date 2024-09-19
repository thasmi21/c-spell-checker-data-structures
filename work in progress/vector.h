#ifndef VECT_H
#define VECT_H

#include <stdio.h>
#include "generic_tab.h"

typedef table_t vect_t;

vect_t vect_new(size_t n,void (*print_data)(void*,FILE*), void* (*delete_data)(void*),int (*equal_data)(void*,void*));

vect_t vect_append(void* e, vect_t table);

void vect_printf(vect_t table);

vect_t vect_delete(vect_t table);

int vect_find(void* param, vect_t l);

int vect_lookup(void* param, vect_t l, int (*)(void*,void*));

vect_t vect_remove_at(int i, vect_t table);

#endif