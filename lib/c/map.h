#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#define CONTAINER_PREFIX Map_
#include "macros.h"

#ifndef CONTAINER
#define CONTAINER CONCAT(CONCAT(CONCAT(Map_, KEY_TYPE), _), TYPE)
#endif


typedef struct {
    KEY_TYPE key;
    TYPE value;
    uint64_t hash;
    bool active;
} MAP_PRIVATE(_entry);

typedef struct {
    MAP_PRIVATE(_entry)* entries;
    size_t size;
    size_t capacity;
} MAP_CONTAINER;

MAP_CONTAINER MAP_METHOD(_create)(void);
void MAP_METHOD(_set)(MAP_CONTAINER* h, KEY_TYPE key, TYPE value);
TYPE MAP_METHOD(_get)(MAP_CONTAINER* h, KEY_TYPE key);
void MAP_METHOD(_clear)(MAP_CONTAINER* h);
size_t MAP_METHOD(_size)(MAP_CONTAINER* h);
bool MAP_METHOD(_empty)(MAP_CONTAINER* h);
void MAP_METHOD(_destroy)(MAP_CONTAINER* h);

#ifdef IMPLEMENTATION

#include <malloc.h>
#include <string.h>

#ifndef INITIAL_SIZE
#define INITIAL_SIZE 32
#endif

uint64_t MAP_PRIVATE(_fnv1aHash)(void* key, size_t len) {
    const char* curr = key;
    uint64_t hash = 0x00000100000001B3ULL;

    for (size_t i = 0; i < len; ++i) {
        hash ^= (uint64_t) curr[i];
        hash *= 0xcbf29ce484222325ULL;
    }

    return hash;
}

void MAP_PRIVATE(_extend)(MAP_CONTAINER* h) {
    size_t newCapacity = h->capacity * 2;
    MAP_PRIVATE(_entry)* newEntries = calloc(newCapacity, sizeof(MAP_PRIVATE(_entry)));
    for (size_t i = 0; i < h->capacity; ++i) {
        MAP_PRIVATE(_entry) *oldEntry = h->entries + i;
        if (oldEntry->active) {
            size_t mask = newCapacity - 1;
            size_t newIndex = oldEntry->hash & mask;
            MAP_PRIVATE(_entry)* newEntry = newEntries + newIndex;
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

size_t MAP_PRIVATE(_probe)(MAP_CONTAINER* h, KEY_TYPE key, uint64_t hash) {
    size_t mask = h->capacity - 1;
    
    size_t index = hash & mask;

    MAP_PRIVATE(_entry) *e = h->entries + index;
    while (e->active && e->key != key) {
        index = (index + 1) & mask;
        e = h->entries + index;
    }

    return index;
}

MAP_CONTAINER MAP_METHOD(_create)(void) {
    return (MAP_CONTAINER) {
        .entries = calloc(INITIAL_SIZE, sizeof(MAP_PRIVATE(_entry))),
        .capacity = INITIAL_SIZE,
    };
}

void MAP_METHOD(_set)(MAP_CONTAINER* h, KEY_TYPE key, TYPE value) {
    uint64_t hash = MAP_PRIVATE(_fnv1aHash)(&key, sizeof(key));
    MAP_PRIVATE(_entry)* e = h->entries + MAP_PRIVATE(_probe)(h, key, hash);

    e->key = key;
    e->value = value;
    e->hash = hash;

    if (!e->active) {
        e->active = true;
        ++h->size;
        if (h->size > h->capacity / 2) {
            MAP_PRIVATE(_extend)(h);
        }
    }
}

TYPE MAP_METHOD(_get)(MAP_CONTAINER* h, KEY_TYPE key) {
    uint64_t hash = MAP_PRIVATE(_fnv1aHash)(&key, sizeof(key));
    MAP_PRIVATE(_entry)* e = h->entries + MAP_PRIVATE(_probe)(h, key, hash);

    return e->value;
}

size_t MAP_METHOD(_size)(MAP_CONTAINER* h) {
    return h->size;
}

bool MAP_METHOD(_empty)(MAP_CONTAINER* h) {
    return h->size == 0;
}

void MAP_METHOD(_clear)(MAP_CONTAINER* h) {
    h->size = 0;
}

void MAP_METHOD(_destroy)(MAP_CONTAINER* h) {
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
