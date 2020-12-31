#include <dlfcn.h>
#include <stdio.h>

typedef void (*voidFunc)();

int main() {
    void *testLib = dlopen("./libtest-lib.so", RTLD_NOW);
    
    if (!testLib) {
        fprintf(stderr, "Failed to load test-lib!\n");
        return 1;
    }

    voidFunc fn1 = dlsym(testLib, "fn1");
    voidFunc fn2 = dlsym(testLib, "fn2");
    
    fn1();

    return 0;
};
