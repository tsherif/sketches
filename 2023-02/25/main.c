#include <stdio.h>

#include "guard.h"

#define TYPE int
#define IMPLEMENTATION
#include "hash.h"

#define TYPE int
#define IMPLEMENTATION
#include "vector.h"

const char* words[] = {
    "Development",
    "on",
    "Windows",
    "and",
    "Linux",
    "is",
    "to",
    "a",
    "great",
    "extent",
    "similar",
    "On",
    "Windows",
    "I",
    "use",
    "cl",
    "to",
    "compile",
    "Visual",
    "Studio",
    "2019",
    "to",
    "debug",
    "and",
    "simple",
    "batch",
    "files",
    "as",
    "the",
    "build",
    "system",
    "On",
    "Linux",
    "I",
    "use",
    "gcc",
    "to",
    "compile",
    "gdb",
    "to",
    "debug",
    "make",
    "to",
    "build",
    "The",
    "development",
    "experience",
    "on",
    "Windows",
    "is",
    "generally",
    "smoother",
    "due",
    "to",
    "the",
    "thorough",
    "API",
    "documentation",
    "on",
    "MSDN",
    "and",
    "a",
    "more",
    "pleasant",
    "debugging",
    "experience",
    "with",
    "Visual",
    "Studio",
    "but",
    "Ive",
    "never",
    "had",
    "to",
    "change",
    "any",
    "parts",
    "of",
    "the",
    "design",
    "of",
    "spaceshooterc",
    "to",
    "fit",
    "constraints",
    "on",
    "one",
    "platform",
    "or",
    "the",
    "other",
    "The",
    "Web",
    "on",
    "the",
    "other",
    "hand",
    "brings",
    "with",
    "it",
    "some",
    "challenges",
    "that",
    "werent",
    "present",
    "on",
    "the",
    "native",
    "platforms",
    "I",
    "use",
    "emcc",
    "to",
    "compile",
    "and",
    "make",
    "again",
    "to",
    "build",
    "I",
    "debug",
    "using",
    "Chrome",
    "DevTools",
    "as",
    "described",
    "in",
    "this",
    "blog",
    "post",
    "which",
    "takes",
    "a",
    "few",
    "steps",
    "to",
    "set",
    "up",
    "The",
    "first",
    "is",
    "to",
    "install",
    "the",
    "CC",
    "DevTools",
    "Support",
    "Extension",
    "and",
    "to",
    "enable",
    "WebAssembly",
    "Debugging",
    "Enable",
    "DWARF",
    "support",
    "in",
    "the",
    "DevTools",
    "settings",
    "Additionally",
    "to",
    "ensure",
    "the",
    "extension",
    "could",
    "find",
    "the",
    "files",
    "on",
    "my",
    "system",
    "I",
    "had",
    "to",
    "set",
    "the",
    "compilation",
    "flag",
    "fdebugcompilationdir",
    "ie",
    "the",
    "root",
    "of",
    "the",
    "repository",
    "relative",
    "to",
    "the",
    "build",
    "directory",
    "and",
    "remap",
    "the",
    "file",
    "paths",
    "as",
    "decribed",
    "in",
    "this",
    "bug",
    "report",
    "In",
    "addition",
    "to",
    "the",
    "debugging",
    "challenges",
    "the",
    "Web",
    "involves",
    "constraints",
    "that",
    "required",
    "changes",
    "to",
    "the",
    "control",
    "flow",
    "of",
    "spaceshooterc",
    "the",
    "most",
    "prominent",
    "of",
    "these",
    "being",
    "the",
    "requirement",
    "that",
    "certain",
    "operations",
    "only",
    "be",
    "performed",
    "in",
    "user",
    "input",
    "callbacks",
    "namely",
    "playing",
    "audio",
    "and",
    "entering",
    "fullscreen",
    "mode",
    "This",
    "challenge",
    "is",
    "further",
    "compounded",
    "by",
    "the",
    "fact",
    "that",
    "the",
    "Web",
    "Gamepad",
    "API",
    "uses",
    "a",
    "polling",
    "system",
    "rather",
    "than",
    "events",
    "and",
    "callbacks",
    "meaning",
    "Gamepad",
    "input",
    "as",
    "specced",
    "isnt",
    "considered",
    "user",
    "input",
    "for",
    "the",
    "purpose",
    "of",
    "enabling",
    "the",
    "abovementioned",
    "operations",
    "Chrome",
    "implements",
    "its",
    "own",
    "workaround",
    "for",
    "this",
    "problem",
    "but",
    "since",
    "its",
    "nonstandard",
    "and",
    "not",
    "supported",
    "in",
    "Firefox",
    "I",
    "only",
    "support",
    "toggling",
    "fullscreen",
    "via",
    "the",
    "keyboard",
    "even",
    "if",
    "a",
    "gamepad",
    "is",
    "connected",
    "Furthermore",
    "I",
    "implement",
    "the",
    "logic",
    "to",
    "toggle",
    "fullscreen",
    "directly",
    "in",
    "the",
    "keyboard",
    "input",
    "handler",
    "rather",
    "than",
    "in",
    "the",
    "game",
    "loop",
    "as",
    "is",
    "done",
    "on",
    "the",
    "other",
    "platforms",
    "Finally",
    "to",
    "ensure",
    "audio",
    "is",
    "initialized",
    "correctly",
    "I",
    "implement",
    "a",
    "start",
    "screen",
    "that",
    "only",
    "appears",
    "on",
    "the",
    "Web",
    "and",
    "asks",
    "the",
    "user",
    "for",
    "keyboard",
    "input",
    "to",
    "start",
    "the",
    "game",
    "so",
    "that",
    "it",
    "can",
    "do",
    "so",
    "within",
    "a",
    "keyboard",
    "input",
    "callback"
};

