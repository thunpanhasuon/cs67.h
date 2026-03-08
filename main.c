#include "vector.h"

typedef struct Task {
	bool is_done;
	char* string;
} Task;

int main() {
	
	Vector* task = vector_init(sizeof(Task));

	Task task1 = {false, "Do math homework"};
	Task task2 = {false, "Do math practice"};
	Task task3 = {false, "Do enlgish practice"};

	vector_push(task, &task1);
	vector_push(task, &task2);
	vector_push(task, &task3);

	for (size_t i = 0; i < task->size; i++) {
		Task* t = vector_get(task, i);
		printf("Done: %d, Task: %s\n", t->is_done, t->string);
    	}
	
	vector_free(task);
	
	return 0;
}
