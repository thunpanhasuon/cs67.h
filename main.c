#include "list.h"

void printForword(List* list) {
	List* temp = list;

	while (temp != NULL) {
		printf("%d\n", temp->data);	
		temp = temp->next;
	}
}
void printBackword(List* list) {
	List* temp = list;
	if (temp == NULL) {
		return;
	}
	
	while (temp->next != NULL) {
		temp = temp->next;
	}
	
	while (temp != NULL) {
		printf("%d\n",temp->data);
		temp = temp->prev;
	}
}
int main() {

	
	List* list = NULL;	
	
	push_front(&list, 6); 
	push_front(&list, 7); 			

	delete_front(&list);
	delete_front(&list);

	push_front(&list, 6); 
	printForword(list);
	
	list_free(&list);
	printForword(list);


	return 0;
}
