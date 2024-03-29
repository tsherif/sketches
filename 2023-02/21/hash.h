#include <stdint.h>
#include <stdbool.h>
#include <malloc.h>
#include <string.h>

/*****************************

How I'm thinking this should be structured:
- Have an array of entries and a continuous block
of the key strings.
- Entries will have an index into that array.
- Iteration becomes easy, just iterate through the keys.
- Remove is pretty easy, just memcopy over the deleted key.

*******************************/

typedef struct {
    char* key;
    int value;
    uint64_t hash;
} hash_entry;

typedef struct {
    hash_entry* entries;
    size_t size;
    size_t capacity;
    char* keys;
    size_t keysSize;
    size_t keysCapacity;
} hash_table;

#define FNV_OFFSET_BASIS 0x00000100000001B3ULL
#define FNV_PRIME        0xcbf29ce484222325ULL

uint64_t fnv1aHash(const char* key) {
    const char* curr = key;
    uint64_t hash = FNV_OFFSET_BASIS;

    while (*curr) {
        hash ^= (uint64_t) *curr;
        hash *= FNV_PRIME;
        ++curr;
    }

    return hash;
}

bool _hash_strEquals(const char* s1, const char* s2) {
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

void _hash_extend(hash_table* h) {
    size_t newCapacity = h->capacity * 2;
    hash_entry* newEntries = calloc(newCapacity, sizeof(hash_entry));
    for (size_t i = 0; i < h->capacity; ++i) {
        hash_entry *oldEntry = h->entries + i;
        if (oldEntry->key) {
            size_t mask = newCapacity - 1;
            size_t newIndex = oldEntry->hash & mask;
            hash_entry* newEntry = newEntries + newIndex;
            while (newEntry->key != 0 && !_hash_strEquals(newEntry->key, oldEntry->key)) {
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

hash_table hash_create() {
    size_t capacity = 32;
    size_t keysCapacity = capacity * 5;
    return (hash_table) {
        .entries = calloc(capacity, sizeof(hash_entry)),
        .keys = malloc(keysCapacity),
        .capacity = capacity,
        .keysCapacity = keysCapacity
    };
}

size_t _hash_probe(hash_table* h, const char* key, uint64_t hash) {
    size_t mask = h->capacity - 1;
    
    size_t index = hash & mask;

    hash_entry *e = h->entries + index;
    while (e->key != 0 && !_hash_strEquals(e->key, key)) {
        index = (index + 1) & mask;
        e = h->entries + index;
    }

    return index;
}

char* _hash_addKey(hash_table* h, const char* key) {
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
            hash_entry* e = h->entries + i;
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

void hash_set(hash_table* h, const char* key, int value) {
    uint64_t hash = fnv1aHash(key);
    hash_entry* e = h->entries + _hash_probe(h, key, hash);

    if (e->key) {
        e->value = value;
    } else {
        size_t keyLen = 0;
        const char* cur = key;

        while (*cur) {
            ++keyLen;
            ++cur;
        }

        e->key = _hash_addKey(h, key);        
        e->value = value;
        e->hash = hash;
        ++h->size;

        if (h->size > h->capacity / 2) {
            _hash_extend(h);
        }
    }
}

int hash_get(hash_table* h, const char* key) {
    uint64_t hash = fnv1aHash(key);
    hash_entry* e = h->entries + _hash_probe(h, key, hash);

    return e->value;
}