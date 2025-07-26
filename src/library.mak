all:
	gcc -c libreadc.c -o libreadc.o
	ar rcs libreadc.a libreadc.o
	rm libreadc.o

	gcc -fPIC -c libreadc.c -o libreadc.o
	gcc -shared -o libreadc.so libreadc.o
	rm libreadc.o


static:
	gcc -c libreadc.c -o libreadc.o
	ar rcs libreadc.a libreadc.o
	rm libreadc.o

shared:
	gcc -fPIC -c libreadc.c -o libreadc.o
	gcc -shared -o libreadc.so libreadc.o
	rm libreadc.o
