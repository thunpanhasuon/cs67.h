#ifndef CS67_H
#define CS67_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 4096 

typedef struct {
    int status_err;
    void *data;
    size_t element_size;
    size_t size;
    size_t capacity;
} Array;

typedef struct {
    void* current;
    size_t element_size;
} Array_Inter;

/* 
 * array_init
 * --------------------------
 * Creates and initializes a new dynamic array.
 * element_size: size of each element in bytes (e.g., sizeof(int))
 * capacity: initial number of elements the array can hold
 * Returns a pointer to the allocated array (void* internally)
 */
void* array_init(size_t element, size_t capacity);

 /* 
 * array_push
 * --------------------------
 * Adds a new element to the end of the array.
 * a: pointer to the Array structure
 * element: pointer to the value to push
 * Returns 0 on success, non-zero on failure (e.g., memory allocation failed)
 */
int array_push(Array *a, const void* element);

/* 
 * array_get
 * --------------------------
 * Returns a pointer to the element at the given index.
 * a: pointer to the Array
 * index: position of the element (0-based)
 * Note: returned pointer must be cast to the correct type by the caller
 */
void* array_get(Array* a, size_t index);

/* 
 * array_free
 * --------------------------
 * Frees all memory associated with the array.
 * a: pointer to the Array
 * After calling, the array should not be used again.
 */
void array_free(Array *a);

/* 
 * inter_begin
 * --------------------------
 * Returns an iterator pointing to the first element of the array.
 * a: pointer to the Array
 */
Array_Inter inter_begin(Array* a);

/* 
 * inter_next
 * --------------------------
 * Advances the iterator to the next element and returns a pointer to it.
 * it: pointer to the iterator structure
 * Returns NULL if the end of the array is reached
 */
void* inter_next(Array_Inter* it);

/* write a wrapper to get the array */
int get_int(Array* a, size_t index);


/* 
 * str_equal
 * --------------------------
 * Compares two strings for equality.
 * Returns 1 if equal, 0 otherwise
 */
int str_equal(const char *a, const char *b);

/* 
 * str_len
 * --------------------------
 * Returns the length of a null-terminated string (excluding the null character)
 */
int str_len(const char* s);

/* 
 * str_cat
 * --------------------------
 * Concatenates src to the end of dest.
 * dest must have enough space to hold the result.
 * Returns pointer to dest
 */
char *str_cat(char* dest, const char* src);

/* 
 * str_chr
 * --------------------------
 * Returns a pointer to the first occurrence of character uc in str.
 * Returns NULL if character not found
 */
char *str_chr(const char *str, const char uc);

/* 
 * str_copy
 * --------------------------
 * Copies the string src into dest.
 * dest must have enough space.
 * Returns pointer to dest
 */
char *str_copy(char* dest, const char* src);

/* 
 * str_clone
 * --------------------------
 * Allocates memory and creates a copy of the string s.
 * Caller is responsible for freeing the returned string.
 * Returns pointer to the cloned string
 */
char *str_clone(const char *s);


/* TODO */
char *read_file(const char *path);

void term_clear();

#endif // CS67_H
