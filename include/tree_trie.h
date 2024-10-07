#ifndef TREE_TRIE
#define TREE_TRIE

#define ASIZE 27 //THE 27 is reserved for \0

typedef struct _node {
    size_t nb_of_parents;
    struct _node *sons[ASIZE]; 
} *trie_t;

trie_t trie_new();

int trie_add_word(trie_t trie, char* str);

int trie_find_word(trie_t trie, char* str);

trie_t trie_delete(trie_t trie);

void trie_print(trie_t trie, size_t index);

//Just a wrapper
void trie_print2(trie_t trie);

void trie_print_test2(trie_t trie);

#endif


//ONLY TAKES AS INPUT abc..yz