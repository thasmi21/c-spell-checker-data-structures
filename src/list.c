#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "list.h"
#include "link.h"

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

    if (list->data == NULL) {
        printf("No fist\n");
        return NULL;
    }

    return list->data->data;
}

list_t list_add_first(list_t list, void* e) {

    if (list == NULL) {
        printf("Error in list.c/list_add_first: link is NULL\n");
        return NULL;
    }

    if (e == NULL) {
        printf("Error in list.c/list_add_first: e == NULL\n");
        list_delete(list);
        return NULL;
    }

    list->data = link_add_first(list->data, e);

    if (list->data == NULL) {
        printf("Error in list.c/list_add_first: link_add_first failed\n");
        list_delete(list);
        return NULL;
    }

    list->size++;
    return list;
}

list_t list_del_first(list_t list) {

    if (list == NULL) {
        printf("Error in list.c/list_del_first: list is NULL\n");
        return NULL;
    }

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

int list_length(list_t list) {

    if (list == NULL) {
        printf("Error in list.c/list_length: list is NULL\n");
        return -1;
    }

    if (list->data != NULL && list->size == 0) {
        printf("Error in list.c/list_length: list is not NULL and size = 0\n");
        return -2;
    }

    if (list->data == NULL && list->size != 0) {
        printf("Error in list.c/list_length: list is NULL and size != 0\n");
        return -3;
    }

    return list->size;
}

void list_printf(list_t list) {

    if (list == NULL) {
        printf("Error in list.c/list_printf: list is NULL\n");
        exit(EXIT_FAILURE);
    }

    if (list->data != NULL && list->size == 0) {
        printf("Error in list.c/list_printf: list is not NULL and size = 0\n");
        exit(EXIT_FAILURE);
    }

    if (list->data == NULL && list->size != 0) {
        printf("Error in list.c/list_printf: list is NULL and size != 0\n");
        exit(EXIT_FAILURE);

    }

    printf("\nlist is of size %zu {\t", list->size);
    link_t p_link = list->data;
    
    while (!link_is_empty(p_link)) {
        list->print_data(p_link->data);
        p_link = p_link->next;
        printf(",\t");
    } 
    printf("}\n");
}

list_t list_delete(list_t list) {

    if (list == NULL) {
        return NULL;
    }

    if (list->data != NULL && list->size == 0) {
        printf("Error in list.c/list_delete: list is not NULL and size = 0\n");
        exit(EXIT_FAILURE);
    }

    if (list->data == NULL && list->size != 0) {
        printf("Error in list.c/list_delete: list is NULL and size != 0\n");
        exit(EXIT_FAILURE);
    }

    list->data = link_delete(list->data, list->delete_data);
    assert(list->data == NULL);

    free(list);
    return NULL;
}

list_t list_add_last(list_t list, void* e) {

    if (list == NULL) {
        printf("Error in list.c/list_add_last: list is NULL\n");
        return NULL;
    }

    if (e == NULL) {
        printf("Error in list.c/list_add_last: e is NULL\n");
        list_delete(list);
        return NULL;
    }

    list->data = link_add_last(list->data, e);

    if (list->data == NULL) {
        printf("Error in list.c/list_add_last: link_add_last failed\n");
        list_delete(list);
        return NULL;
    }

    list->size++;

    return list;
}

list_t list_del_last(list_t list) {

    if (list == NULL) {
        printf("Error in list.c/list_del_last: list is NULL\n");
        return NULL;
    }

    if (list->data != NULL && list->size == 0) {
        printf("Error in list.c/list_del_last: list is not NULL and size = 0\n");
        return NULL;
    }

    if (list->data == NULL && list->size != 0) {
        printf("Error in list.c/list_del_last: list is NULL and size != 0\n");
        return NULL;
    }

    list->data = link_del_last(list->data , list->delete_data);

    list->size--;
    return list;
}

link_t list_lookup(list_t list, void* elem, int(*compare)(void* e1, void* e2)) {

    if (elem == NULL) {
        printf("Error in list.c/list_lookup: elem is NULL\n");
        return NULL;
    }

    if (list == NULL) {
        printf("Error in list.c/list_lookup: list is NULL\n");
        return NULL;
    }

    if (list->data == NULL) {
        return NULL;
    }

    link_t p_data = list->data;
    
    while (!link_is_empty(p_data)) {
        
        int rst = compare(p_data->data, elem);

        if (rst == 1) {
            return p_data;
        }
        
        if (rst < 0) {
            printf("Error in list.c/list_lookup: compare rst is NULL\n");
            return NULL;
        }
        p_data = p_data->next;
    }

    return NULL;
}

link_t list_find(list_t list, void* elem) {

    if (elem == NULL) {
        printf("Error in list.c/list_lookup: elem is NULL\n");
        return NULL;
    }

    if (list == NULL) {
        printf("Error in list.c/list_lookup: list is NULL\n");
        return NULL;
    }

    if (list->data == NULL) {
        return NULL;
    }

    link_t p_data = list->data;
    
    while (!link_is_empty(p_data)) {
        
        int rst = list->equal_data(p_data->data, elem);

        if (rst == 1) {
            return p_data;
        }
        
        if (rst < 0) {
            printf("Error in list.c/list_lookup: compare rst is NULL\n");
            return NULL;
        }
        p_data = p_data->next;
    }

    return NULL;
}

list_t list_remove(list_t list, void* elem) {

    if (elem == NULL) {
        printf("Error in list.c/list_lookup: elem is NULL\n");
        return NULL;
    }

    if (list == NULL) {
        printf("Error in list.c/list_lookup: list is NULL\n");
        return NULL;
    }

    if (list->data == NULL) {
        return NULL;
    }
    
    link_t link = list_find(list, elem);

    if (link == NULL) {
        printf("Error in list.c/list_lookup: Element not found or list_find failed\n");
        return NULL;
    }

    link = link_del_first(link , list->delete_data);
    list->size--;
    return list;
}