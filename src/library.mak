all:
	gcc -c libread.c -o libread.o
	ar rcs libread.a libread.o
	rm libread.o

	gcc -fPIC -c libread.c -o libread.o
	gcc -shared -o libread.so libread.o
	rm libread.o


static:
	gcc -c libread.c -o libread.o
	ar rcs libread.a libread.o
	rm libread.o

shared:
	gcc -fPIC -c libread.c -o libread.o
	gcc -shared -o libread.so libread.o
	rm libread.o
