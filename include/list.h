#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include "link.h"

typedef struct _list{
  link_t data;
  size_t size;

  void* (*delete_data)(void*);
  void (*print_data)(void*);
  int (*equal_data)(void*,void*);
} * list_t;

// Creation d'une liste vide, avec les pointeurs de fonctions utiles
list_t list_new(void (*print_data)(void*),void* (*delete_data)(void*),
          int (*equal_data)(void*,void*)) ;

// Retourne VRAI si l est une liste vide
int list_is_empty(list_t list);

// Retourne l'élément en tête de liste : PRECONDITION : liste non vide
void* list_first(list_t list);

// Ajoute l'élément e en tête des maillons et retourne cette tete
// Retourne 1 si bon ou <0 si erreur, ne modifie pas la liste en cas d'erreur
// Ajoute l'élément e en tête de liste et retourne cette liste
list_t list_add_first(list_t list, void* e);

// Supprime le maillon en tête de liste et retourne la nouvelle liste
// PRECONDITION : liste non vide
list_t list_del_first(list_t list);

// Retourne le nombre d'éléments (ou de maillons) de la liste
int list_length(list_t list);

// Affiche la liste a l'ecran.
void list_printf(list_t list);

// Libère toute la liste et retourne une liste vide
// Libere les elements avec delete_data si la fonction existe
list_t list_delete(list_t list);

// Ajoute en queue de liste, eventuellement
list_t list_add_last(list_t list, void* e);

//Suppression en queue, eventuellement
list_t list_del_last(list_t list);

// Recherche un element selon le critere compare. Retourne le maillon trouve ou NULL
link_t list_lookup(list_t list, void* elem, int(*compare)(void* e1, void* e2));
// Recherche le premier maillon contenant e,
// au sens du equal_data ou de l'egalite de pointeurs si equal_data est NULL
// ou NULL si elem n'est pas dans la liste       
link_t list_find(list_t list, void* elem);

// Suppression de l'element elem, au sens de equal_data
list_t list_remove(list_t list, void* elem);

list_t list_link_remove(list_t list, link_t link);

//To test
int list_is_equal(list_t list1, list_t list2);

list_t list_fusion(list_t list_dst, list_t list_src);
#endif