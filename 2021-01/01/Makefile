all: debug-lazy debug-now debug-aot

debug-lazy: lazy
	-LD_DEBUG=all ./test-dlfcn-lazy > debug-lazy.txt 2>&1

debug-now: now
	-LD_DEBUG=all ./test-dlfcn-now > debug-now.txt 2>&1

debug-aot: aot
	-LD_DEBUG=all LD_LIBRARY_PATH=$(LD_LIBRARY_PATH):. ./test-aot > debug-aot.txt 2>&1

test-lazy: lazy
	-./test-dlfcn-lazy

test-now: now
	-./test-dlfcn-now

test-aot: aot
	-LD_LIBRARY_PATH=$(LD_LIBRARY_PATH):. ./test-aot

lazy: test-dlfcn-lazy.c libtest-lib
	gcc -g -o test-dlfcn-lazy test-dlfcn-lazy.c -ldl

now: test-dlfcn-now.c libtest-lib
	gcc -g -o test-dlfcn-now test-dlfcn-now.c -ldl

aot: test-aot.c libtest-lib
	gcc -g -o test-aot test-aot.c -ltest-lib -L.

libtest-lib: test-lib.o
	gcc -g -shared -o libtest-lib.so test-lib.o -lm

test-lib.o: test-lib.c
	gcc -c -fpic test-lib.c
