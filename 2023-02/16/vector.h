#include <stdint.h>
#include <malloc.h>
#include <string.h>

#ifndef CONCAT
#define CONCAT(a, b) a##b
#endif

#ifndef PREFIX
#define PREFIX(prefix, name) CONCAT(prefix, name)
#endif

#ifndef SUFFIX
#define SUFFIX(name, suffix) CONCAT(name, suffix)
#endif

#define CONTAINER PREFIX(vector_, TYPE)
#define METHOD(name) SUFFIX(CONTAINER, name)

typedef struct {
    TYPE* data;
    uint32_t length;
    uint32_t capacity;
} CONTAINER;

CONTAINER METHOD(_create)(void) {
    return (CONTAINER) {
        .data = malloc(32 * sizeof(TYPE)),
        .capacity = 32
    };
}

void METHOD(_append)(CONTAINER* v,  TYPE value) {
    if (v->length == v->capacity) {
        TYPE* newData = malloc(v->capacity * 2 * sizeof(TYPE));
        memcpy(newData, v->data, v->capacity * sizeof(TYPE));
        v->data = newData;
        v->capacity *= 2;
    }

    v->data[v->length++] = value;
}

TYPE METHOD(_get)(CONTAINER* v, uint32_t i) {
    return v->data[i];
}

void METHOD(_set)(CONTAINER* v, uint32_t i, TYPE value) {
    v->data[i] = value;
}

uint32_t METHOD(_length)(CONTAINER* v) {
    return v->length;
}

#undef TYPE
#undef CONTAINER
#undef METHOD