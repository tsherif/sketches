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

bool _priv_hash_strEquals(const char* s1, const char* s2) {
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

hash_table hash_create() {
    return (hash_table) {
        .entries = calloc(32, sizeof(hash_entry)),
        .capacity = 32
    };
}

void hash_set(hash_table* h, const char* key, int value) {
    uint64_t hash = fnv1aHash(key);
    size_t index = hash & (h->capacity - 1);

    hash_entry *e = h->entries + index;

    while (e->key != 0 && !_priv_hash_strEquals(e->key, key)) {
        index = (index + 1) & (h->capacity - 1);
        e = h->entries + index;
    }

    if (e->key) {
        e->value = value;
    } else {
        size_t keyLen = 0;
        const char* cur = key;

        while (*cur) {
            ++keyLen;
            ++cur;
        }

        e->key = malloc(keyLen + 1);
        memcpy(e->key, key, keyLen + 1);
        
        e->value = value;
        e->hash = hash;
        ++h->size;

        if (h->size > h->capacity / 2) {
            size_t newCapacity = h->capacity * 2;
            hash_entry* newEntries = calloc(newCapacity, sizeof(hash_entry));
            for (size_t i = 0; i < h->capacity; ++i) {
                hash_entry *oldEntry = h->entries + i;
                if (oldEntry->key) {
                    size_t newIndex = oldEntry->hash & (newCapacity - 1);
                    hash_entry* newEntry = newEntries + newIndex;
                    while (newEntry->key != 0 && !_priv_hash_strEquals(newEntry->key, key)) {
                        newIndex = (newIndex + 1) & (newCapacity - 1);
                        newEntry = newEntries + newIndex;
                    }
                    *newEntry = *oldEntry;
                }
                
            }
            h->capacity = newCapacity;
            h->entries = newEntries;
        }
    }
}

int hash_get(hash_table* h, const char* key) {
    uint64_t hash = fnv1aHash(key);
    size_t index = hash & (h->capacity - 1);

    hash_entry *e = h->entries + index;
    size_t probeLength = 0;
    while (e->key && !_priv_hash_strEquals(e->key, key)) {
        index = (index + 1) & (h->capacity - 1);
        e = h->entries + index;
        ++probeLength;
    }

    if (probeLength > 0) {
        printf("####Probe length: %zd\n", probeLength);
    }

    return e->value;
}