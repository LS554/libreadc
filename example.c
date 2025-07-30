//
// Created by London Sheard on 21/07/25.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "src/libreadc.h"

int main(int argc, char** argv) {
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
    int ci = getch();
    char c = (char)ci;
    printf("%c\n", c);

    if (argc != 2) {
        fprintf(stderr, "Not enough arguments -> read_file example\n");
        return 1;
    }

    FILE* file = fopen(argv[1], "r");
    if (!file) {
        char errormsg[256];
        snprintf(errormsg, sizeof errormsg, "Could not read file `%s`", argv[1]);
        perror(errormsg);
        return 1;
    }
    char* string = read_file(file, 1);
    printf("%s : %s : %ld bytes\n", argv[1], string, strlen(string));
}
