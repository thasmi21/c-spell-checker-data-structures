#ifndef HASH_TABLE
#define HASH_TABLE
// Inclusion des listes génériques
#include "../include/vector.h"
///////// Les maillons des listes génériques contiennent des pointeurs vers des triplets clés, valeurs, hashcode.
///////// Le hashcode n'est utile que pour l'optimisation du redimensionnement
typedef struct {

  void* key;
  void* data;
  size_t hashcode;

} * cell_t;

///////// Le type des tables d'association
typedef struct {
  size_t total_number;
  size_t size;

  int (*hachage)(void *);

  vect_t data;

  void* (*delete_key)(void*);
  void* (*delete_data)(void*);
  int (*compare_key)(void* e1, void* e2);
  void (*print_key)(void*,FILE*);
  void (*print_data)(void*,FILE*);

}* hash_t;

hash_t hash_new(size_t n, int (*hachage)(void * ),
  void* (*delete_key)(void*),void* (*delete_data)(void*),
  int (*compare_key)(void* e1, void* e2),
  void (*print_key)(void*,FILE*),void (*print_data)(void*,FILE*));

hash_t hash_delete(hash_t table);

int hash_put(void* key, void* data, hash_t table) ;

void* hash_get_value(void* key, hash_t table) ;

void hash_remove_key(void* key, hash_t table) ;

void hash_fprintf(hash_t table,FILE*fp) ;

void hash_printf(hash_t table) ;
// Optionel, si Redimensionnement
// sens =1 pour accroitre la table, -1 sinon
int hash_new_length(int sens, hash_t table);

#endif