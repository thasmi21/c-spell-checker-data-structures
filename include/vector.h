#ifndef VECT_H
#define VECT_H

#include <stdio.h>
#include "generic_table.h"

//!!! Still to do write error return for vect_lookup() and vect_remove_at() and remove assert() !!!

// Define vect_t as an alias for table_t to use in vector operations
typedef table_t vect_t;

/**
 * vect_new - Creates a new vector (dynamically allocated).
 * 
 * @param n: Initial size of the vector.
 * @param print_data: Function pointer to print the data stored in the vector.
 * @param delete_data: Function pointer to delete the data stored in the vector.
 * @param equal_data: Function pointer to check equality between two elements.
 * 
 * @return A pointer to the newly created vector, or NULL if memory allocation fails or invalid parameters.
 */
vect_t vect_new(size_t n, void (*print_data)(void*), void* (*delete_data)(void*), int (*equal_data)(void*, void*));

/**
 * vect_append - Adds a new element to the vector.
 * 
 * @param element: Pointer to the element to be added to the vector.
 * @param vec: The vector to which the element should be added.
 * 
 * @return 1 on success, or a negative value if an error occurs (e.g., memory issues or invalid parameters).
 */
int vect_append(void* element, vect_t vec);

/**
 * vect_printf - Prints the contents of the vector.
 * 
 * @param vec: The vector to be printed.
 * 
 * This function uses the print_data function pointer provided when creating the vector to print each element.
 */
void vect_printf(vect_t vec);

/**
 * vect_delete - Deletes the vector and frees its memory.
 * 
 * @param vec: The vector to be deleted.
 * 
 * @return NULL after successfully deleting the vector.
 */
vect_t vect_delete(vect_t vec);

/**
 * vect_find - Finds an element in the vector by using the vector's equality function.
 * 
 * @param element: The element to search for in the vector.
 * @param vec: The vector to search in.
 * 
 * @return The index of the element if found, or -1 if not found.
 */
int vect_find(void* element, vect_t vec);

/**
 * vect_lookup - Finds an element in the vector using a custom equality function.
 * 
 * @param element: The element to search for in the vector.
 * @param vec: The vector to search in.
 * @param equality_test: A function pointer that defines how to check equality between two elements.
 * 
 * @return The index of the element if found, or -1 if not found.
 */
int vect_lookup(void* element, vect_t vec, int (*equality_test)(void*, void*));

/**
 * vect_remove_at - Removes an element from the vector at the specified index.
 * 
 * @param index: The index of the element to remove.
 * @param vec: The vector from which the element will be removed.
 * 
 * @return 1 on success, or a negative value if an error occurs.
 *         The vector size is shrunk if necessary to free unused memory.
 */
int vect_remove_at(size_t index, vect_t vec);

int vect_is_equal(vect_t tab1, vect_t tab2);

#endif // VECT_H
