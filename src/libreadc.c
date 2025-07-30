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
 * Removes the trailing newline if present.
 *
 * Usage:
 * char buffer[1024];
 * if (readln(buffer, sizeof(buffer)) == 0) {
 *     // use buffer
 * }
 * @param string Char array buffer to store input.
 * @param size Size of the buffer.
 * @return 0 on success, 1 on error, -1 on overflow.
 */
int readln(char* string, const size_t size) {
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
 * if (readlnm(&buffer) == 0) {
 *     // use buffer
 *     free(buffer);
 * }
 * @warning MUST FREE
 * @param string Pointer to a char* that will hold the allocated string.
 * @return 0 on success, 1 on error.
 */
int readlnm(char** string) {
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
 * Reads a single character from standard input without requiring a newline and without printing the character.
 *
 * Temporarily modifies the terminal attributes by disabling canonical mode (ICANON) and local echo (ECHO).
 * Restores the original terminal settings after reading.
 *
 * Usage:
 * int ci = getch();
 * char c = (char)ci;
 *
 * @return The character read as an int, or EOF on error.
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
static long int get_size(FILE* file) {
    fseek(file, 0, SEEK_END);
    const long int size = ftell(file);
    rewind(file);

    return size;
}

/**
 * Reads an entire file `file`, removes ending newline, and returns as char array.
 *
 * Usage:
 * FILE* file = fopen("filename", "r");
 * char* string = read_file(file);
 *
 * @warning free after use
 * @param file FILE* pointer to file stream.
 * @param option boolean - cut or leave trailing newline
 * @return char* on success, NULL on error
 */
char* read_file(FILE* file, _Bool option) {
    long int size = get_size(file);
    if (!size) {
        return NULL;
    }
    if (size == -1) {
        return NULL;
    }

    char* buffer = malloc(size +1);
    if (!buffer) {
        return NULL;
    }

    size_t read = fread(buffer, 1, size, file);
    if (!read) {
        return NULL;
    }
    if (read != size) {
        free(buffer);
        return NULL;
    }

    size_t len = strlen(buffer);
    if (option == 1) {
        if (buffer[len -1] == '\n') {
            buffer[len -1] = '\0';
        }
    }

    return buffer;
}


/**
 * Frees all provided pointers (sets them to NULL after freeing)
 *
 * Usage:
 * char* a = malloc(100);
 * char* b = malloc(100);
 * freeall(2, &a, &b);
 * @param count Number of provided pointers.
 * @param ... pointers to pointers (e.g., &a, &b).
 * @return 0 on success, 1 on error.
 */
int freeall(const int count, ...) {
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
