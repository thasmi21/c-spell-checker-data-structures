#include <stdio.h>
#include <stdlib.h>

#include "../include/dico_utils.h"
#include "../include/add_find_dico.h"
#include "../include/key.h"
#include "../include/hash_table.h"

#define ERR(msg) fprintf(stderr, "Error: %s\n", msg)

//static int str_compare(char *s1, char* s2) {
//   return (strcmp(s1, s2) + 1);
//}

//static void print_str(char* s) {
//    printf("%s", s);
//}

//static size_t hash_string(char* str) {
//    unsigned long hash = 5381;
//    int c;
//
//    while ((c = *str++)) {
//        hash = ((hash << 5) + hash) + c;  // hash * 33 + c
//    }
//
//    return hash;
//}

//static char* delete_str(char* str) {
//
//    if (str == NULL) {
//        return NULL;
//    }
//    free(str);
// 
//    str = NULL;
//   return str;
//}

// Dummy hash table functions
hash_t hash_dico_controler(FILE* fp) {
    
    //hash_t h_tab = hash_new(100, (size_t (*)(void *))hash_string, (void *(*)(void *))delete_str, (void *(*)(void *))0x1,
    // (int (*)(void *, void *))str_compare, (int (*)(void *, void *))0x1, (void (*)(void *))print_str, (void (*)(void *))0x1);
    ////0X1 IS FOR USELLESS FUNCTION, BUT NULL IS INVALID (will not code them just for fun, the best code to debug is no code)

    //if (h_tab == NULL) {
    //    ERR("Hash_new failed");
    //    return NULL;
    //}

    //h_tab = add_dico_from_file(fp, (void*)h_tab, (void* (*)(char*, void*)));
    return NULL;  // Returning NULL as a placeholder
}

int hash_dico_find(char* key, hash_t dico) {
    printf("Called hash_dico_find (stub) with key: %s\n", key);
    return 0;  // Returning 0 to indicate "not found"
}

hash_t hash_dico_delete(hash_t dico) {
    printf("Called hash_dico_delete (stub)\n");
    return NULL;  // Returning NULL to indicate successful delete
}

// Dummy trie tree functions
trie_t tree_trie_controler(FILE* fp) {
    printf("Called tree_trie_controler (stub)\n");
    return NULL;  // Placeholder return
}

int tree_trie_find(char* key, trie_t dico) {
    printf("Called tree_trie_find (stub) with key: %s\n", key);
    return 0;  // Returning 0 to indicate "not found"
}

trie_t tree_trie_dico_delete(trie_t dico) {
    printf("Called tree_trie_dico_delete (stub)\n");
    return NULL;  // Returning NULL to indicate delete success
}

// Dummy radix (Patricia tree) functions
radix_t tree_patricia_controler(FILE* fp) {
    printf("Called tree_patricia_controler (stub)\n");
    return NULL;  // Placeholder return
}

int tree_patricia_find(char* key, radix_t dico) {
    printf("Called tree_patricia_find (stub) with key: %s\n", key);
    return 0;  // Returning 0 to indicate "not found"
}

radix_t tree_patricia_dico_delete(radix_t dico) {
    printf("Called tree_patricia_dico_delete (stub)\n");
    return NULL;  // Returning NULL to indicate delete success
}

// Dummy compressed trie functions
trie_t trie_compressed_controler(FILE* fp) {
    printf("Called trie_compressed_controler (stub)\n");
    return NULL;  // Placeholder return
}

int trie_compressed_find(char* key, trie_t dico) {
    printf("Called trie_compressed_find (stub) with key: %s\n", key);
    return 0;  // Returning 0 to indicate "not found"
}

trie_t trie_compressed_dico_delete(trie_t dico) {
    printf("Called trie_compressed_dico_delete (stub)\n");
    return NULL;  // Returning NULL to indicate delete success
}

// Dummy Patricia-compressed functions
radix_t patrica_compressed_dico_new(FILE* fp) {
    printf("Called patrica_compressed_dico_new (stub)\n");
    return NULL;  // Placeholder return
}

int patrica_compressed_dico_find(char* key, radix_t dico) {
    printf("Called patrica_compressed_dico_find (stub) with key: %s\n", key);
    return 0;  // Returning 0 to indicate "not found"
}

radix_t patricia_compressed_dico_delete(radix_t dico) {
    printf("Called patricia_compressed_dico_delete (stub)\n");
    return NULL;  // Returning NULL to indicate delete success
}
