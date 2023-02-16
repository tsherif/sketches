#include <stdint.h>
#include <malloc.h>
#include <string.h>

#ifndef CONCAT
#define CONCAT(a, b) a##b
#endif

#ifndef APPEND_SUFFIX
#define APPEND_SUFFIX(type, suffix) CONCAT(type, suffix)
#endif

typedef struct {
    VECTOR_TYPE* data;
    uint32_t length;
    uint32_t capacity;
} APPEND_SUFFIX(VECTOR_TYPE, _vector);

APPEND_SUFFIX(VECTOR_TYPE, _vector) APPEND_SUFFIX(VECTOR_TYPE, _vector_create)(void) {
    return (APPEND_SUFFIX(VECTOR_TYPE, _vector)) {
        .data = malloc(32 * sizeof(VECTOR_TYPE)),
        .capacity = 32
    };
}

void APPEND_SUFFIX(VECTOR_TYPE, _vector_append)(APPEND_SUFFIX(VECTOR_TYPE, _vector)* v,  VECTOR_TYPE value) {
    if (v->length == v->capacity) {
        VECTOR_TYPE* newData = malloc(v->capacity * 2 * sizeof(VECTOR_TYPE));
        memcpy(newData, v->data, v->capacity * sizeof(VECTOR_TYPE));
        v->data = newData;
        v->capacity *= 2;
    }

    v->data[v->length++] = value;
}

VECTOR_TYPE APPEND_SUFFIX(VECTOR_TYPE, _vector_get)(APPEND_SUFFIX(VECTOR_TYPE, _vector)* v, uint32_t i) {
    return v->data[i];
}

void APPEND_SUFFIX(VECTOR_TYPE, _vector_set)(APPEND_SUFFIX(VECTOR_TYPE, _vector)* v, uint32_t i, VECTOR_TYPE value) {
    v->data[i] = value;
}

uint32_t APPEND_SUFFIX(VECTOR_TYPE, _vector_length)(APPEND_SUFFIX(VECTOR_TYPE, _vector)* v) {
    return v->length;
}

#undef VECTOR_TYPE