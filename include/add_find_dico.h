#ifndef ADD_FIND_DICO
#define ADD_FIND_DICO

#include <stdio.h>

void* add_dico_from_file(FILE* fp, void* dico, void* (*dico_add)(char*, void*), int max);

int find_str_in_dico(const char* str, void* dico, int (*dico_find)(const char*, void*));
#endif