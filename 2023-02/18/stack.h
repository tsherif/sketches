#include <stdint.h>
#include <stdbool.h>
#include <malloc.h>
#include <string.h>

#define CONTAINER_PREFIX stack_
#include "macros.h"

#ifndef INITIAL_SIZE
#define INITIAL_SIZE 32
#endif

typedef struct {
    TYPE* data;
    uint32_t size;
    uint32_t capacity;
} CONTAINER;

CONTAINER METHOD(_create)(void) {
    return (CONTAINER) {
        .data = malloc(INITIAL_SIZE * sizeof(TYPE)),
        .capacity = INITIAL_SIZE
    };
}

void METHOD(_push)(CONTAINER* s,  TYPE value) {
    if (s->size == s->capacity) {
        TYPE* newData = malloc(s->capacity * 2 * sizeof(TYPE));
        memcpy(newData, s->data, s->capacity * sizeof(TYPE));
        s->data = newData;
        s->capacity *= 2;
    }

    s->data[s->size++] = value;
}

TYPE METHOD(_pop)(CONTAINER* s) {
    return s->data[--s->size];
}

TYPE METHOD(_peek)(CONTAINER* s) {
    return s->data[s->size - 1];
}

uint32_t METHOD(_size)(CONTAINER* s) {
    return s->size;
}

bool METHOD(_empty)(CONTAINER* s) {
    return s->size == 0;
}

#undef CONTAINER_PREFIX
#undef TYPE
#undef INITIAL_SIZE