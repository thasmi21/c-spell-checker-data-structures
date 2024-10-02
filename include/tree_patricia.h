#ifndef TREE_TRIE
#define TREE_TRIE

typedef struct node_radix {
    char value;
    struct node_radix *sons;
    struct node_radix *brothers;
}  *radix_t;

radix_t radix_new(char c, radix_t brother);

int radix_add_word(radix_t radix, char* str);

int radix_find(radix_t radix, char* str);

radix_t radix_delete(radix_t radix);

void radix_print(radix_t radix, size_t index);
#endif