int allocate(const char * res) {
    printf("Allocating: %s\n", res);

    return 1;
}

int failAllocate(const char * res) {
    printf("Failing allocation: %s\n", res);

    return 0;
}

void deallocate(const char * res, int* i) {
    *i = 0;
    printf("Deallocating: %s\n", res);
}

#define TEST(x, y) CONCAT(x, CONCAT(_, y))

void main(void) {
    size_t numWords = sizeof(words) / sizeof(words[0]);

    hash_int h = hash_int_create();
    
    for (int i = 0; i < numWords; ++i) {
        int val = hash_int_get(&h, words[i]);
        hash_int_set(&h, words[i], val + 1);
    }

    printf("{\n");
    for (uint32_t i = 0; i < h.capacity; ++i) {
        if (h.entries[i].key) {
            int count = hash_int_get(&h, h.entries[i].key);
            printf("    \"%s\": %d,\n", h.entries[i].key, count);
        }
    }
    printf("}\n");

    vector_int v = vector_int_create();

    for (int i = 0; i < 100; ++i) {
        vector_int_push(&v, i);
    }

    for (int i = 0; i < 100; ++i) {
        vector_int_set(&v, i, vector_int_get(&v, i) * 2);
    }

    for (size_t i = 0; i < vector_int_size(&v); ++i) {
        printf("vector[%zd]: %d\n", i, vector_int_get(&v, i));
    }

    while (!vector_int_empty(&v)) {
        printf("vector: %d\n", vector_int_pop(&v));
    }

    int res = allocate("RES1");
    GUARD(res, deallocate("RES1", &res)) {
        printf("Using RES1\n");
    }

    res = allocate("RES2");
    GUARD(res, deallocate("RES2", &res)) {
        printf("Using RES2 then breaking\n");
        if (res) {
            GUARD_BREAK;
        }
        printf("SHOULDN'T SEE THIS!!!!!!");
    }

    res = failAllocate("RES3");
    GUARD(res, deallocate("RES3", &res)) {
        printf("SHOULDN'T SEE THIS!!!!!!\n");
    }

    int res1 = allocate("Nested RES1");
    GUARD(res1, deallocate("Nested RES1", &res1)) {
        printf("Using Nested RES1\n");

        int res2 = allocate("Nested RES2");
        GUARD(res2, deallocate("Nested RES2", &res2)) {
            printf("Using Nested RES2\n");
        }
    }
} 