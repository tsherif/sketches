#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#ifndef IMPLEMENTATION_ONLY

#include "macros.h"

#ifndef CONTAINER
#define CONTAINER CONCAT(CONCAT(CONCAT(Map_, KEY_TYPE), _), TYPE)
#endif

typedef struct {
    KEY_TYPE key;
    TYPE value;
    uint64_t hash;
    bool active;
} PRIVATE(_entry);

typedef struct {
    PRIVATE(_entry)* entries;
    size_t size;
    size_t capacity;
} CONTAINER;

CONTAINER METHOD(_create)(void);
void METHOD(_set)(CONTAINER* h, KEY_TYPE key, TYPE value);
TYPE METHOD(_get)(CONTAINER* h, KEY_TYPE key);
void METHOD(_clear)(CONTAINER* h);
size_t METHOD(_size)(CONTAINER* h);
bool METHOD(_empty)(CONTAINER* h);
void METHOD(_destroy)(CONTAINER* h);

#endif


#if defined(IMPLEMENTATION) || defined(IMPLEMENTATION_ONLY)

#include <malloc.h>
#include <string.h>

#ifndef INITIAL_SIZE
#define INITIAL_SIZE 32
#endif

uint64_t PRIVATE(_fnv1aHash)(void* key, size_t len) {
    const char* curr = key;
    uint64_t hash = 0x00000100000001B3ULL;

    for (size_t i = 0; i < len; ++i) {
        hash ^= (uint64_t) curr[i];
        hash *= 0xcbf29ce484222325ULL;
    }

    return hash;
}

void PRIVATE(_extend)(CONTAINER* h) {
    size_t newCapacity = h->capacity * 2;
    PRIVATE(_entry)* newEntries = calloc(newCapacity, sizeof(PRIVATE(_entry)));
    for (size_t i = 0; i < h->capacity; ++i) {
        PRIVATE(_entry) *oldEntry = h->entries + i;
        if (oldEntry->active) {
            size_t mask = newCapacity - 1;
            size_t newIndex = oldEntry->hash & mask;
            PRIVATE(_entry)* newEntry = newEntries + newIndex;
            while (newEntry->active && newEntry->key != oldEntry->key) {
                newIndex = (newIndex + 1) & mask;
                newEntry = newEntries + newIndex;
            }
            *newEntry = *oldEntry;
        }
        
    }
    free(h->entries);
    h->capacity = newCapacity;
    h->entries = newEntries;
}

size_t PRIVATE(_probe)(CONTAINER* h, KEY_TYPE key, uint64_t hash) {
    size_t mask = h->capacity - 1;
    
    size_t index = hash & mask;

    PRIVATE(_entry) *e = h->entries + index;
    while (e->active && e->key != key) {
        index = (index + 1) & mask;
        e = h->entries + index;
    }

    return index;
}

CONTAINER METHOD(_create)(void) {
    return (CONTAINER) {
        .entries = calloc(INITIAL_SIZE, sizeof(PRIVATE(_entry))),
        .capacity = INITIAL_SIZE,
    };
}

void METHOD(_set)(CONTAINER* h, KEY_TYPE key, TYPE value) {
    uint64_t hash = PRIVATE(_fnv1aHash)(&key, sizeof(key));
    PRIVATE(_entry)* e = h->entries + PRIVATE(_probe)(h, key, hash);

    e->key = key;
    e->value = value;
    e->hash = hash;

    if (!e->active) {
        e->active = true;
        ++h->size;
        if (h->size > h->capacity / 2) {
            PRIVATE(_extend)(h);
        }
    }
}

TYPE METHOD(_get)(CONTAINER* h, KEY_TYPE key) {
    uint64_t hash = PRIVATE(_fnv1aHash)(&key, sizeof(key));
    PRIVATE(_entry)* e = h->entries + PRIVATE(_probe)(h, key, hash);

    return e->value;
}

size_t METHOD(_size)(CONTAINER* h) {
    return h->size;
}

bool METHOD(_empty)(CONTAINER* h) {
    return h->size == 0;
}

void METHOD(_clear)(CONTAINER* h) {
    h->size = 0;
}

void METHOD(_destroy)(CONTAINER* h) {
    if (h->entries) {
        free(h->entries);
    }
    h->entries = 0;
    h->capacity = 0;
    h->size = 0;
}

#endif

#undef IMPLEMENTATION
#undef CONTAINER
#undef KEY_TYPE
#undef TYPE
