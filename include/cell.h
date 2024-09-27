#ifndef CELL_T
#define CELL_T

#include <stdio.h>

typedef struct {

  void* key;
  void* data;
  size_t hashcode;

} * cell_t;

cell_t cell_new(void* key, void* data, size_t hashcode);

void cell_print(cell_t cell, void (*print_data)(void*), void (*print_key)(void*));

cell_t cell_delete(cell_t cell, void* (*delete_data)(void*), void*(*delete_key)(void*));

int cell_compare(cell_t cell1, cell_t cell2, int(*compare_data)(void*, void*), int (*compare_key)(void*, void*));

int cell_compare_key(cell_t cell1, cell_t cell2, int (*compare_key)(void*, void*));

#endif