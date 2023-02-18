#include <stdint.h>
#include <malloc.h>

/*****************************

How I'm thinking this should be structured:
- Have an array of entries and a continuous block
of the key strings.
- Entries will have an index into that array.
- Iteration becomes easy, just iterate through the keys.
- Remove is pretty easy, just memcopy over the deleted key.

*******************************/

typedef struct {
    const char* key;
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

uint64_t fnv1aHash(const char* key, size_t len) {
    uint64_t hash = FNV_OFFSET_BASIS;

    for (size_t i = 0; i < len; ++i) {
        hash ^= (uint64_t) key[i];
        hash *= FNV_PRIME;
    }

    return hash;
}

hash_table hash_create() {
    return (hash_table) {
        .entries = calloc(32, sizeof(hash_entry)),
        .capacity = 32
    };
}

void hash_set(hash_table* h, const char* key, int value) {
    size_t len = 0;
    const char* curr = key;
    while (*curr) {
        ++len;
        ++curr;
    }

    uint64_t hash = fnv1aHash(key, len);
    size_t index = hash & (h->capacity - 1);
    hash_entry *e = h->entries + index;
    e->key = key;
    e->value = value;
    e->hash = hash;
    ++h->size;
}

int hash_get(hash_table* h, const char* key) {
    size_t len = 0;
    const char* curr = key;
    while (*curr) {
        ++len;
        ++curr;
    }

    uint64_t hash = fnv1aHash(key, len);
    size_t index = hash & (h->capacity - 1);
    return h->entries[index].value;
}