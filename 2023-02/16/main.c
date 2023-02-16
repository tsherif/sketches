#include <stdio.h>

#define VECTOR_TYPE int
#include "vector.h"

typedef struct {
    int a;
    double b;
} test;

#define VECTOR_TYPE test
#include "vector.h"

void main(void) {
    int_vector v = int_vector_create();
    int_vector_append(&v, 1);
    int_vector_append(&v, 7);
    int_vector_append(&v, 2);
    int_vector_append(&v, 3);

    for (uint32_t i = 0; i < int_vector_length(&v); ++i) {
        printf("%d\n", int_vector_get(&v, i));
    }

    test_vector tv = test_vector_create();
    test_vector_append(&tv, (test) {
        .a = 5,
        .b = 2.0   
    });

    test_vector_append(&tv, (test) {
        .a = 7,
        .b = 1.0   
    });

    test_vector_append(&tv, (test) {
        .a = 6,
        .b = 14.0   
    });

    for (uint32_t i = 0; i < test_vector_length(&tv); ++i) {
        test current = test_vector_get(&tv, i);
        printf("%d -- %f\n", current.a, current.b);
    }
} 