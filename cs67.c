#include "cs67.h"


Node* create_node(const void* element, size_t element_size) {
	Node* temp = (Node *)malloc(sizeof(Node));
	if (temp == NULL) {
		fprintf(stderr, "Error value %d \n", errno);
		fprintf(stderr, "Error allocating memory %s\n", strerror(errno));	
		/* sorry no memory */
		return NULL;
	}
	temp->element_size = element_size;
	temp->data = malloc(element_size);
	if (temp->data == NULL) {
		fprintf(stderr, "Error value %d \n", errno);
		fprintf(stderr, "Error allocating memory %s\n", strerror(errno));	
		/* sorry no memory */
		return NULL;
	}
	
	/* we have to know the size to copy the entire data */
	memcpy(temp->data, element, temp->element_size);
	temp->next = NULL;
	
	return temp;
}

Node* push_back(Node* head, const void* element) {

	printf("Size -> %zu \n", head->element_size);

	Node* temp = create_node(element, sizeof(head->element_size));
	
	if (head == NULL) {
		/* if the list is empty */
		return temp;
	} else {	
		Node* current = head;
		while (current->next != NULL) {
			/* point to the next node*/
			current = current->next;
		}
		/* link out the last prv node */
		current->next = temp;	
	}

	/* if the node is empty */
	return head;
}
Node* push_front(Node** head, const void* element) {
	Node* temp = create_node(element, (*head)->element_size);
	
	temp->next = (*head); /* pointed last when the head pointed */
	
	/* update the new head pointer */
	(*head) = temp;
	
	return *head;
}

void* pop_front(Node** head) {

	if (*head == NULL) {
		/* the list is empty no data poping */
		return *head;
	}
	Node* temp = *head;
	
	void* data = temp->data;

	*head = temp->next;
	
	free(temp);
	
	return data;
}
/*
	Create new_array then return the new_array that we have cretaed  
	given size(bytes), and capacity  
*/
Array* array_init(size_t element, size_t capacity) {
	
	
	Array* new_array = malloc(sizeof(Array));
	if (new_array == NULL) {
		new_array->status_err = -1;
		fprintf(stderr, "Error value %d \n", errno);
		fprintf(stderr, "Error allocating memory %s\n", strerror(errno));	
		/* sorry no memory */
		return NULL;
	} 
	new_array->size = 0;
	new_array->element_size = element;
	new_array->capacity = capacity;

	new_array->data = malloc(new_array->capacity * new_array->element_size);		
	if (new_array->data == NULL) {
		new_array->status_err = -1;
		fprintf(stderr, "Error value %d \n", errno);
		fprintf(stderr, "Error allocating memory %s\n", strerror(errno));	
		/* sorry no memory */
		return NULL;	
	}
	new_array->status_err = 0;
	
	return new_array; 
}

/* 
	To push an element, we need size and capacity, 
	To know where it store we use this formula start + (index * size)
*/
int array_push(Array* a, const void* element) {
	if (a->size == a->capacity)	{
		a->capacity *= 2;

		void* new_space = realloc(a->data, a->capacity * a->element_size);
		if (new_space == NULL) {
			/* write to status error */
			a->status_err = -1;
			fprintf(stderr, "Error value %d \n", errno);
			fprintf(stderr, "Error allocating memory %s\n", strerror(errno));	
			return -1;
		}
		a->data = new_space;
	}

	/* calculate where the memory will be store */
	void* target = (char*)a->data + (a->size * a->element_size);
	memcpy(target, element, a->element_size);
	a->size++;
	return 0;
}

/*
	Just like an array
	Just give it index
	Using our previous formula start + (index * size)
	It will give us the location where it stored 
*/
void* array_get(Array* a, size_t index) {
    if (index >= a->size) return NULL;
    return (char *)a->data + (index * a->element_size);
}

void array_free(Array* a) {
	free(a->data);
	free(a);
}


/*
	it a wrapper, without constantly type casting 
	Basically return derefrance the data 
*/
int get_int(Array* a, size_t index) {
	return *(int *)array_get(a, index);
}


/*
	String is just pointer at the end of the day
	if we inc the pointer for s1, s2 to \0
	if both equal the different will be zero 
*/
int str_equal(const char *a, const char *b) {
	while (*a == *b && *a != '\0') {
		*a++;
		*b++;
	}
	return (unsigned char *)a - (unsigned char* )b;
}

/*
	inc the pointer and count the string 
*/
int str_len(const char* s) {
	int count = 0;
	while (*s != '\0') {
		count++;
		*s++;
	}
	return count;
}

/*
	inc the pointer and copy the string uitl it reach \0
*/
char *str_copy(char* dest, const char* src) {
	
	while ((*dest++ = *src++) != '\0') { /* leave it empty */}
	return dest;
}

/* 
	if it hit the the target char we return the pointer basically it position 
	if not it hit the end so no match it just the return the stirng
*/
char *str_chr(const char *str, const char uc) {

	while (*str != '\0') {
		*str++;

		if (*str == uc) {
			return (char *)str;
		}	
	}
	
	return (char *)str;	
}

/* 
	we move the pointer to the end of the dest 
	We start copying form there uitl it reach \0 
*/
char* str_cat(char* dest, const char* src) {
	char* ptr = dest;

	while (*dest != '\0') { 
		*dest++;
	}
	while ((*dest++ = *src++));

	return ptr;		
}

/* 
	allocated this amount becuase we can not create pointer on the fly 
	it act like str_cat()
	don't forget to free it 
*/
char *str_clone(const char *s) {
	size_t str_size = str_len(s);

	char* clone = malloc(str_size * sizeof(char));

	char* start = clone;
	if (clone == NULL) {
		return NULL;
	}
	while (*s != '\0') {
		*clone++ = *s++;
	}

	return start;
}

/* io file utils */
char *read_file(const char *path) {
	size_t size_allocaition = sizeof(char) * MAX_LINE_LENGTH;
	char* buffer = malloc(size_allocaition);
	if (buffer == NULL) {
		return NULL;
	}
	
	FILE* fptr = fopen(path, "r");
	if (fptr == NULL) {
		fprintf(stderr, "Value of error %d \n", errno);
		fprintf(stderr, "Error open file %s \n", strerror(errno));
	} 
	/* it will return EOF */	
	while (fgets(buffer, MAX_LINE_LENGTH, fptr) != NULL);
		
	buffer[MAX_LINE_LENGTH] = '\0';
	fclose(fptr);
	/* don't forget to free*/
	return buffer;
}
