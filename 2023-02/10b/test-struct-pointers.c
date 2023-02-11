#include <stdio.h>

typedef struct {
    int* pi;
} Test;

int main(void) {
    int i = 5;

    Test test = {
        .pi = &i
    };

    printf("Value is: %d\n", *test.pi);

    return 0;
}