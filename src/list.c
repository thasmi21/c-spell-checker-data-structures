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
    list->data = NULL;

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
        list = list_delete(list);
        assert(list == NULL);
        return list;
    }

    list->data = link_add_first(list->data, e);

    if (list->data == NULL) {
        printf("Error in list.c/list_add_first: link_add_first failed\n");
        list = list_delete(list);
        assert(list == NULL);
        return list;
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

    printf("List, list->size = %zu list->data = [", list->size);
    link_t p_link = list->data;
    
    while (!link_is_empty(p_link)) {
        list->print_data(p_link->data);
        p_link = p_link->next;
        printf(",\t");
    } 
    printf("]");
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
        list = list_delete(list);
        assert(list == NULL);
        return list;
    }

    if (e == NULL) {
        printf("Error in list.c/list_add_last: e is NULL\n");
        list = list_delete(list);
        assert(list == NULL);
        return list;
    }

    list->data = link_add_last(list->data, e);

    if (list->data == NULL) {
        printf("Error in list.c/list_add_last: link_add_last failed\n");
        list = list_delete(list);
        assert(list == NULL);
        return list;
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

    if (compare == NULL) {
        printf("Error in list.c/list_lookup: compare is NULL\n");
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
        printf("Error in list.c/list_find: elem is NULL\n");
        return NULL;
    }

    if (list == NULL) {
        printf("Error in list.c/list_find: list is NULL\n");
        return NULL;
    }

    if (list->data == NULL) {
        return NULL;
    }

    link_t p_link = list->data;

    if (list->equal_data == NULL) {
        printf("Error in list.c/list_find: list->equal_data == NULL\n");
        return NULL;
    }

    while (!link_is_empty(p_link)) {

        if (p_link->data == NULL || elem == NULL || list->equal_data == NULL) {
        }
        int rst = list->equal_data(p_link->data, elem);
        if (rst == 1) {
            return p_link;
        }
        
        if (rst < 0) {
            printf("Error in list.c/list_find: compare rst <0\n");
            return NULL;
        }
        p_link = p_link->next;
    }

    return NULL;
}

list_t list_remove(list_t list, void* elem) {

    if (elem == NULL) {
        printf("Error in list.c/list_remove: elem is NULL\n");
        return NULL;
    }

    if (list == NULL) {
        printf("Error in list.c/list_remove: list is NULL\n");
        return NULL;
    }

    if (list->data == NULL) {
        return NULL;
    }
    
    link_t link = list_find(list, elem);

    if (link == NULL) {
        printf("Error in list.c/list_remove: Element not found or list_find failed\n");
        return NULL;
    }

    link = link_del_first(link , list->delete_data);
    list->size--;
    return list;
}

list_t list_link_remove(list_t list, link_t link) {

    if (link == NULL) {
        printf("Error in list.c/list_link_remove: link is NULL\n");
        return list;
    }

    if (list == NULL) {
        printf("Error in list.c/list_link_remove: list is NULL\n");
        return NULL;
    }

    if (list->data == NULL) {
        printf("Void list\n");
        return NULL;
    }


    link = list_find(list, link->data);

    if (link == NULL) {
        printf("Error in list.c/list_link_remove: Element not found or list_find failed\n");
        return list;
    }

    if (list->delete_data == NULL) {
        printf("Error in list.c/list_link_remove: list->delete_data = NULL\n");
        return list;
    }

    link_t p_link = list->data;
    if (p_link == link) {
        list->data = link_del_first(list->data , list->delete_data);

        list->size--;
        return list;
    }
    
    link_t link_preview = NULL;
    while (p_link->next != NULL && link_preview == NULL) {

        if (p_link->next == link) {
            link_preview = p_link;
        }
        assert(p_link->next != NULL);
        p_link->next = p_link;
    }
    
    p_link->next = link_del_first(p_link->next , list->delete_data);
    list->size--;
    return list;
}

int list_is_equal(list_t list1, list_t list2) {


    if (list1 == NULL) {
        printf("Error in list.c/list_is_equal: list1 = NULL\n");
        return -1;
    }

    if (list2 == NULL) {
        printf("Error in list.c/list_is_equal: list2 = NULL\n");
        return -2;
    }

    if (list1->size != list2->size) {
        return 0;
    }

    link_t p_link1 = list1->data;
    link_t p_link2 = list2->data;

    if (p_link1 == NULL && p_link2 == NULL) {
        return 1;
    }

    if (list1->equal_data == NULL) {
        printf("Error in list.c/list_is_equal: list1->equal_data = NULL\n");
        return -3;
    }
    while(p_link1 != NULL) {

        if (p_link2 == NULL) {
            printf("Error in list.c/list_is_equal: list1 and list2 are not same size while list->size is equal, MAJOR BUG\n");
            return -3;
        }
        int rst = list1->equal_data(p_link1, p_link2);

        if (rst < 0) {
            printf("Error in list.c/list_is_equal: rst < 0 list1->equal_data failed\n");
            return -3;
        }

        int valid_rst = (rst == 1 || rst == 0);
        if (!valid_rst) {
            printf("Error in list.c/list_is_equal: rst > 1, MAJOR BUG\n");
        }

        if (rst == 0) {
            return 0;
        }
    }
    
    return 1;
}