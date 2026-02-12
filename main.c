#include "cs67.h"
int main() {

	printf("Hello from CS67\n");
	double x = 1.0310, y = 10.323;	

	Array* container = array_init(sizeof(double), 1); 
	
	array_push(container, &x);
	array_push(container, &y);

	/* create a loop that loop to range and print out the content ether to access it */
	double *rax = (double *)vector_get(container, 0);
    double *rbx = (double *)vector_get(container, 1);
	
	printf("Element -> %f %f\n", *rax, *rbx);


	array_free(container);
	

	
	

	return 0;
}
