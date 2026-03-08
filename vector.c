#include "vector.h"

/* vector for version 2.0 */
Vector* vector_init(usize element) {
	
	
	Vector* new_vec = malloc(sizeof(Vector));
	if (new_vec == NULL) {
		fprintf(stderr, "Error value %d \n", errno);
		fprintf(stderr, "Error allocating memory %s\n", strerror(errno));	
		new_vec->data = NULL;
		/* sorry no memory */
		return NULL;
	} 

	new_vec->size = 0;
	new_vec->element_size = element;
	new_vec->capacity = 10;

	new_vec->data = malloc(new_vec->capacity * new_vec->element_size);		
	if (new_vec->data == NULL) {
		fprintf(stderr, "Error value %d \n", errno);
		fprintf(stderr, "Error allocating memory %s\n", strerror(errno));	
		new_vec->data = NULL;
		/* sorry no memory */
		return NULL;	
	}
	
	return new_vec; 
}

void vector_clear(Vector* vec) {
	/* can we dec the size */
	if (vec->data == NULL)	{
		fprintf(stderr, "Error value %d \n", errno);
		fprintf(stderr, "can't not clear an already clear array %s\n", strerror(errno));	
		return;
	}		
	/* how do we remove all the data */
	free(vec->data);
	vec->data = NULL;
	
	char* new_alloc = malloc(vec->capacity * vec->element_size);
	if (new_alloc == NULL) {
		fprintf(stderr, "Error value %d \n", errno);
		fprintf(stderr, "Error allocating memory %s\n", strerror(errno));	
		new_alloc = NULL;
	}
	vec->data = new_alloc; 
	/* reset size */
	vec->size = 0;
}
void vector_reserve(Vector* vec, usize new_capacity) { 

	char* new_alloc = realloc(vec->data, new_capacity * vec->element_size);
	if (new_alloc == NULL) {
		fprintf(stderr, "Error value %d \n", errno);
		fprintf(stderr, "Error allocating memory %s\n", strerror(errno));	
		new_alloc = NULL;
	}
	vec->data = new_alloc;
	vec->capacity = new_capacity;
}

int vector_push(Vector* vec, const void* element) {
	if (vec->size == vec->capacity)	{
		vec->capacity *= 2;

		void* new_space = realloc(vec->data, vec->capacity * vec->element_size);
		if (new_space == NULL) {
			fprintf(stderr, "Error value %d \n", errno);
			fprintf(stderr, "Error allocating memory %s\n", strerror(errno));	
			new_space = NULL;
			return -1;
		}
		vec->data = new_space;
	}

	/* calculate where the memory will be store */
	void* target = (char*)vec->data + (vec->size * vec->element_size);
	memcpy(target, element, vec->element_size);
	vec->size++;
	return 0;
}

int vector_pop_back(Vector* vec) {
	/* no poppy play time */	
	if (vec->size == 0) return -1;

	vec->size--;

	return 0;
}

void* vector_get(Vector* vec, usize index) {
    if (index >= vec->size) return NULL;
    return (char *)vec->data + (index * vec->element_size);
}

bool is_empty(Vector* vec) {

	if (vec->data == vec->data + (vec->size * vec->element_size)) return true;

	return false;
}
void vector_free(Vector* vec) {
	free(vec->data);
	free(vec);
}


