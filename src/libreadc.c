// Copyright (c) 2025, London Sheard
// Licensed under the 3-Clause Sheard License
// See the LICENSE file in project root for details.
//
// Created by London Sheard on 21/07/25.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <termios.h>
#include <unistd.h>

/**
 * Reads a line from stdin into `string`.
 * Removes the trailing newline if present, and flushes stdin.
 *
 * Usage:
 * char buffer[1024];
 * if (ReadLine(buffer, sizeof(buffer)) == 0) {
 *     // use buffer
 * }
 * @param string Char array buffer to store input.
 * @param size Size of the buffer.
 * @return 0 on success, 1 on error, -1 on overflow.
 */
int ReadLine(char* string, const size_t size) {
    if (fgets(string, size, stdin) == NULL) {
        return 1;
    }
    const size_t len = strlen(string);

    if (len > 0 && string[len -1] == '\n') {
        string[len -1] = '\0';
    } else {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF); // flush buffer to prevent overflow
        return -1;
    }
    return 0;
}

/**
 * Reads a line from stdin into a dynamically allocated buffer `string`.
 * Removes the trailing newline if present.
 *
 * Usage:
 * char* buffer;
 * if (ReadLinem(&buffer) == 0) {
 *     // use buffer
 *     free(buffer);
 * }
 * @warning MUST FREE
 * @param string Pointer to a char* that will hold the allocated string.
 * @return 0 on success, 1 on error.
 */
int ReadLinem(char** string) {
    size_t size = 128;
    size_t len = 0;
    char* buffer = malloc(size);
    if (!buffer)
        return 1;

    while (1) {
        // Read into the buffer starting at offset 'len'
        if (fgets(buffer + len, size - len, stdin) == NULL) {
            free(buffer);
            return 1;
        }
        
        // Determine length of the newly read chunk and update len.
        size_t chunk_len = strlen(buffer + len);
        len += chunk_len;

        // If the last character is newline, replace it with a null terminator and break.
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
            len--;
            break;
        }

        // If no newline, it means that the input line is longer than the available space.
        // Double the buffer size to read more.
        size_t new_size = size * 2;
        char* new_buffer = realloc(buffer, new_size);
        if (!new_buffer) {
            free(buffer);
            return 1;
        }
        buffer = new_buffer;
        size = new_size;
    }

    // Optionally, shrink the buffer to fit the string exactly.
    char* final_str = realloc(buffer, len + 1);
    if (final_str)
        buffer = final_str;
    *string = buffer;
    return 0;
}

/**
 * Getch (implementation).
 * Reads a single character from standard input without requiring a newline and without printing the character.
 *
 * Temporarily modifies the terminal attributes by disabling canonical mode (ICANON) and local echo (ECHO).
 * Restores the original terminal settings after reading.
 *
 * Usage:
 * int ci = getch();
 * char c = (char)ci;
 *
 * @return The character read as an int.
 */
int getch() {
    struct termios oldattr, newattr;

    // get term settings
    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;

    // disable line buffering
    newattr.c_lflag &= ~(ICANON | ECHO);

    // apply
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);

    int ch = getchar();

    // restore term
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);

    return ch;
}

/* get size of file -> f()read_file */
static long int GetSize(FILE* file) {
    fseek(file, 0, SEEK_END);
    const long int size = ftell(file);
    rewind(file);

    return size;
}

/**
 * Reads an entire file `file`, removes ending newline based on OPTION, and returns as char array.
 *
 * Usage:
 * FILE* file = fopen("filename", "r");
 * char* string = ReadFile(file);
 *
 * @warning free after use
 * @param file FILE* pointer to file stream.
 * @param option _Bool - cut or leave trailing newline
 * @return char* on success, NULL on error
 */
char* ReadFile(FILE* file, _Bool option) {
    long int fsize = GetSize(file);
    if (!fsize) {
        return NULL;
    }

    char* buffer = malloc(fsize +1);
    if (!buffer) {
        return NULL;
    }

    size_t cssize = fread(buffer, 1, fsize, file);
    if (!cssize) {
        return NULL;
    }
    if (cssize != fsize) {
        free(buffer);
        return NULL;
    }

    if (option == 1) {
	if (buffer[cssize -1] == '\n') {
	    buffer[cssize -1] = '\0';
	}
    }
    return buffer;
}

/**
 * Reads an entire file `file` as individual characters, removes ending newline based on OPTION, and returns as char array.
 *
 * Usage:
 * FILE* file = fopen("filename", "r");
 * char* string = ReadFilec(file);
 *
 * @warning free after use
 * @param file FILE* pointer to file stream.
 * @param option _Bool - cut or leave trailing newline
 * @return char* on success, NULL on error
 */
char* ReadFilec(FILE* file, _Bool option) {
    long int fsize = GetSize(file);
    if (!fsize) {
	return NULL;
    }

    char* buffer = malloc(fsize +1);
    if (!buffer) {
	return NULL;
    }

    int ci;
    for (long i = 0; i < fsize; i++) {
	ci = fgetc(file);
	if (ci == EOF) {
	    return NULL;
	}
	buffer[i] = (char)ci;
    }

    if (option == 1) {
	if (buffer[fsize -1] == '\n') {
	    buffer[fsize -1] = '\0';
	}
    }
    return buffer;
}


/**
 * Trims string to provided ending size.
 * Usage:
 * char* out = Trim(char* in, unsigned int trim_len);
 *
 * @param char* in - input string
 * @param option unsigned int trim_len - end length to leave
 * @return char* out on success; in on overflow
 */
char* Trim(char input[], size_t trim_size) {
    size_t old_len = strlen(input);
	if (trim_size > old_len) {trim_size = old_len;}
	
    char* new = malloc(trim_size + 1);

    for (size_t i = 0; i < trim_size; i++) {
        new[i] = input[old_len - trim_size + i];
    }

    new[trim_size] = '\0';

    return new;
}


/**
 * Frees and nulls all provided pointers.
 *
 * Usage:
 * char* a = malloc(100);
 * char* b = malloc(100);
 * FreeAll(2, &a, &b);
 * @param count Number of provided pointers.
 * @param ... pointers to pointers (e.g., &a, &b).
 * @return 0 on success, 1 on error.
 */
int FreeAll(const int count, ...) {
    va_list args;
    va_start(args, count);

    for (int i = 0; i < count; i++) {
        void **ptr = va_arg(args, void **);
        if (ptr && *ptr) {
            free(*ptr);
            *ptr = NULL;
        }
    }
    va_end(args);
    return 0;
}
