#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <assert.h>

typedef struct _link {
  void* data;               /* un élément de la liste*/
  struct _link *next;       /* l'adresse du maillon suivant */
} *link_t;

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
// Retourne VRAI si l est un maillon vide
int link_is_empty(link_t link);

// Retourne l'élément en tête de liste : PRECONDITION : liste non vide
void* list_first(list_t list);

// Ajoute l'élément e en tête des maillons et retourne cette tete
// Retourne NULL, ne modifie pas la liste en cas d'erreur
link_t link_add_first(void* e, link_t link);
// Ajoute l'élément e en tête de liste et retourne cette liste
list_t list_add_first(void* e, list_t list);

// Supprime le maillon en tête des maillons et retourne les maillons
// PRECONDITION : maillons non vide
link_t link_del_first(link_t link , void* (*delete)(void*));
// Supprime le maillon en tête de liste et retourne la nouvelle liste
// PRECONDITION : liste non vide
list_t list_del_first(list_t list);

// Retourne le nombre d'éléments (ou de maillons) de la liste
size_t list_length(list_t list);

// Affiche la liste a l'ecran, dans un fichier.
void list_fprintf(list_t list, FILE* fp);
void list_printf(list_t list);

// Libère toute la liste et retourne une liste vide
// Libere les elements avec delete_data si la fonction existe
list_t list_delete(list_t list);

// Ajoute en queue de liste, eventuellement
list_t list_add_last(void* e, list_t list);
link_t link_add_last(void* e, link_t list);
//Suppression en queue, eventuellement
list_t list_del_last(list_t list);
link_t link_del_last(link_t list, void* (*delete)(void*));

// Recherche un element selon le critere compare. Retourne le maillon trouve ou NULL
link_t list_lookup(void* elem, list_t list, int(*compare)(void* e1, void* e2));
// Recherche le premier maillon contenant e,
// au sens du equal_data ou de l'egalite de pointeurs si equal_data est NULL
// ou NULL si e n'est pas dans la liste       
link_t list_find(void* e, list_t list);

// Suppression de l'element param, au sens de equal_data
list_t list_remove(void* param, list_t list);

// Les visiteurs
void list_simple_visit(list_t list, void (*)(void*,void*), void* param);
void list_visit(list_t list, int (*exec_on_value)(void*,void*), int (*exec_on_link)(list_t,void*),void* param);

#endif