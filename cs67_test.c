#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "cs67.h"

/* Test result counters */
int tests_passed = 0;
int tests_failed = 0;

/* Macro for test assertions */
#define TEST_ASSERT(condition, test_name) \
    do { \
        if (condition) { \
            printf("✓ PASS: %s\n", test_name); \
            tests_passed++; \
        } else { \
            printf("✗ FAIL: %s\n", test_name); \
            tests_failed++; \
        } \
    } while(0)

/* ============================================
   LINKED LIST TESTS
   ============================================ */

void test_create_node() {
    printf("\n=== Testing create_node ===\n");
    
    int value = 42;
    Node* node = create_node(&value, sizeof(int));
    
    TEST_ASSERT(node != NULL, "Node creation succeeds");
    TEST_ASSERT(node->element_size == sizeof(int), "Element size is correct");
    TEST_ASSERT(*(int*)node->data == 42, "Node data is correct");
    TEST_ASSERT(node->next == NULL, "Node next pointer is NULL");
    
    free(node->data);
    free(node);
}

void test_push_back() {
    printf("\n=== Testing push_back ===\n");
    
    int val1 = 10;
    int val2 = 20;
    int val3 = 30;
    
    Node* head = create_node(&val1, sizeof(int));
    head = push_back(head, &val2);
    head = push_back(head, &val3);
    
    TEST_ASSERT(*(int*)head->data == 10, "First element is correct");
    TEST_ASSERT(*(int*)head->next->data == 20, "Second element is correct");
    TEST_ASSERT(*(int*)head->next->next->data == 30, "Third element is correct");
    
    /* Clean up */
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp->data);
        free(temp);
    }
}

void test_push_front() {
    printf("\n=== Testing push_front ===\n");
    
    int val1 = 10;
    int val2 = 20;
    int val3 = 30;
    
    Node* head = create_node(&val1, sizeof(int));
    push_front(&head, &val2);
    push_front(&head, &val3);
    
    TEST_ASSERT(*(int*)head->data == 30, "First element after push_front is correct");
    TEST_ASSERT(*(int*)head->next->data == 20, "Second element after push_front is correct");
    TEST_ASSERT(*(int*)head->next->next->data == 10, "Third element after push_front is correct");
    
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp->data);
        free(temp);
    }
}

/* ============================================
   DYNAMIC ARRAY TESTS
   ============================================ */

void test_array_init() {
    printf("\n=== Testing array_init ===\n");
    
    Array* arr = array_init(sizeof(int), 5);
    
    TEST_ASSERT(arr != NULL, "Array initialization succeeds");
    TEST_ASSERT(arr->size == 0, "Initial size is 0");
    TEST_ASSERT(arr->capacity == 5, "Initial capacity is correct");
    TEST_ASSERT(arr->element_size == sizeof(int), "Element size is correct");
    TEST_ASSERT(arr->status_err == 0, "Status error is 0");
    
    array_free(arr);
}

void test_array_push() {
    printf("\n=== Testing array_push ===\n");
    
    Array* arr = array_init(sizeof(int), 2);
    
    int val1 = 100;
    int val2 = 200;
    int val3 = 300;
    
    TEST_ASSERT(array_push(arr, &val1) == 0, "First push succeeds");
    TEST_ASSERT(array_push(arr, &val2) == 0, "Second push succeeds");
    TEST_ASSERT(array_push(arr, &val3) == 0, "Third push (triggers realloc) succeeds");
    
    TEST_ASSERT(arr->size == 3, "Size after three pushes is correct");
    TEST_ASSERT(arr->capacity == 4, "Capacity doubled after exceeding initial capacity");
    
    array_free(arr);
}

void test_array_get() {
    printf("\n=== Testing array_get ===\n");
    
    Array* arr = array_init(sizeof(int), 5);
    
    int values[] = {10, 20, 30, 40, 50};
    for (int i = 0; i < 5; i++) {
        array_push(arr, &values[i]);
    }
    
    TEST_ASSERT(*(int*)array_get(arr, 0) == 10, "Get element at index 0");
    TEST_ASSERT(*(int*)array_get(arr, 2) == 30, "Get element at index 2");
    TEST_ASSERT(*(int*)array_get(arr, 4) == 50, "Get element at index 4");
    TEST_ASSERT(array_get(arr, 10) == NULL, "Get out of bounds returns NULL");
    
    array_free(arr);
}

