#include <stdio.h>
#include <stdlib.h>

#include "list.h"

list_t list_new(void (*print_data)(void*),void* (*delete_data)(void*), int (*equal_data)(void*,void*)) {

    if (print_data == NULL) {
        printf("Error in list.c/listle_new: print_data must not be NULL\n");
        return NULL;
    }

    if (delete_data == NULL) {
        printf("Error in list.c/listle_new: delete_data must not be NULL\n");
        return NULL;
    }

    if (equal_data == NULL) {
        printf("Error in list.c/listle_new: equal_data must not be NULL\n");
        return NULL;
    }

    list_t list = calloc(1, sizeof(*list));

    if (list == NULL) {
        printf("Error in list.c/listle_new: list is NULL malloc failed\n");
        return NULL;
    }
    
    list->size = 0;
    list->print_data = print_data;
    list->delete_data = delete_data;
    list->equal_data = equal_data;

    return list;
}

int list_is_empty(list_t list) {

    if (list == NULL) {
        printf("Error in list.c/listle_is_empty: list is NULL\n");
        return -1;
    }

    if (list->data == NULL && list->size != 0) {
        printf("Error in list.c/list_is_empty: data is NULL and list size != 0\n");
        return -2;
    }

    if (list->data != NULL && list->size == 0) {
        printf("Error in list.c/list_is_empty: data is not NULL and list size = 0\n");
        return -3;
    }

    if (list->data == NULL) {
        return 1;
    }
    else {
        return 0;
    }
}

int link_is_empty(link_t link) {

    return (link == NULL);
}

//to remake !!!
void* list_first(list_t list) {

    if (list == NULL) {
        printf("Error in list.c/list_first: list is NULL\n");
        return NULL;
    }

    if (list->data == NULL && list->size > 0) {
        printf("Error in list.c/list_first: list->data is NULL && size > 0\n");
        return NULL;
    }

    if (list->data == NULL && list->size == 0) {
        printf("Nothing to print\n");
    }

    printf("\tdata[0] = ");
    list->print_data(list->data);
    printf("\n");
    return NULL;
}

link_t link_add_first(void* e, link_t link) {

    if (link == NULL) {
        printf("Error in list.c/link_add_first: link is NULL\n");
        return NULL;
    }

    if (e == NULL) {
        printf("Error in list.c/link_add_first: e == NULL\n");
        return NULL;
    }

    link_t new_link = malloc(sizeof(*link));

    new_link->data = e;
    new_link->next = link;

    return new_link;
}

list_t list_add_first(void* e, list_t list) {

    if (list == NULL) {
        printf("Error in list.c/list_add_first: link is NULL\n");
        return NULL;
    }

    if (e == NULL) {
        printf("Error in list.c/list_add_first: e == NULL\n");
        return NULL;
    }

    list->data = link_add_first(e, list->data);
    return list;
}

link_t link_del_first(link_t link , void* (*delete)(void*)) {

    if (link == NULL) {
        printf("Error in list.c/link_del_first: link is NULL\n");
        return NULL;
    }

    if (delete == NULL) {
        printf("Error in list.c/link_del_first: delete == NULL\n");
        return NULL;
    }

    link_t new_first = link->next;

    link = delete(link);
    assert(link == NULL);
    return new_first;
}

list_t list_del_first(list_t list) {

    int rst = list_is_empty(list);
    if (rst < 0) {
        printf("Error in list.c/list_del_first: rst < 0\n");
        return NULL;
    }

    if (rst == 1) {
        printf("Error in list.c/list_del_first: list is empty\n");
        return NULL;
    }

    assert(list->data != NULL);
    
    list->data = link_del_first(list->data , list->delete_data);
    (list->size)--;
    return list;
}

size_t list_length(list_t list) {

    if (list == NULL) {
        printf("Error in list.c/list_length: list is NULL\n");
        exit(EXIT_FAILURE);
    }

    if (list->data != NULL && list->size == 0) {
        printf("Error in list.c/list_length: list is not NULL and size = 0\n");
        exit(EXIT_FAILURE);
    }

    if (list->data == NULL && list->size != 0) {
        printf("Error in list.c/list_length: list is NULL and size != 0\n");
        exit(EXIT_FAILURE);

    }

    return list->size;
}

void list_fprintf(list_t list, FILE* fp) {

    if (list == NULL) {
        printf("Error in list.c/list_length: list is NULL\n");
        exit(EXIT_FAILURE);
    }

    if (list->data != NULL && list->size == 0) {
        printf("Error in list.c/list_length: list is not NULL and size = 0\n");
        exit(EXIT_FAILURE);
    }

    if (list->data == NULL && list->size != 0) {
        printf("Error in list.c/list_length: list is NULL and size != 0\n");
        exit(EXIT_FAILURE);

    }

    printf("\nlist is of size %zu {\t", list->size);
    size_t size = list->size;
    link_t data = list->data;
    for (size_t i = 0; i < size; i++) {
        list->print_data(data);
        data = data->next;
        printf("\t");
    } 
    printf("}\n");
}
