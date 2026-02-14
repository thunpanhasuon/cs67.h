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

/*
	Create new_array then return the new_array that we have cretaed  
	given size(bytes), and capacity  
*/
void* array_init(size_t element, size_t capacity) {
	
	
	Array* new_array = malloc(sizeof(Array));
	if (new_array == NULL) {
		new_array->status_err = -1;
		return NULL;
		
	}

	new_array->size = 0;
	new_array->element_size = element;
	new_array->capacity = capacity;

	new_array->data = malloc(new_array->capacity * new_array->element_size);	
	
	if (new_array->data == NULL) {
		new_array->status_err = -1;
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
	point to the first element of array 
*/
Array_Inter inter_begin(Array* a) {
	return (Array_Inter){a->data, a->element_size};
}

/*
	pointto the next by if we know the next element_size 
	We can also just jump to the next 
*/
void* inter_next(Array_Inter* it) {
	return (char*)it->current + it->element_size;	
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
	
	while (*dest != '\0') {
		*dest++ = *src++;
	}
	return (char*)dest;
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
		return NULL;
	}
	/* it will return EOF */	
	while (fgets(buffer, MAX_LINE_LENGTH, fptr) != NULL);
		
	buffer[MAX_LINE_LENGTH + 1] = '\0';
	fclose(fptr);
	/* don't forget to free*/
	return buffer;
}