#ifndef PATRICA_COMPRESS
#define PATRICA_COMPRESS

#include "vector.h"
#include "hash_table.h"
#include "tree_patricia.h"

//vect_t v_key_new();

//int make_add_char(char c, vect_t v_key);

int add_v_key_char(radix_t radix, vect_t v_key);

//char* make_char_key(vect_t v_key);

char* make_key_radix(radix_t radix);

int radix_add_in_hash(radix_t radix, hash_t h_tab);

radix_t radix_in_hash_find(radix_t radix, hash_t h_tab);

radix_t patricia_compressed_delete(radix_t radix);

radix_t patricia_compress(radix_t radix, hash_t h_tab);

radix_t patricia_compressor(radix_t radix);

hash_t hash_patricia_new(size_t n);
#endif