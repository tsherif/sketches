#include <dlfcn.h>
#include <stdio.h>

extern void fn1();
extern void fn2();

int main() {
    fprintf(stderr, "Before fn1()\n");
    fn1();
    fprintf(stderr, "After fn1()\n");

    return 0;
};
