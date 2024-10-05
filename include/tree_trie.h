#ifndef TREE_TRIE
#define TREE_TRIE

#define ASIZE 27 //THE 27 is reserved for \0

typedef struct _node {
    size_t nb_of_parents;
    struct _node *sons[ASIZE]; 
} *tree_t;

tree_t tree_new();

int tree_add_word(tree_t tree, char* str);

int tree_find_word(tree_t tree, char* str);

tree_t tree_delete(tree_t tree);

void tree_print(tree_t tree, size_t index);
#endif

//ONLY TAKES AS INPUT abc..yz