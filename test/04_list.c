#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "../include/list.h"
#include "../include/link.h"

void print_char(char* c) {
    printf("%c", *c);
}

char* delete_char(char* c) {

    assert(c != NULL);
    free(c);
 
    c = NULL;
    return c;
}

int equal_char(char* c1, char* c2) {

    assert(c1 != NULL && c2 != NULL);
    return (*c1 == *c2);
}

//Test if ascci value are same parity
int equal_char2(char* c1, char* c2) {

    assert(c1 != NULL && c2 != NULL);

    int i1 = (*c1 - 0x61)%2;
    int i2 = (*c2 - 0x61)%2;
    return (i1 == i2);
}

char* create_char(char value) {

    char* p_chr = malloc(sizeof(char));
    assert(p_chr != NULL && "Error in 04_list.c/create_char: malloc failed and returned NULL\n");
    *p_chr = value;
    return p_chr;
}

list_t list_crea_list() {

    list_t list = list_new((void (*)(void *))print_char, 
    (void (*))delete_char, 
    (int (*)(void *, void *))equal_char);
    assert(list != NULL);
    
    char* a = create_char('a');
    assert(a != NULL);
    char* b = create_char('b');
    assert(b != NULL);

    list = list_add_first(list, b);
    assert(list != NULL);
    list = list_add_first(list, a);
    assert(list != NULL);

    return list; 
}

int test_list_new() {

    fprintf(stderr, "\n## Test of the list_new function\n");

    fprintf(stderr, "<= Test : We try to create a invalid new list and test its parameters\n");

    list_t list = NULL;
    list = list_new((void (*)(void *))NULL, 
    (void (*))delete_char, 
    (int (*)(void *, void *))equal_char);
    assert(list == NULL);

    list = list_new((void (*)(void *))print_char, 
    (void (*))NULL, 
    (int (*)(void *, void *))equal_char);
    assert(list == NULL);

    list = list_new((void (*)(void *))print_char, 
    (void (*))delete_char, 
    (int (*)(void *, void *))NULL);
    assert(list == NULL);

    fprintf(stderr, "=> Test passed with success\n");

    fprintf(stderr, "<= Test : We try to create a valid new list and test its parameters\n");

    list = list_new((void (*)(void *))print_char, 
    (void (*))delete_char, 
    (int (*)(void *, void *))equal_char);
 
    assert(list != NULL);
    assert(list->size == 0);
    assert(list->data == NULL);
    assert(list->delete_data != NULL);
    assert(list->print_data != NULL);
    assert(list->equal_data != NULL);

    //list = list_delete(list);
    //assert(list == NULL);

    fprintf(stderr, "=> Test passed with success\n");
    return 1;
}

int test_list_add_first() {

    fprintf(stderr, "\n## Test of the list_add_first function\n");

    fprintf(stderr, "<= Test : We try to add in an invalid way and test its parameters\n");

    list_t list = list_new((void (*)(void *))print_char, 
    (void (*))delete_char, 
    (int (*)(void *, void *))equal_char);

    assert(list != NULL);

    list = list_add_first(list, NULL);
    assert(list == NULL);

    char* p_char = create_char('a');
    assert(p_char != NULL);

    list = list_add_first(NULL, p_char);
    assert(list == NULL);

    fprintf(stderr, "=> Test passed with success\n");

    fprintf(stderr, "<= Test : We try to create a add validly to a list and test its parameters\n");

    list = list_new((void (*)(void *))print_char, 
    (void (*))delete_char, 
    (int (*)(void *, void *))equal_char);
    assert(list != NULL);

    char* p_char2 = create_char('b');
    assert(p_char2 != NULL);

    list = list_add_first(list, p_char2);
    assert(list != NULL && '1');
    assert(list->size == 1);
    assert(list->data->next == NULL);

    assert(list->data->data == p_char2 && '2');

    list = list_add_first(list, p_char);
    assert(list != NULL);

    assert(list->size == 2);
    assert(list->data->data == p_char);
    assert(list->data->next->data == p_char2);
 
    fprintf(stderr, "=> Test passed with success\n");
    return 1; 

}

