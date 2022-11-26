// Testing how array arguments work in C. 
// Result: They don't add any additional constraints
// on what can be passed.

#include <stdio.h>

int test(int p1[2], int p2[2]) {
    return p1[0] + p2[4];
}

int main() {
    int a1[] = {1, 2, 3, 4};
    int a2[] = {5, 6, 7, 8};

    printf("Result: %d\n", a1[5]);

    return 0;
}