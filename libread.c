// Copyright (c) 2025, London Sheard
// Licensed under the 3-Clause Sheard License
// See the LICENSE file in project root for details.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Reads a line from stdin into `string`.
 * Removes the trailing newline if present.
 *
 * Usage:
 * char buffer[1024];
 * if (read(buffer, sizeof(buffer))) {
 *     // use buffer
 * }
 * @param string Char array buffer to store input.
 * @param size Size of the buffer.
 * @return 1 on success, -1 on error.
 */
int read(char* string, const size_t size) {
    if (fgets(string, size, stdin) == NULL) {
        return -1;
    }
    const size_t len = strlen(string);

    if (len > 0 && string[len -1] == '\n') {
        string[len -1] = '\0';
    }
    return 1;
}

/**
 * Reads a line from stdin into a dynamically allocated buffer.
 * Removes the trailing newline if present.
 *
 * Usage:
 * char* buffer;
 * if (readm(&buffer)) {
 *     // use buffer
 *     free(buffer);
 * }
 * @warning MUST FREE
 * @param string Pointer to a char* that will hold the allocated string.
 * @return 1 on success, 0 on error.
 */
int readm(char** string) {
    size_t size = 128;
    size_t len = 0;
    char* buffer = malloc(size);
    if (!buffer) return 0;

    while (1) {
        if (fgets(buffer + len, size - len, stdin) == NULL) {
            free(buffer);
            return 0;
        }

        len += strlen(buffer + len);

        if (len > 0 && buffer[len - 1] == '\n') {
            len--;
            break;
        }
        size_t new_size = size * 2;
        char* new_buffer = realloc(buffer, new_size);
        if (!new_buffer) {
            free(buffer);
            return 0;
        }
        buffer = new_buffer;
        size = new_size;
    }
    char* final_str = realloc(buffer, len + 1);
    if (final_str) buffer = final_str;
    *string = buffer;
    return 1;

}
