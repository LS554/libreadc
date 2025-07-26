# libread
 c library for user input

# Usage
readln - Reads a line from stdin into `string`. Removes the trailing newline if present.
```
char buffer[1024];
if (readln(buffer, sizeof(buffer)) == 0) {
    // use buffer
}
```
readlnm - Reads a line from stdin into a dynamically allocated buffer `string`. Removes the trailing newline if present.
```
if (readlnm(&buffer) == 0) {
    // use buffer
    free(buffer);
}
```
## Compiling your programme
#### Using static library:
```
gcc main.c libreadc.a -o main
```
#### If installed system-wide: 
```
gcc main.c -lreadc -o main
```
