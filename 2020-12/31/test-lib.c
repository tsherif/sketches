#include <stdio.h>

extern void undefinedFn();

void fn1() {
    printf("Hello SO1!\n");
}

void fn2() {
    printf("Hello SO2!\n");
    undefinedFn();
}
