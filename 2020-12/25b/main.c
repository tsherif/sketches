#include <stdio.h>

extern void (*value)();

int main() {
	printf("Value is: %p\n", value);

	return 0;
}