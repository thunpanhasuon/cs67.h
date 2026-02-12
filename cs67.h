#ifndef CS67_H
#define CS67_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALLOCATION_SUCCESS 0
#define ALLOCATION_FALIURE -1
/* simple utils */
void term_clear();

typedef struct {
    int status_err;
    void *data;
    size_t element_size;
    size_t size;
    size_t capacity;
} Array;

void* array_init(size_t element, size_t capacity);
int array_push(Array *a, const void* element);
void array_free(Array *a);
void* vector_get(Array* a, size_t index);

#endif // CS67_H
