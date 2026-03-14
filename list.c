#include "list.h"

void* create_list(u32 data) {
	List* new_list = malloc(sizeof(List));	
	if (new_list == NULL) {
		return NULL;
	}
	new_list->data = data;
	new_list->next = NULL;
	new_list->prev = NULL;
	return new_list;
}

void push_front(List** list, u32 data) {

	List* new = create_list(data);
	/* cheack if head ?*/
	if (list == NULL) {
		/* mod the pointer */
		*list = new;
	}
	/* point to the current head ? */	
	new->next = *list;
	*list = new;
	new->prev = *list;
}
/* return 0 successful deletion*/
int delete_front(List** list) {
	int data;
	
	if (*list == NULL) {
		/* empty no del (list empty)*/
		return 0;
	}
	
	/* create a temp data */
	List *temp = *list;

	data = temp->data;

	*list = temp->next;
	
	if (temp != NULL) {
		/* the last head is gone del it */
		/* all we do is move head back to the next while prev pointed to the head (temp is head)*/
		temp->prev = NULL;
	}
			
	free(temp);
	return data;
}


void list_free(List** list) {
	free(*list);	
	*list = NULL;
}

void debug_list_forword(List* list) {
	if (list == NULL) {
		return;
	}
	
	List *temp = list;
	
	while (temp != NULL) {
		printf("Data: %d\n", temp->data);
		temp = temp->next;
	}

}
void debug_list_backword(List* list) {
	if (list == NULL) {
		return;
	}
	/* move the pointer to the ends */
	List* temp = list;	
	while (temp != NULL)  {
		/* move it to the end */
		temp = temp->next;
	}
	
	while (temp != NULL) {
		printf("Data: %d\n", temp->data);
		temp = temp->prev;
	}
	
}

