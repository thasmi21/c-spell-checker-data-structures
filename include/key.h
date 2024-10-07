#ifndef KEY_H
#define KEY_H

#include "vector.h"

vect_t v_key_new();

int make_add_char(char c, vect_t v_key);

char* make_char_key(vect_t v_key);

char* make_key(void* tree, int(*make_v_key)(void*, vect_t));

char* char_make(char c);

hash_t hash_tree_new(size_t n, void(*print_tree)(void*));

int tree_add_in_hash(void* tree, hash_t h_tab, int(*make_v_key)(void*, vect_t));

void* tree_in_hash_find(void* tree, hash_t h_tab, int (*add_v_key_chars)(void *, vect_t));

void* tree_compressor(void* tree, void* (*tree_compress)(void*, hash_t), void(*tree_print)(void*));

#endif