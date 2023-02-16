#include <stdio.h>

#define TYPE int
#include "vector.h"

typedef struct {
    int a;
    double b;
} test;

#define TYPE test
#include "vector.h"

void main(void) {
    vector_int v = vector_int_create();
    vector_int_append(&v, 1);
    vector_int_append(&v, 7);
    vector_int_append(&v, 2);
    vector_int_append(&v, 3);

    for (uint32_t i = 0; i < vector_int_length(&v); ++i) {
        printf("%d\n", vector_int_get(&v, i));
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

    for (uint32_t i = 0; i < vector_test_length(&tv); ++i) {
        test current = vector_test_get(&tv, i);
        printf("%d -- %f\n", current.a, current.b);
    }
} 