#include <stdint.h>
#include <malloc.h>
#include <string.h>

#define CONTAINER_PREFIX vector_
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

void METHOD(_append)(CONTAINER* v,  TYPE value) {
    if (v->size == v->capacity) {
        TYPE* newData = malloc(v->capacity * 2 * sizeof(TYPE));
        memcpy(newData, v->data, v->capacity * sizeof(TYPE));
        free(v->data);
        v->data = newData;
        v->capacity *= 2;
    }

    v->data[v->size++] = value;
}

TYPE METHOD(_get)(CONTAINER* v, uint32_t i) {
    return v->data[i];
}

void METHOD(_set)(CONTAINER* v, uint32_t i, TYPE value) {
    v->data[i] = value;
}

uint32_t METHOD(_size)(CONTAINER* v) {
    return v->size;
}

#undef CONTAINER_PREFIX
#undef TYPE