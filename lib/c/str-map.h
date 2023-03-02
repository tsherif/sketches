#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#define CONTAINER_PREFIX StrMap_
#include "macros.h"

typedef struct {
    char* key;
    TYPE value;
    uint64_t hash;
} PRIVATE(_entry);

typedef struct {
    PRIVATE(_entry)* entries;
    size_t size;
    size_t capacity;
    char* keys;
    size_t keysSize;
    size_t keysCapacity;
} CONTAINER;

CONTAINER METHOD(_create)(void);
void METHOD(_set)(CONTAINER* h, const char* key, TYPE value);
TYPE METHOD(_get)(CONTAINER* h, const char* key);
bool METHOD(_has)(CONTAINER* h, const char* key);
void METHOD(_clear)(CONTAINER* h);
size_t METHOD(_size)(CONTAINER* h);
bool METHOD(_empty)(CONTAINER* h);
void METHOD(_destroy)(CONTAINER* h);

#ifdef IMPLEMENTATION

#include <malloc.h>
#include <string.h>

#ifndef INITIAL_SIZE
#define INITIAL_SIZE 32
#endif

uint64_t PRIVATE(_fnv1aHash)(const char* key) {
    const char* curr = key;
    uint64_t hash = 0x00000100000001B3ULL;

    while (*curr) {
        hash ^= (uint64_t) *curr;
        hash *= 0xcbf29ce484222325ULL;
        ++curr;
    }

    return hash;
}

bool PRIVATE(_strEquals)(const char* s1, const char* s2) {
    const char* c1 = s1;
    const char* c2 = s2;

    while (*c1 && *c2) {
        if (*c1 != *c2) {
            return false;
        }
        ++c1;
        ++c2;
    }

    return !*c1 && !*c2;
}

void PRIVATE(_extend)(CONTAINER* h) {
    size_t newCapacity = h->capacity * 2;
    PRIVATE(_entry)* newEntries = calloc(newCapacity, sizeof(PRIVATE(_entry)));
    for (size_t i = 0; i < h->capacity; ++i) {
        PRIVATE(_entry) *oldEntry = h->entries + i;
        if (oldEntry->key) {
            size_t mask = newCapacity - 1;
            size_t newIndex = oldEntry->hash & mask;
            PRIVATE(_entry)* newEntry = newEntries + newIndex;
            while (newEntry->key != 0 && !PRIVATE(_strEquals)(newEntry->key, oldEntry->key)) {
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

size_t PRIVATE(_probe)(CONTAINER* h, const char* key, uint64_t hash) {
    size_t mask = h->capacity - 1;
    
    size_t index = hash & mask;

    PRIVATE(_entry) *e = h->entries + index;
    while (e->key != 0 && !PRIVATE(_strEquals)(e->key, key)) {
        index = (index + 1) & mask;
        e = h->entries + index;
    }

    return index;
}

char* PRIVATE(_addKey)(CONTAINER* h, const char* key) {
    size_t keySize = 1; // Including null terminator
    const char* curr = key;
    while (*curr) {
        ++keySize;
        ++curr;
    }

    if (h->keysSize + keySize > h->keysCapacity) {
        size_t newCapacity = h->keysCapacity * 2;
        char* newKeys = malloc(newCapacity);
        memcpy(newKeys, h->keys, h->keysSize);

        for (size_t i = 0; i < h->capacity; ++i) {
            PRIVATE(_entry)* e = h->entries + i;
            if (e->key) {
                size_t offset = e->key - h->keys;
                e->key = newKeys + offset;
            }
        }

        free(h->keys);
        h->keys = newKeys;
        h->keysCapacity = newCapacity;
    }
    char* keyLoc = h->keys + h->keysSize;
    memcpy(keyLoc, key, keySize);
    h->keysSize += keySize;

    return keyLoc;
}

CONTAINER METHOD(_create)(void) {
    size_t capacity = INITIAL_SIZE;
    size_t keysCapacity = capacity * 8;
    return (CONTAINER) {
        .entries = calloc(capacity, sizeof(PRIVATE(_entry))),
        .keys = malloc(keysCapacity),
        .capacity = capacity,
        .keysCapacity = keysCapacity
    };
}

void METHOD(_set)(CONTAINER* h, const char* key, TYPE value) {
    uint64_t hash = PRIVATE(_fnv1aHash)(key);
    PRIVATE(_entry)* e = h->entries + PRIVATE(_probe)(h, key, hash);

    if (e->key) {
        e->value = value;
    } else {
        size_t keyLen = 0;
        const char* cur = key;

        while (*cur) {
            ++keyLen;
            ++cur;
        }

        e->key = PRIVATE(_addKey)(h, key);        
        e->value = value;
        e->hash = hash;
        ++h->size;

        if (h->size > h->capacity / 2) {
            PRIVATE(_extend)(h);
        }
    }
}

TYPE METHOD(_get)(CONTAINER* h, const char* key) {
    uint64_t hash = PRIVATE(_fnv1aHash)(key);
    PRIVATE(_entry)* e = h->entries + PRIVATE(_probe)(h, key, hash);

    return e->value;
}

bool METHOD(_has)(CONTAINER* h, const char* key) {
    uint64_t hash = PRIVATE(_fnv1aHash)(key);
    PRIVATE(_entry)* e = h->entries + PRIVATE(_probe)(h, key, hash);

    return e->key != 0;
}

size_t METHOD(_size)(CONTAINER* h) {
    return h->size;
}

bool METHOD(_empty)(CONTAINER* h) {
    return h->size == 0;
}

void METHOD(_clear)(CONTAINER* h) {
    h->size = 0;
    h->keysSize = 0;
}

void METHOD(_destroy)(CONTAINER* h) {
    if (h->entries) {
        free(h->entries);
    }
    if (h->keys) {
        free(h->keys);
    }
    h->entries = 0;
    h->keys = 0;
    h->capacity = 0;
    h->keysCapacity = 0;
    h->size = 0;
    h->keysSize = 0;
}

#endif

#undef IMPLEMENTATION
#undef CONTAINER_PREFIX
#undef TYPE
