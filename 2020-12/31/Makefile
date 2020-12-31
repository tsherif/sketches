test-lazy: lazy
	./test-dlfcn-lazy

test-now: now
	./test-dlfcn-now

lazy: test-dlfcn-lazy.c libtest-lib
	gcc -g -o test-dlfcn-lazy test-dlfcn-lazy.c -ldl

now: test-dlfcn-now.c libtest-lib
	gcc -g -o test-dlfcn-now test-dlfcn-now.c -ldl

libtest-lib: test-lib.o
	gcc -g -shared -o libtest-lib.so test-lib.o

test-lib.o: test-lib.c
	gcc -c -fpic test-lib.c
