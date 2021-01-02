#include <stdio.h>
#include <math.h>

float value = 4.0f;

void fn1() {
    fprintf(stderr, "Hello from fn1! The square root of %.1f is %.1f!\n", value, sqrt(value));
}

void fn2() {
    fprintf(stderr, "Hello from f2! The floor of %.1f is %.1f!\n", value, floor(value));
}
