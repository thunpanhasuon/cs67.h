#ifndef LIST_H
#define LIST_H

#include "type.h" 
#include <stdlib.h>
#include <stdio.h>

typedef struct List {
	u32 data;	
	struct List* next;
	struct List* prev;
} List;

/* add a init for list */
void* create_list(u32 data);
/* add a push front */
void push_front(List** list, u32 data);
/* add push back */
int delete_front(List** list);
/* debug and print out */
void list_free(List** list);
/* for printing debug data*/
void debug_list_forword(List* list);
void debug_list_backword(List* list);

#endif // LIST_H
