#include <stdio.h>

#include "hash.h"

#define TYPE int
#include "vector.h"

typedef struct {
    int a;
    double b;
} test;

#define TYPE test
#include "vector.h"

#define TYPE int
#include "stack.h"

void main(void) {
    vector_int v = vector_int_create();

    for (uint32_t i = 0; i < 50; ++i) {
        vector_int_append(&v, i);
    }

    for (uint32_t i = 0; i < vector_int_size(&v); ++i) {
        printf("Vector int: %d\n", vector_int_get(&v, i));
    }

    vector_test tv = vector_test_create();
    vector_test_append(&tv, (test) {
        .a = 5,
        .b = 2.0   
    });

    vector_test_append(&tv, (test) {
        .a = 7,
        .b = 1.0   
    });

    vector_test_append(&tv, (test) {
        .a = 6,
        .b = 14.0   
    });

    for (uint32_t i = 0; i < vector_test_size(&tv); ++i) {
        test current = vector_test_get(&tv, i);
        printf("Vector test: %d -- %f\n", current.a, current.b);
    }

    stack_int si = stack_int_create();

    for (uint32_t i = 0; i < 50; ++i) {
        stack_int_push(&si, 2 * i);
    }
    

    while (!stack_int_empty(&si)) {
        printf("Stack int: %d\n", stack_int_pop(&si));
    }

    printf("ul: %zu\n", sizeof(0x00000100000001B3));
    printf("ull: %zu\n", sizeof(unsigned long long));

    printf("%llu\n", fnv1aHash("hello", sizeof("hello") - 1));
    printf("%llu\n", fnv1aHash("goodby", sizeof("goodby") - 1));

    hash_table h = hash_create();
    hash_set(&h, "hello", 5);
    hash_set(&h, "goodbye", 7);

    printf("Hash get: %d\n", hash_get(&h, "hello"));
    printf("Hash get: %d\n", hash_get(&h, "goodbye"));

    for (uint32_t i = 0; i < h.capacity; ++i) {
        if (h.entries[i].key) {
            printf("%d: %s -- %d\n", i, h.entries[i].key, h.entries[i].value);
        }
    }   
} 