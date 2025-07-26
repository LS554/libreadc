# libread
 c library for user input

# Usage
readln - Reads a line from stdin into `string`. Removes the trailing newline if present.
```
char buffer[1024];
if (readln(buffer, sizeof(buffer))) {
    // use buffer
}
```
readlnm - Reads a line from stdin into a dynamically allocated buffer `string`. Removes the trailing newline if present.
```
if (readlnm(&buffer)) {
    // use buffer
    free(buffer);
}
```
Compile your programme with:
```
gcc -lreadc ...
```