int test_list_add_last() {

    fprintf(stderr, "\n## Test of the list_add_last function\n");

    fprintf(stderr, "<= Test : We try to add in an invalid way and test its parameters\n");

    list_t list = list_new((void (*)(void *))print_char, 
    (void (*))delete_char, 
    (int (*)(void *, void *))equal_char);

    assert(list != NULL);

    list = list_add_last(list, NULL);
    assert(list == NULL);

    char* p_char = create_char('a');
    assert(p_char != NULL);

    list = list_add_last(NULL, p_char);
    assert(list == NULL);

    fprintf(stderr, "=> Test passed with success\n");

    fprintf(stderr, "<= Test : We try to create a add validly to a list and test its parameters\n");

    list = list_new((void (*)(void *))print_char, 
    (void (*))delete_char, 
    (int (*)(void *, void *))equal_char);
    assert(list != NULL);
    char* p_char2 = create_char('b');
    assert(p_char2 != NULL);

    list = list_add_last(list, p_char2);

    assert(list != NULL && '1');
    assert(list->size == 1);
    assert(list->data->next == NULL);

    assert(list->data->data == p_char2 && '2');

    list = list_add_last(list, p_char);

    assert(list != NULL);
    assert(list->size == 2);
    assert(list->data->data == p_char2);
    assert(list->data->next->data == p_char);
 
    fprintf(stderr, "=> Test passed with success\n");
    return 1; 

}

int test_list_is_empty() {

    fprintf(stderr, "\n## Test of the list_is_empty function\n");

    fprintf(stderr, "<= Test : We try to create new a list and test if they are empty before and after adding\n");
   
    list_t list = list_new((void (*)(void *))print_char, 
    (void (*))delete_char, 
    (int (*)(void *, void *))equal_char);
    assert(list != NULL);

    assert(list_is_empty(list) == 1);
    char* p_char = create_char('a');
    assert(p_char != NULL);

    list = list_add_first(list, p_char);
    assert(list != NULL);
    assert(list_is_empty(list) == 0);

    list = list_delete(list);
    assert(list == NULL);

    fprintf(stderr, "=> Test passed with success\n");

    return 1;
}

int test_list_del_first() {

    fprintf(stderr, "\n## Test of the list_del_last function\n");

    fprintf(stderr, "<= Test : We try to create new list and test its parameters before and after deleting first\n");
   
    list_t list = list_crea_list();
    assert(list != NULL);

    list = list_del_first(list);
    assert(list != NULL);
    assert(list->size == 1);
    assert(list->data != NULL);
    char b = *(char*)(list->data->data);
    assert(b == 'b');
    assert(list->data->next == NULL);

    list = list_del_first(list);
    assert(list != NULL);
    assert(list->size == 0);
    assert(list->data == NULL);

    fprintf(stderr, "=> Test passed with success\n");
    return 1;
}

int test_list_del_last() {

    fprintf(stderr, "\n## Test of the list_del_last function\n");

    fprintf(stderr, "<= Test : We try to create new list and test its parameters before and after deleting first\n");
   
    list_t list = list_crea_list();
    assert(list != NULL);

    list = list_del_last(list);
    assert(list != NULL);
    assert(list->size == 1);
    assert(list->data != NULL);
    char a = *(char*)(list->data->data);
    assert(a == 'a');
    assert(list->data->next == NULL);

    list = list_del_last(list);
    assert(list != NULL);
    assert(list->size == 0);
    assert(list->data == NULL);

    fprintf(stderr, "=> Test passed with success\n");
    return 1;
}

int test_list_delete() {

    fprintf(stderr, "\n## Test of the list_delete function\n");

    fprintf(stderr, "<= Test : We try to create new list and test its parameters before and after deleting first\n");
   
    list_t list = list_crea_list();
    assert(list != NULL);

    list = list_delete(list);
    assert(list == NULL);
    fprintf(stderr, "=> Test passed with success\n");
    return 1;
}

int test_list_length() {

    fprintf(stderr, "\n## Test of the lis_length function\n");

    fprintf(stderr, "<= Test : We try a NULL in length\n");

    assert(list_length(NULL) == -1);

    list_t list = list_new((void (*)(void *))print_char, 
    (void (*))delete_char, 
    (int (*)(void *, void *))equal_char);

    assert(list != NULL);

    assert(list_length(list) == 0);

    list = list_delete(list);
    assert(list == NULL);

    list = list_crea_list();
    assert(list != NULL);

    assert(list_length(list) == 2);

    list = list_delete(list);
    assert(list == NULL);
    fprintf(stderr, "=> Test passed with success\n");
    return 1;
}

int test_list_printf() {

    fprintf(stderr, "\n## Test of the lis_length function\n");

    fprintf(stderr, "<= Test : We try a NULL in length\n");

    assert(list_length(NULL) == -1);

    list_t list = list_crea_list();
    assert(list != NULL);

    list_printf(list);

    list = list_delete(list);
    assert(list == NULL);
    fprintf(stderr, "=> Test passed with success\n");
    return 1;
}

int main() {
    test_list_new();
    test_list_add_first();
    test_list_add_last();
    test_list_is_empty();
    test_list_del_first();
    test_list_del_last();
    test_list_delete();
    test_list_length();
    test_list_printf();



    fprintf(stderr, "Tests of file 04_list.c pass with success\n");
    return EXIT_SUCCESS;
}

