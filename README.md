# libread
 c library for user input

# Usage
readln - Reads a line from stdin into a preallocated buffer. Removes the trailing newline if present.
```
char buffer[1024];
if (readln(buffer, sizeof(buffer)) == 0) {
    // use buffer
}
```
readlnm - Reads a line from stdin into a dynamically allocated buffer (automatically resizes). Removes the trailing newline if present.
```
char* buffer = NULL;
if (readlnm(&buffer) == 0) {
    // use buffer
    free(buffer);
}
```
getch (implementation) - get character input without waiting for return
```
int ch = getch();
printf("%d", ch);
```
freeall - frees all provided pointers (takes count and pointers to pointers)
```
char* a = malloc(100);
char* b = malloc(100);
freeall(2, &a, &b);
```
## Compiling your programme
Download the library in [releases](https://github.com/LS554/libreadc/releases)
#### Using static library:
```
gcc main.c libreadc.a -o main
```
#### If installed system-wide: 
```
gcc main.c -lreadc -o main
```
### Manual:
Or just git clone the repo and link manually with the source:
```
gcc main.c libreadc.c -o main
```
