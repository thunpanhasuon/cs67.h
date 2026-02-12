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

void* array_init(size_t element, size_t capacity) {
	Array* new_array = malloc(sizeof(Array));
	/* fuck it i don't care anymore */
	if (new_array == NULL) {
		/* reseting the allocation */
		exit(EXIT_FAILURE);	
	}
	new_array->size = 0;
	new_array->element_size = element;
	new_array->capacity = capacity;
	new_array->data = malloc(new_array->capacity * new_array->element_size);	
	
	if (new_array->data == NULL) {
		/* reseting the allocation */
		exit(EXIT_FAILURE);
	}
	new_array->status_err = 0;
	
	return new_array; 
}

int array_push(Array* a, const void* element) {
	if (a->size == a->capacity)	{
		/* double the memroy capacity */
		size_t new_capacity = a->capacity * 2;
		a->capacity = new_capacity;

		/* allocated new space */
		void* new_space = realloc(a->data, a->capacity * a->element_size);
		if (new_space == NULL) {
			/* get nuke */
			exit(EXIT_FAILURE);
		}
		a->data = new_space;
	}
	
	void* target = (char*)a->data + (a->size * a->element_size);
	memcpy(target, element, a->element_size);
	a->size++;
	return 0;
}
void* vector_get(Array* a, size_t index) {
    if (index >= a->size) return NULL;
    return (char *)a->data + (index * a->element_size);
}

void array_free(Array* a) {
	/* free data and dynamic array */
	free(a->data);
	free(a);
}