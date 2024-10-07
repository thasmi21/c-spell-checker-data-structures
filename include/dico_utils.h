#ifndef DICO_UTILS
#define DICO_UTILS

#include "../include/hash_table.h"
#include "../include/tree_trie.h"
#include "../include/tree_patricia.h"

// Function signatures for hash-based dictionary
hash_t hash_dico_controler(FILE*);
int hash_dico_find(char*, hash_t);
hash_t hash_dico_delete(hash_t);

// Function signatures for trie-based dictionary
trie_t tree_trie_controler(FILE*);
int tree_trie_find(char*, trie_t);
trie_t tree_trie_dico_delete(trie_t);

// Function signatures for Patricia-based dictionary
radix_t tree_patricia_controler(FILE*);
int tree_patricia_find(char*, radix_t);
radix_t tree_patricia_dico_delete(radix_t);

// Function signatures for compressed trie-based dictionary
trie_t trie_compressed_controler(FILE*);
int trie_compressed_find(char*, trie_t);
trie_t trie_compressed_dico_delete(trie_t);

// Function signatures for Patricia compressed dictionary
radix_t patrica_compressed_dico_new(FILE*);
int patrica_compressed_dico_find(char*, radix_t);
radix_t patricia_compressed_dico_delete(radix_t);

#endif
