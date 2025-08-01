//
// Created by London Sheard on 21/07/25.
//

#ifndef LIBREAD_H
#define LIBREAD_H

int readln(char* string, size_t size);

int readlnm(char** string);

int getch(void);

char* read_file(FILE* file, _Bool option);

char* read_filec(FILE* file, _Bool option);

int freeall(int count, ...);

#endif //LIBREAD_H
