#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

long factorial(long n) {
	if (n < 0) {
		return 0;
	} 

	long fact = 1;

	while (n > 1) {
		fact *= n;
		n--;
	}

	return fact;
}

long fibonacci(long n) {
	if (n < 1) {
		return 0;
	}
	if (n < 3) {
		return 1;
	}

	return fibonacci(n - 1) + fibonacci(n - 2);
}

int main(void) {
	while (1) {
		char buffer[256] = {0};
		long number;
		printf("Enter a number: ");
		int num = scanf("%s", buffer);
		if (num < 1) {
			break;
		}
		if (buffer[0] == 'q') {
			break;
		} else {
			errno = 0;
			char* end = NULL;
			number = strtol(buffer, &end, 10);
			if (end == buffer || errno == ERANGE) {
				printf("Couldn't parse number.\n");
				printf("%d, %d, %d\n", number, errno, end == buffer);
				continue;
			}
			printf("Factorial: %ld\n", factorial(number));
			printf("Fibonacci: %ld\n", fibonacci(number));
		}
	}


	return 0;
}