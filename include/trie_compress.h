#ifndef TRIE_COMPRESS
#define TRIE_COMPRESS

#include "tree_trie.h"
#include "vector.h"
#include "hash_table.h"

int add_v_key_chars_trie(trie_t trie, vect_t v_key);

trie_t trie_compress(trie_t trie, hash_t h_tab);

trie_t trie_compressor(trie_t trie);

trie_t trie_compressed_delete(trie_t trie);


#endif