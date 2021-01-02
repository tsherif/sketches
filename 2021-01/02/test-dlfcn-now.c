#include <dlfcn.h>
#include <stdio.h>

typedef void (*voidFunc)();

int main() {
    fprintf(stderr, "Before dlopen(RTLD_NOW)\n");
    void *testLib = dlopen("./libtest-lib.so", RTLD_NOW);
    fprintf(stderr, "After dlopen(RTLD_NOW)\n");
    
    if (!testLib) {
        fprintf(stderr, "Failed to load test-lib!\n");
        return 1;
    }

    fprintf(stderr, "Before dlsym(fn1)\n");
    voidFunc fn1 = dlsym(testLib, "fn1");
    fprintf(stderr, "Before dlsym(fn2)\n");
    voidFunc fn2 = dlsym(testLib, "fn2");
    fprintf(stderr, "After dlsym\n");
    
    fprintf(stderr, "Before first call fn1()\n");
    fn1();
    fprintf(stderr, "Before second call fn1()\n");
    fn1();
    fprintf(stderr, "After fn1()\n");

    return 0;
};
