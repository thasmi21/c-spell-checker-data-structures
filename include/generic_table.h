
#ifndef GENERIC_TAB_H
#define GENERIC_TAB_H

#include <stdio.h>

//A major problem appeard when using such function if we want decent performance we want to have an insert last in O(1)
//But if 2 pointers pointing to the same value are insered when the block is freed, we are risking a double free
//Therefore an isue arive should we assure security and check if any block is already pointed by an other element ?
//A solution could be to check in the free but first it will create an O(n2)
//This solution permit to reduce run time overhead and nobody care if your game take time to close.
//Also the O(n2) is just a simple list traversal meaning the real k of time = k*n2 will be small.
//(not douable if we wanted to sore multiple type in an array like in python)

//MOST OF COMMENTARY IS CHAT_GPT GENERATED

/*
 * A structure to represent a generic table that can hold an array of void* elements.
 * It also supports custom functions for printing, deleting, and comparing elements.
 * 
 * Fields:
 *  - data: A dynamically allocated array of void* pointers to hold the elements.
 *  - max_size: The maximum capacity of the table (number of elements).
 *  - actual_size: The current number of elements in the table.
 *  - print_data: A function pointer for printing elements. The function must take 
 *    a void* and a FILE* for output.
 *  - delete_data: A function pointer for deleting elements. The function must 
 *    return NULL upon successful deletion.
 *  - equal_data: A function pointer for comparing two elements. It must return a non-zero 
 *    value if the two elements are equal, otherwise return 0.
 */
typedef struct {
    void** data;
    size_t max_size;
    size_t actual_size;
    void (*print_data)(void*, FILE*);
    void* (*delete_data)(void*);
    int (*equal_data)(void*, void*);
} *table_t;

/*
 * Creates a new table of a specified size 'n'. The 'print_data', 'delete_data', 
 * and 'equal_data' functions must be provided to handle the elements properly.
 * 
 * Parameters:
 *  - n: The maximum number of elements the table can hold (must be > 0).
 *  - print_data: Function pointer for printing an element.
 *  - delete_data: Function pointer for deleting an element (must return NULL upon success).
 *  - equal_data: Function pointer for comparing two elements.
 * 
 * Returns:
 *  - A new table_t structure on success.
 *  - NULL if an error occurs (invalid parameters or memory allocation failure).
 */
table_t table_new(size_t n, void (*print_data)(void*, FILE*), void* (*delete_data)(void*), int (*equal_data)(void*, void*));

/*
 * Deletes the table and frees all allocated memory. It also calls the delete_data 
 * function on each element to clean up user-defined resources.
 * 
 * This function is full of assert so if anything is wrong it will be BREAK. 
 * It is on purpose, we do not mess with memory
 * 
 * Further testing is needed
 * 
 * Parameters:
 *  - tab: The table to delete.
 * 
 * Returns:
 *  - NULL after deletion.
 */
table_t table_delete(table_t tab);

/*
 * Prints the contents of the table using the print_data function provided during
 * the creation of the table.
 * 
 * Parameters:
 *  - tab: The table to print.
 */
void table_printf(table_t tab);

/*
 * Appends a new element to the table. The table's current size must be less than 
 * the maximum capacity.
 * 
 * Parameters:
 *  - val: The new element to add (not NULL).
 *  - tab: The table where the element will be appended (not NULL).
 * 
 * Returns:
 *  - 1 if the append is successful.
 *  - Assertion failure if the table is full or any parameter is invalid.
 */
int table_append(void* val, table_t tab);

/*
 * Inserts a new element at the specified index. Elements to the right of the index 
 * are shifted one position to the right. This operation has O(n) complexity, and 
 * should not be used for inserting at the end of the table (use table_append instead).
 * 
 * Parameters:
 *  - val: The new element to insert.
 *  - index: The position to insert the element (must be between 0 and actual_size-1).
 *  - tab: The table where the element will be inserted.
 * 
 * Returns:
 *  - 1 if the insertion is successful.
 *  - An error code (-1 to -7) if the operation fails (invalid parameters or memory constraints).
 */
int table_insert_at(void* val, size_t index, table_t tab);

/*
 * Removes an element at the specified index. Elements to the right of the index 
 * are shifted one position to the left. This operation has O(n) complexity.
 * 
 * Parameters:
 *  - index: The position of the element to remove (must be between 0 and actual_size-1).
 *  - tab: The table from which the element will be removed.
 * 
 * Returns:
 *  - 1 if the removal is successful.
 *  - An error code (-1 to -7) if the operation fails (invalid parameters or memory constraints).
 */
int table_remove_at(size_t index, table_t tab);

#endif
