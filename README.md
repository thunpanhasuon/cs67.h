# CS67lib

**CS67lib** is a C library inspired by [CS50](https://cs50.harvard.edu/) and designed for students at RUPP to **practice memory management and low-level programming concepts**. It provides hands-on tools for working with dynamic arrays, strings, and linked lists, helping users understand safe and efficient memory use.I'm also plan to add more feature like important dsa in computer science, and also add a human wirtten test becuase this test is build by AI :(

## Features Overview

```c
/* Dynamic array */
Array* array_init(size_t element, size_t capacity);
int array_push(Array *a, const void* element);
void* array_get(Array* a, size_t index);
void array_free(Array *a);

/* List */
Node* create_node(const void* element, size_t element_size);
Node* push_back(Node* head, const void* element);
Node* push_front(Node** head, const void* element);
void* pop_front(Node** head);

/* String */


/* Io uitls */



