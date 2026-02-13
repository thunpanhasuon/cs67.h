#ifndef CS67_H
#define CS67_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 4096 
#define ALLOCATION_SUCCESS 0
#define ALLOCATION_FALIURE -1

typedef struct {
    int status_err;
    void *data;
    size_t element_size;
    size_t size;
    size_t capacity;
} Array;

/* dynamic array */
void* array_init(size_t element, size_t capacity);
int array_push(Array *a, const void* element);
void array_free(Array *a);
void* vector_get(Array* a, size_t index);
void* array_inter(Array* a); 


/* simple helper function */
int str_equal(const char *a, const char *b);
int str_len(const char* s);
char *str_cat(char* dest, const char* src);
char *str_chr(const char *str, const char uc);
char *str_copy(char* dest, const char* src);
char *str_clone(const char *s);

/* simple helper io uitls function */
char *read_file(const char *path);

void term_clear();

#endif // CS67_H