void test_get_int() {
    printf("\n=== Testing get_int ===\n");
    
    Array* arr = array_init(sizeof(int), 3);
    
    int val1 = 123;
    int val2 = 456;
    
    array_push(arr, &val1);
    array_push(arr, &val2);
    
    TEST_ASSERT(get_int(arr, 0) == 123, "get_int returns correct value at index 0");
    TEST_ASSERT(get_int(arr, 1) == 456, "get_int returns correct value at index 1");
    
    array_free(arr);
}

/* ============================================
   STRING UTILITY TESTS
   ============================================ */

void test_str_equal() {
    printf("\n=== Testing str_equal ===\n");
    
    const char* s1 = "hello";
    const char* s2 = "hello";
    const char* s3 = "world";
    
    TEST_ASSERT(str_equal(s1, s2) == 0, "Equal strings return 0");
    TEST_ASSERT(str_equal(s1, s3) != 0, "Different strings return non-zero");
}

void test_str_len() {
    printf("\n=== Testing str_len ===\n");
    
    TEST_ASSERT(str_len("hello") == 5, "Length of 'hello' is 5");
    TEST_ASSERT(str_len("") == 0, "Length of empty string is 0");
    TEST_ASSERT(str_len("test string") == 11, "Length of 'test string' is 11");
}

void test_str_copy() {
    printf("\n=== Testing str_copy ===\n");
    
    char dest[20] = "";
    const char* src = "testing";
    
    str_copy(dest, src);
    
    TEST_ASSERT(strcmp(dest, "testing") == 0, "String copied correctly");
}

void test_str_chr() {
    printf("\n=== Testing str_chr ===\n");
    
    const char* str = "hello world";
    char* result = str_chr(str, 'w');
    
    TEST_ASSERT(result != NULL, "Character found in string");
    TEST_ASSERT(*result == 'w', "Correct character returned");
    
    char* not_found = str_chr(str, 'z');
    TEST_ASSERT(*not_found == '\0', "Character not found returns end of string");
}

void test_str_cat() {
    printf("\n=== Testing str_cat ===\n");
    
    char dest[50] = "Hello ";
    const char* src = "World";
    
    str_cat(dest, src);
    
    TEST_ASSERT(strcmp(dest, "Hello World") == 0, "Strings concatenated correctly");
}

void test_str_clone() {
    printf("\n=== Testing str_clone ===\n");
    
    const char* original = "clone me";
    char* clone = str_clone(original);
    
    TEST_ASSERT(clone != NULL, "Clone created successfully");
    TEST_ASSERT(strcmp(clone, original) == 0, "Clone content matches original");
    TEST_ASSERT(clone != original, "Clone is at different memory address");
    
    free(clone);
}

/* ============================================
   FILE I/O TESTS
   ============================================ */

void test_read_file() {
    printf("\n=== Testing read_file ===\n");
    
    /* Create a test file */
    char* content = read_file("Hello.txt");
    
    printf("%s", content);

    TEST_ASSERT(content != NULL, "File read successfully");
    TEST_ASSERT(strlen(content) > 0, "File content is not empty");
    
    
    free(content);
    remove("Hello2.txt");
}

/* ============================================
   MAIN TEST RUNNER
   ============================================ */

int main() {
    printf("\n");
    printf("==========================================\n");
    printf("    CS67 Library Test Suite\n");
    printf("==========================================\n");
    
    /* Run all tests */
    test_create_node();
    test_push_back();
    test_push_front();
    
    test_array_init();
    test_array_push();
    test_array_get();
    test_get_int();
    
    test_str_equal();
    test_str_len();
    test_str_copy();
    test_str_chr();
    test_str_cat();
    test_str_clone();
    
    test_read_file();
    
    /* Print summary */
    printf("\n");
    printf("==========================================\n");
    printf("    Test Results\n");
    printf("==========================================\n");
    printf("Tests Passed: %d\n", tests_passed);
    printf("Tests Failed: %d\n", tests_failed);
    printf("Total Tests:  %d\n", tests_passed + tests_failed);
    printf("==========================================\n\n");
    
    return tests_failed > 0 ? 1 : 0;
}
