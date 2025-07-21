//
// Created by london on 21/07/25.
//
#include <stdio.h>
#include <stdlib.h>
#include "libread.h"


int main() {
    char* buf;
    readm(&buf);
    printf("%s", buf);
    free(buf);

    char buf2[1024];
    read(buf2, sizeof(buf2));
    printf("%s", buf2);
}