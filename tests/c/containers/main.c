#include <stdio.h>
#include <stdlib.h>

#include "../../../lib/c/guard.h"

#define TYPE int
#define IMPLEMENTATION
#include "../../../lib/c/str-map.h"

#define TYPE int
#define IMPLEMENTATION
#include "../../../lib/c/vector.h"

#define TYPE float
#define CONTAINER MY_VEC
#define IMPLEMENTATION
#include "../../../lib/c/vector.h"

#define KEY_TYPE int
#define TYPE float
#define IMPLEMENTATION
#include "../../../lib/c/map.h"

#define KEY_TYPE float
#define TYPE int
#define CONTAINER MY_MAP
#define IMPLEMENTATION
#include "../../../lib/c/map.h"

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

void expect(bool condition, const char* message) {
    if (!condition) {
        fputs("ERROR: ", stderr);
        fputs(message, stderr);
        fputs("\n", stderr);
        exit(1);
    }
}

void main(void) {
    size_t numWords = sizeof(words) / sizeof(words[0]);

    StrMap_int h = StrMap_int_create();
    
    for (int i = 0; i < numWords; ++i) {
        int val = StrMap_int_get(&h, words[i]);
        StrMap_int_set(&h, words[i], val + 1);
    }

    expect(StrMap_int_get(&h, "in") == 7, "StrMap_int value wrong for in");
    expect(StrMap_int_get(&h, "keyboard") == 4, "StrMap_int value wrong for keyboard");
    expect(StrMap_int_get(&h, "and") == 10, "StrMap_int value wrong for and");

    Vector_int v = Vector_int_create();

    for (int i = 0; i < 100; ++i) {
        Vector_int_push(&v, i);
    }

    for (int i = 0; i < 100; ++i) {
        Vector_int_set(&v, i, Vector_int_get(&v, i) * 2);
    }

    for (size_t i = 0; i < Vector_int_size(&v); ++i) {
        expect(Vector_int_get(&v, i) == i * 2, "Vector_int value wrong on get");
    }

    while (!Vector_int_empty(&v)) {
        size_t expectedValue = (Vector_int_size(&v) - 1) * 2;
        expect(Vector_int_pop(&v) == expectedValue, "Vector_int value wrong on pop");
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
        expect(false, "GUARD_BREAK failed");
    }

    res = failAllocate("RES3");
    GUARD(res, deallocate("RES3", &res)) {
        expect(false, "GUARD failed on failed allocation");
    }

    int res1 = allocate("Nested RES1");
    GUARD(res1, deallocate("Nested RES1", &res1)) {
        printf("Using Nested RES1\n");

        int res2 = allocate("Nested RES2");
        GUARD(res2, deallocate("Nested RES2", &res2)) {
            printf("Using Nested RES2\n");
        }
    }

    Map_int_float m = Map_int_float_create();
    expect(Map_int_float_empty(&m) == true, "Map_int_float should be empty");
    
    Map_int_float_set(&m, 1, 1.5f);    
    Map_int_float_set(&m, 2, 2.5f);    
    Map_int_float_set(&m, 3, 3.5f);    
    Map_int_float_set(&m, 4, 5.5f);    
    Map_int_float_set(&m, 2, 6.5f);    
    Map_int_float_set(&m, 3, 7.5f);    
    Map_int_float_set(&m, 2, 8.5f);    
    Map_int_float_set(&m, 1, 9.5f);

    expect(Map_int_float_size(&m) == 4, "Map_int_float size should be 4");
    expect(m.capacity == 32, "Map_int_float capacity should be 32");

    expect(Map_int_float_get(&m, 4) == 5.5f, "Map_int_float value wrong for 4");    
    expect(Map_int_float_get(&m, 2) == 8.5f, "Map_int_float value wrong for 2");    
    expect(Map_int_float_get(&m, 3) == 7.5f, "Map_int_float value wrong for 3");    


    for (int i = 0; i < 40; ++i) {
        Map_int_float_set(&m, i, i + 0.5f);    
    }
    expect(Map_int_float_size(&m) == 40, "Map_int_float size should be 40");
    expect(m.capacity == 128, "Map_int_float capacity should be 128");

    for (int i = 0; i < 40; ++i) {
        expect(Map_int_float_get(&m, i) == i + 0.5f, "Map_int_float value");  
    }

    Map_int_float_clear(&m);
    expect(Map_int_float_empty(&m) == true, "Map_int_float should be empty after clear");
    expect(Map_int_float_size(&m) == 0, "Map_int_float size should be 0 after clear");

    MY_VEC myv = MY_VEC_create();
    for (int i = 0; i < 50; ++i) {
        MY_VEC_push(&myv, i * 1.5f);
    }

    expect(MY_VEC_size(&myv) == 50, "MY_VEC size should be 50.");

    MY_MAP mym = MY_MAP_create();
    expect( MY_MAP_empty(&mym) == true, "MY_MAP should be empty");

    MY_MAP_set(&mym, 1.5, 1);    
    MY_MAP_set(&mym, 2.5, 2);    
    MY_MAP_set(&mym, 3.5, 3);    
    MY_MAP_set(&mym, 5.5, 4);    
    MY_MAP_set(&mym, 6.5, 2);    
    MY_MAP_set(&mym, 7.5, 3);    
    MY_MAP_set(&mym, 8.5, 2);    
    MY_MAP_set(&mym, 9.5, 1);
    expect(MY_MAP_size(&mym) == 8, "MY_MAP size should be 8.");

    printf("ALL TESTS PASSED!");
} 