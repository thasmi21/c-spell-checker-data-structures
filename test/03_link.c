#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "link.h"

static char* delete_char(char* c) {

    assert(c != NULL);
    free(c);
 
    c = NULL;
    return NULL;
}

//static void print_char(char* c) {
// printf("%c", *c);
//}

static char* create_char(char value) {

 char* p_chr = malloc(sizeof(char));
 assert(p_chr != NULL && "Error in 03_link.c/create_char: malloc failed and returned NULL\n");
 *p_chr = value;
 return p_chr;
}


static int test_link_new() {

    fprintf(stderr, "\n## Test of the link_new function\n");

    fprintf(stderr, "<= Test : We try to create a new link and test its parameters\n");

    link_t link = link_new();
    assert(link == NULL);

    link = link_delete(link, (void (*))delete_char);
    assert(link == NULL);

    fprintf(stderr, "=> Test passed with success\n");
    return 1;

}

static int test_link_add_first() {

    fprintf(stderr, "\n## Test of the link_add_first function\n");

    fprintf(stderr, "<= Test : We try to create invalid operation, must return errors\n");

    link_t link = link_new();
    assert(link == NULL);

    link = link_add_first(link, NULL);
    assert(link == NULL);

    fprintf(stderr, "=> Test passed with success\n");

    fprintf(stderr, "<= Test : We try to create new link and test its parameters\n");

    link = link_new();
    assert(link == NULL);

    char* p_char = create_char('a');
    assert(p_char != NULL);

    link = link_add_first(link, p_char);
    assert(link != NULL);

    char* p_char2 = create_char('b');
    assert(p_char2 != NULL);

    link = link_add_first(link, p_char2);
    assert(link != NULL);

    assert(link != NULL);

    assert(link->next != NULL);
    assert(link->data == p_char2);
    assert(link->next->data == p_char);
    printf("lol5.4\n");
    assert(link->next->next == NULL);
    printf("lol6\n");
    link = link_delete(link, (void (*))delete_char);
    assert(link == NULL);
    return 1;
}

static int test_link_add_last() {

    fprintf(stderr, "\n## Test of the link_add_last function\n");

    fprintf(stderr, "<= Test : We try to create invalid operation, must return errors\n");

    char* p_char = create_char('a');
    assert(p_char != NULL);

    link_t test_link = link_new();
    assert(test_link == NULL);

    test_link = link_add_last(test_link, NULL);
    assert(test_link == NULL);

    fprintf(stderr, "=> Test passed with success\n");

    fprintf(stderr, "<= Test : We try to do valid operations and tests theirs results\n");

    link_t link = link_new();
    assert(link == NULL);

    char* p_char2 = create_char('b');
    assert(p_char2 != NULL && "1");

    link = link_add_last(link, p_char);
    assert(link != NULL && "2");

    link = link_add_last(link, p_char2);
    assert(link != NULL && "3");

    printf("lol\n");

    assert(link != NULL);
    assert(link->next != NULL);
    assert(link->data == p_char);
    assert(link->next->data == p_char2);
    assert(link->next->next == NULL);
    
    link = link_delete(link, (void (*))delete_char);
    assert(link == NULL);
    
    fprintf(stderr, "=> Test passed with success\n");
    return 1;
}

static int test_link_del_first() {
    
    fprintf(stderr, "\n## Test of the link_del_first function\n");

    fprintf(stderr, "<= Test : We try to create invalid operation, must return errors\n");

    char* p_char = create_char('a');
    assert(p_char != NULL);

    link_t test_link = link_new();
    assert(test_link == NULL);

    test_link = link_del_first(test_link, NULL);
    assert(test_link == NULL);

    fprintf(stderr, "=> Test passed with success\n");

    fprintf(stderr, "<= Test : We try to create new link and test its parameters after deleting\n");

    link_t link = link_new();
    assert(link == NULL);

    char* p_char2 = create_char('b');
    assert(p_char2 != NULL);

    link = link_add_first(link, p_char2);
    assert(link != NULL);

    link = link_add_first(link, p_char);
    assert(link != NULL);

    link = link_del_first(link, (void (*))delete_char);
    assert(link != NULL);

    assert(link->data == p_char2);
    assert(link->next == NULL);

    link = link_del_first(link, (void (*))delete_char);
    assert(link == NULL);

    fprintf(stderr, "=> Test passed with success\n");
    return 1;
}

static int test_link_del_last() {

    fprintf(stderr, "\n## Test of the link_del_first function\n");

    fprintf(stderr, "<= Test : We try to create invalid operation, must return errors\n");

    char* p_char = create_char('a');
    assert(p_char != NULL);

    link_t test_link = link_new();
    assert(test_link == NULL);

    test_link = link_del_last(test_link, NULL);
    assert(test_link == NULL);

    fprintf(stderr, "=> Test passed with success\n");

    fprintf(stderr, "<= Test : We try to create new link and test its parameters after deleting\n");

    link_t link = link_new();
    assert(link == NULL);

    char* p_char2 = create_char('b');
    assert(p_char2 != NULL);

    link = link_add_first(link, p_char2);
    assert(link != NULL);

    link = link_add_first(link, p_char);
    assert(link != NULL);

    link = link_del_last(link, (void (*))delete_char);
    assert(link != NULL);

    assert(link->data == p_char);
    assert(link->next == NULL);

    link = link_del_last(link, (void (*))delete_char);
    assert(link == NULL);


    fprintf(stderr, "=> Test passed with success\n");
    return 1;
}

static int test_link_delete() {

    fprintf(stderr, "\n## Test of the link_del_first function\n");

    fprintf(stderr, "<= Test : We try to create new links and test their parameters after deleting\n");
   
    char* p_char = create_char('b');
    assert(p_char != NULL);
    link_t link = link_new();
    assert(link == NULL);

    char* p_char2 = create_char('a');
    assert(p_char2 != NULL);

    link = link_add_first(link, p_char2);
    assert(link != NULL);

    link = link_add_first(link, p_char);
    assert(link != NULL);

    link = link_delete(link, (void (*))delete_char);
    assert(link == NULL);
    fprintf(stderr, "=> Test passed with success\n");
    return 1;
}

static int test_link_is_empty() {


    fprintf(stderr, "\n## Test of the link_is_empty function\n");

    fprintf(stderr, "<= Test : We try to create new links and test if they are empty before and after adding\n");
   
    link_t link = link_new();
    assert(link == NULL);
    assert(link_is_empty(link) == 1);
    char* p_char2 = create_char('a');
    assert(p_char2 != NULL);

    link = link_add_first(link, p_char2);
    assert(link != NULL);
    assert(link_is_empty(link) == 0);

    link = link_delete(link, (void (*))delete_char);
    assert(link == NULL);

    fprintf(stderr, "=> Test passed with success\n");

    return 1;
}

int main() {

    test_link_new();
    test_link_add_first();
    test_link_add_last();
    test_link_del_first();
    test_link_del_last();
    test_link_delete();
    test_link_is_empty();
    fprintf(stderr, "Tests of file 03_link.c passed with success\n");
    return EXIT_SUCCESS;
}

//valgrind command to run
//valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./test/03_link
