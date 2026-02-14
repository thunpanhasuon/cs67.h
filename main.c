#include "cs67.h"
int main() {

	printf("Hello from CS67\n");
	int x = 10, y = 20, z = 40;

	Array* container = array_init(sizeof(double), 1); 
	printf("Is allocation -> %d\n", container->status_err);
	
	array_push(container, &x);
	array_push(container, &y);
	array_push(container, &z);

	Array_Inter inter;
	inter_begin(container);
	for (int i = 0; i < container->size; i++) {
		int x = get_int(container, i);
		printf("Inter -> %d \n", x);
		inter_next(&inter);
	}
	array_free(container);
	
	char* test_string1 = "I love C programming";
	char* test_string2 = str_clone(test_string1);
	char* data = read_file("Hello.txt");

	
	printf("Clone stirng %s\n", test_string2);	
	printf("Reading form file %s \n", data);


	free(test_string2);
	free(data);	

	return 0;
}
