//
// Created by London Sheard on 21/07/25.
//
#include <stdio.h>
#include <stdlib.h>
#include "src/libreadc.h"

int main() {
    char buffer[1024];
    readln(buffer, sizeof(buffer));
    printf("%s\n", buffer);

    char* allocbuffer;
    readlnm(&allocbuffer);
    printf("%s", allocbuffer);
    free(allocbuffer);
    /* use after free!!! printf("%s", allocbuffer); */

    char* a = malloc(100);
    char* b = malloc(100);
    freeall(2, &a, &b);
}
