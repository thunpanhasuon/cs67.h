#include "cs67.h"


void term_clear() {

	#ifdef _WIN32	
		system("cls");
	#elif __LINUX__
		system("clear");
	#elif __APPLE__
		system("clear");
	#else 
		#error "Unsupported System"
	#endif 

}
/* impermentation of dynamic array */
void* array_init(size_t element, size_t capacity) {
	
	/* details instruction on how it work */
	

	/* allocated the structure */
	Array* new_array = malloc(sizeof(Array));
	if (new_array == NULL) {
		new_array->status_err = -1;
		return NULL;
		
	}
	/* init the requred data */
	new_array->size = 0;
	new_array->element_size = element;
	new_array->capacity = capacity;

	/* we allocated the data done congrate :)*/
	new_array->data = malloc(new_array->capacity * new_array->element_size);	
	
	if (new_array->data == NULL) {
		new_array->status_err = -1;
		return NULL;	
	}
	new_array->status_err = 0;
	
	return new_array; 
}

int array_push(Array* a, const void* element) {
	/* this part check if do we have enough memory if not double it and give it to the next persion*/
	if (a->size == a->capacity)	{
		a->capacity *= 2;

		void* new_space = realloc(a->data, a->capacity * a->element_size);
		if (new_space == NULL) {
			a->status_err = -1;
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
void* vector_get(Array* a, size_t index) {
	/* given the index it pretty easy just calucated the postion and return it */
    if (index >= a->size) return NULL;
    return (char *)a->data + (index * a->element_size);
}

void array_free(Array* a) {
	free(a->data);
	free(a);
}


/* impermentation of simple helper function */

int str_equal(const char *a, const char *b) {
	/* point to both of them ether of them hit the null \0 we will return 0 or negitive for not */
	while (*a == *b && *a != '\0') {
		*a++;
		*b++;
	}
	return (unsigned char *)a - (unsigned char* )b;
}

int str_len(const char* s) {
	int count = 0;
	while (*s != '\0') {
		count++;
		*s++;
	}
	return count;
}

char *str_copy(char* dest, const char* src) {
	
	/* point to the first dest and move the pointer along src */
	while (*dest != '\0') {
		*dest++ = *src++;
	}
	/* return pointer to a string*/
	return (char*)dest;
}

char *str_chr(const char *str, const char uc) {

	while (*str != '\0') {
		*str++;

		/* if it hit the the target char we return the pointer basically it position */
		if (*str == uc) {
			/* return that location */
			return (char *)str;
		}	
	}
	
	/* if not it hit the end so no match it just the return the stirng */
	return (char *)str;	
}

char* str_cat(char* dest, const char* src) {
	/* save the pointer then move the prt along src we use the correct locating in memory basically stirng only work ether the pointer *toFrist */
	char* ptr = dest;

	while (*dest != '\0') { 
		*dest++;
	}
	while ((*dest++ = *src++));

	return ptr;		
}

char *str_clone(const char *s) {
	/* allocated this amount becuase we can not create pointer by the fly */
	size_t str_size = str_len(s);

	char* clone = malloc(str_size * sizeof(char));

	char* start = clone;
	if (clone == NULL) {
		return NULL;
	}
	/* it act like str_cat() */	
	while (*s != '\0') {
		*clone++ = *s++;
	}

	/* don't forget to free it */
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
		return NULL;
	}
	/* it will return EOF */	
	while (fgets(buffer, MAX_LINE_LENGTH, fptr) != NULL);
		
	buffer[MAX_LINE_LENGTH + 1] = '\0';
	fclose(fptr);
	/* don't forget to free*/
	return buffer;
}