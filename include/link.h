#ifndef LINK_H
#define LINK_H

#include <stdio.h>

typedef struct _link {
  void* data;               /* un élément de la liste*/
  struct _link *next;       /* l'adresse du maillon suivant */
} *link_t;

link_t link_new(void);

int link_is_empty(link_t link);

link_t link_add_first(link_t link, void* e);

link_t link_add_last(link_t link, void* e);

//To test
link_t link_fusion(link_t link_dst, link_t link_src);

link_t link_del_first(link_t link , void* (*delete)(void*));

link_t link_del_last(link_t list, void* (*delete)(void*));

link_t link_delete(link_t link, void* (*delete)(void*));

#endif