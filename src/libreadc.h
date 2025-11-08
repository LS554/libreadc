//
// Created by London Sheard on 21/07/25.
//

#ifndef LIBREAD_H
#define LIBREAD_H

#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>

int ReadLine(char* string, size_t size);

int ReadLinem(char** string);

int getch(void);

char* ReadFile(FILE* file, _Bool option);

char* ReadFilec(FILE* file, _Bool option);

char* Trim(char* string, unsigned int trim_len);

int FreeAll(int count, ...);

#endif //LIBREAD_H
