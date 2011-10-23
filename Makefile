test2: test2.c
	clang -O0 -g test2.c -o test2

test: test.c
	clang -O0 -g test.c -o test
