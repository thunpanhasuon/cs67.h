#include "string.h"

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
	char* initial = dest;
	while ((*dest++ = *src++) != '\0');
	return initial;
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
	/* save pointer for return */	
	char* initial = dest;

	/* move the pointer to the end */
	while (*dest != '\0') { 
		*dest++;
	}
	while ((*dest++ = *src++) != '\0') { /* I leaves this empty for a resssssssssssion :) */};

	return initial;

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

