#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../include/link.h"

link_t link_new(void) {
    return NULL;
}

int link_is_empty(link_t link) {
    return (link == NULL);
}

link_t link_add_first(link_t link, void* e) {

    if (e == NULL) {
        printf("Error in link.c/link_add_first: e == NULL\n");
        return NULL;
    }

    link_t new_link = malloc(sizeof(*link));
    if (new_link == NULL) {
        printf("Error in link.c/link_add_first: new_link is NULL malloc failed\n");
        return NULL;
    }

    if (link == NULL) {
        new_link->data = e;
        new_link->next = NULL;
        assert(new_link != NULL);
        return new_link;
    }

    new_link->data = e;
    new_link->next = link;
    assert(new_link != NULL);
    assert(link != NULL);
    return new_link;
}

link_t link_add_last(link_t link, void* e) {
    
    if (e == NULL) {
        printf("Error in link.c/link_add_last: e is NULL\n");
        return NULL;
    }

    if (link == NULL) {
        link = link_add_first(link, e);
        return link;
    }

    link_t p_link = link;
    while (p_link->next != NULL) {
        p_link = p_link->next;
    }

    assert(p_link != NULL);
    assert(p_link->next == NULL);
    p_link->next = link_add_first(p_link->next, e);
    if (p_link->next == NULL) {
        printf("Error in link.c/link_add_last: link_add_first failed\n");
        return NULL;
    }

    return link;
}

link_t link_del_first(link_t link , void* (*delete)(void*)) {

    if (link == NULL) {
        printf("Error in link.c/link_del_first: link is NULL\n");
        return NULL;
    }

    if (delete == NULL) {
        printf("Error in link.c/link_del_first: delete == NULL\n");
        return NULL;
    }

    link_t new_first = link->next;

    link->data = delete(link->data);
    assert(link->data == NULL);
    free(link);
    return new_first;
}

link_t link_del_last(link_t link , void* (*delete)(void*)) {

    if (link == NULL) {
        printf("Error in link.c/link_del_last: link is NULL\n");
        return NULL;
    }

    if (delete == NULL) {
        printf("Error in link.c/link_del_last: delete == NULL\n");
        return NULL;
    }

    if (link->next == NULL) {
        link->data = delete(link->data);
        assert(link->data == NULL);
        free(link);
        return NULL;
    }

    link_t p_link_last = link;
    link_t p_link_before_last = link;

    while (p_link_last->next != NULL) {
        p_link_before_last = p_link_last;
        p_link_last = p_link_last->next;
    }

    p_link_last->data = delete(p_link_last->data);
    assert(p_link_last->data == NULL);
    p_link_before_last->next = NULL;
    free(p_link_last);

    return link;
}

link_t link_delete_not_safe(link_t link, void* (*delete)(void*)) {

    assert(delete != NULL);

    if (link == NULL) {
        return NULL;
    }

    while(!link_is_empty(link)) {
        link = link_del_first(link , delete);
    }

    return NULL;
}

link_t link_delete(link_t link, void* (*delete)(void*)) {

    assert(delete != NULL);

    if (link == NULL) {
        return NULL;
    }

    while(!link_is_empty(link)) {

        void* p_data = (void*)link->data;
        link_t p_link = link->next;
        while (p_link != NULL) {
            if (p_link->data == p_data) {
                p_link->data = NULL;
            }
            p_link = p_link->next;

        }
        link = link_del_first(link , delete);

    }

    return NULL;
}
