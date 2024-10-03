#ifndef HASH_T
#define HASH_T
// Inclusion des listes génériques
#include "vector.h"
#include "cell_wf.h"

///////// Les maillons des listes génériques contiennent des pointeurs vers des triplets clés, valeurs, hashcode.
///////// Le hashcode n'est utile que pour l'optimisation du redimensionnement

///////// Le type des tables d'association
typedef struct {
  size_t total_number;
  size_t size;

  size_t (*hachage)(void *);

  vect_t data;

  void* (*delete_key)(void*);
  void* (*delete_data)(void*);
  int (*compare_key)(void* e1, void* e2);
  int (*compare_data)(void* e1, void* e2);
  void (*print_key)(void*);
  void (*print_data)(void*);

}* hash_t;

hash_t hash_new(size_t n, size_t (*hachage)(void * ),
    void* (*delete_key)(void*),void* (*delete_data)(void*),
        int (*compare_key)(void* e1, void* e2), int (*compare_data)(void* e1, void* e2),
    void (*print_key)(void*),void (*print_data)(void*));

hash_t hash_delete(hash_t table);

int hash_put(void* key, void* data, hash_t table) ;

cell_t hash_get_value(void* key, hash_t table) ;

int hash_remove_key(void* key, hash_t table) ;

void hash_print(hash_t table) ;

// Optionel, si Redimensionnement
// sens =1 pour accroitre la table, -1 sinon
int hash_new_length(int sens, hash_t table);

//TO test, return table->size as errors because it is an impossible value
size_t hash_indice(void* key, hash_t table);


cell_wf_t cell_wrapper(void* key, void* data, hash_t table);

#endif