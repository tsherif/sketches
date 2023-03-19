#ifndef IMPLEMENTATION_ONLY

#include <stddef.h>
#include <stdint.h>

#include "macros.h"

#ifndef CONTAINER
#define CONTAINER CONCAT(Vector_, TYPE)
#endif

typedef struct {
    TYPE* data;
    size_t size;
    size_t capacity;
} CONTAINER;

CONTAINER METHOD(_create)(void);
void METHOD(_push)(CONTAINER* v,  TYPE value);
TYPE METHOD(_pop)(CONTAINER* v);
TYPE METHOD(_get)(CONTAINER* v, size_t i);
void METHOD(_set)(CONTAINER* v, size_t i, TYPE value);
size_t METHOD(_size)(CONTAINER* v);
bool METHOD(_empty)(CONTAINER* v);
void METHOD(_clear)(CONTAINER* v);
void METHOD(_destroy)(CONTAINER* v);

#endif


#if defined(IMPLEMENTATION) || defined(IMPLEMENTATION_ONLY)

#include <malloc.h>
#include <string.h>

#ifndef INITIAL_SIZE
#define INITIAL_SIZE 32
#endif


CONTAINER METHOD(_create)(void) {
    return (CONTAINER) {
        .data = malloc(INITIAL_SIZE * sizeof(TYPE)),
        .capacity = INITIAL_SIZE
    };
}

void METHOD(_push)(CONTAINER* v,  TYPE value) {
    if (v->size == v->capacity) {
        TYPE* newData = malloc(v->capacity * 2 * sizeof(TYPE));
        memcpy(newData, v->data, v->capacity * sizeof(TYPE));
        free(v->data);
        v->data = newData;
        v->capacity *= 2;
    }

    v->data[v->size++] = value;
}

TYPE METHOD(_pop)(CONTAINER* v) {
    if (v->size == 0) {
        return (*((TYPE[1]) { 0 }));
    }

    --v->size;
    return v->data[v->size];
}

TYPE METHOD(_get)(CONTAINER* v, size_t i) {
    return v->data[i];
}

void METHOD(_set)(CONTAINER* v, size_t i, TYPE value) {
    v->data[i] = value;
}

size_t METHOD(_size)(CONTAINER* v) {
    return v->size;
}

bool METHOD(_empty)(CONTAINER* v) {
    return v->size == 0;
}

void METHOD(_clear)(CONTAINER* v) {
    v->size = 0;
}

void METHOD(_destroy)(CONTAINER* v) {
    if (v->data) {
        free(v->data);
    }
    v->data = 0;
    v->size = 0;
    v->capacity = 0;
}

#endif

#undef IMPLEMENTATION
#undef CONTAINER
#undef TYPE