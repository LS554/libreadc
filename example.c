//
// Created by London Sheard on 21/07/25.
//
#include <stdio.h>
#include <stdlib.h>
#include "src/libreadc.h"

int main() {
    /* readln example */
    puts("Enter string: ");
    char buffer[1024];
    readln(buffer, sizeof(buffer));
    printf("%s\n", buffer);

    /* readlnm example */
    puts("Enter another string: ");
    char* allocbuffer;
    readlnm(&allocbuffer);
    printf("%s\n", allocbuffer);

    /* freeall example */
    char* a = malloc(100);
    char* b = malloc(100);
    freeall(3, &allocbuffer, &a, &b);

    /* getch example */
    puts("Press a key: ");
    int ch = getch();
    printf("%d", ch);
}
