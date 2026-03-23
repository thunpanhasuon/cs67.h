#ifndef VECTOR_H
#define VECTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include "type.h"

typedef struct {
    void *data;
    usize element_size;
    usize size;
    usize capacity;
} Vector;

extern int errno;
/**
 * @file vector.h
 * @brief A generic dynamic array (vector) implementation in C
 */

/**
 * @brief Initializes a new vector
 * 
 * @param element   Size of each element in bytes (use sizeof)
 * @param capacity  Initial capacity of the vector
 * @return          Pointer to the new vector, or NULL on failure
 * 
 * @example
 *   Vector* v = vector_init(sizeof(int), 4);
 */
Vector* vector_init(usize element);

/**
 * @brief Pushes an element to the end of the vector
 * 
 * @param vec     Pointer to the vector
 * @param element Pointer to the element to push
 * @return        0 on success, -1 on failure
 */
int vector_push(Vector* vec, const void* element);

/**
 * @brief Removes the last element
 * 
 * @param vec Pointer to the vector
 * @return    0 on success, -1 if vector is empty
 */
int vector_pop_back(Vector* vec);

/**
 * @brief Gets element at index
 * 
 * @param vec   Pointer to the vector
 * @param index Zero-based index
 * @return      Pointer to element, or NULL if out of bounds
 */
void* vector_get(Vector* vec, usize index);

/**
 * @brief check if it empty  
 * 
 * @param vec   Pointer to the vector
 * @return      true, or false  
 */
bool is_empty(Vector* vec);

/**
 * @brief free the entire vector data  
 * 
 * @param vec   Pointer to the vector
 * @return      Pointer to a new memory element, or NULL if out of bounds
 */
void vector_clear(Vector* vec);


/**
 * @brief Frees all memory associated with the vector
 * 
 * @param vec Pointer to the vector
 */
void vector_free(Vector* vec);

#endif // VECTOR_H 
