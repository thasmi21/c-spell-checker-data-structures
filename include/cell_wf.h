#ifndef CELL_WF_T
#define CELL_WF_T

#include "cell.h"

typedef struct {

    void (*print_data)(void*);
    void (*print_key)(void*);
    void* (*delete_data)(void*);
    void*(*delete_key)(void*);
    int(*compare_data)(void*, void*);
    int (*compare_key)(void*, void*);
    cell_t cell;

} * cell_wf_t;

cell_wf_t cell_wf_new(void* key, void* data, size_t hashcode, void (*print_data)(void*),
    void (*print_key)(void*), void* (*delete_data)(void*),void*(*delete_key)(void*),
    int(*compare_data)(void*, void*), int (*compare_key)(void*, void*));

cell_wf_t cell_wf_new2(cell_t cell, void (*print_data)(void*),
    void (*print_key)(void*), void* (*delete_data)(void*),void*(*delete_key)(void*),
    int(*compare_data)(void*, void*), int (*compare_key)(void*, void*));

void cell_wf_print(cell_wf_t cell_wf);

cell_wf_t cell_wf_delete(cell_wf_t cell_wf);

//The 3rd one is only there to have 3 params has other want it
int cell_wf_compare(cell_wf_t cell_wf1, cell_wf_t cell_wf2, int (*unused)(void*, void*));

int cell_wf_compare_key(cell_wf_t cell_wf1, cell_wf_t cell_wf2, int (*unused)(void*, void*));

#endif