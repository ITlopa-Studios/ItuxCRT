/*
 * Copyright (C) 2025 ITlopa
 *
 * This file is part of ItuxCRT.
 *
 * ItuxCRT is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * ItuxCRT is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 */

#include "./stdio.h"
#include "./stdlib.h"
#include "./unistd.h"
#include "./string.h"
#include "./errno.h"

// Standard input, output, and error streams
FILE stdin_stream = {.fd = 0};
FILE stdout_stream = {.fd = 1};
FILE stderr_stream = {.fd = 2};

FILE *stdin = &stdin_stream;
FILE *stdout = &stdout_stream;
FILE *stderr = &stderr_stream;

/**
 * Get the open flags based on the mode string.
 * 
 * @param __mode The mode string (e.g., "r", "w", "a").
 * @return The flags to be used with the open() system call.
 */
int get_open_flags(const char *__mode) {
    int flags = 0;

    if (strchr(__mode, 'r')) {
        flags |= O_RDONLY; // Read-only
    }
    if (strchr(__mode, 'w')) {
        flags |= O_WRONLY | O_CREAT | O_TRUNC; // Write, create, truncate
    }
    if (strchr(__mode, 'a')) {
        flags |= O_WRONLY | O_CREAT | O_APPEND; // Append, create
    }

    return flags;
}

/**
 * Open a file with the specified path and mode.
 * 
 * @param __path The path to the file.
 * @param __mode The mode in which to open the file.
 * @return A pointer to the FILE structure, or NULL on failure.
 */
FILE *fopen(const char* __path, const char *__mode) {
    FILE *result = (FILE*)malloc(sizeof(FILE));
    if (result == NULL) {
        errno = ENOMEM; // Set errno for memory allocation failure
        return NULL;
    }

    // Get the flags based on the mode
    int flags = get_open_flags(__mode);
    
    // Open the file
    result->fd = open(__path, flags, 0644); // 0644 is the file permission
    if (result->fd == -1) {
        free(result); // Free allocated memory on failure
        return NULL; // Handle file open failure
    }

    // Duplicate the mode string
    result->mode = strdup(__mode);
    if (result->mode == NULL) {
        close(result->fd); // Close the file descriptor on failure
        free(result); // Free allocated memory
        errno = ENOMEM; // Set errno for memory allocation failure
        return NULL;
    }

    return result; // Return the FILE pointer
}

/**
 * Close a file stream.
 * 
 * @param __stream The file stream to close.
 * @return 0 on success, -1 on failure.
 */
int fclose(FILE *__stream) {
    if (__stream != NULL) {
        close(__stream->fd);
        free(__stream);
        return 0;
    } else {
        errno = EINVAL; // Set errno for invalid argument
        return -1;
    }
}

/**
 * Write data to a file stream.
 * 
 * @param __ptr Pointer to the data to write.
 * @param __size Size of each element to write.
 * @param __count Number of elements to write.
 * @param __stream The file stream to write to.
 * @return The number of elements successfully written, or 0 on error.
 */
size_t fwrite(const void *__ptr, size_t __size, size_t __count, FILE *__stream) {
    if (__stream == NULL || __ptr == NULL || __size == 0 || __count == 0) {
        errno = EINVAL; // Set errno for invalid argument
        return 0; // Return 0 if invalid parameters
    }

    // Calculate the total number of bytes to write
    size_t __total_bytes = __size * __count;
    ssize_t __bytes_written = write(__stream->fd, __ptr, __total_bytes);

    // Check for errors
    if (__bytes_written < 0) {
        errno = EIO; // Set errno for I/O error
        return 0; // Return 0 on error
    }

    return __bytes_written / __size; // Return the number of elements written
}

/**
 * Read data from a file stream.
 * 
 * @param __ptr Pointer to the buffer where the read data will be stored.
 * @param __size Size of each element to read.
 * @param __count Number of elements to read.
 * @param __stream The file stream to read from.
 * @return The number of elements successfully read, or 0 on error.
 */
size_t fread(void *__ptr, size_t __size, size_t __count, FILE *__stream) {
    if (__stream == NULL || __ptr == NULL || __size == 0 || __count == 0) {
        errno = EINVAL; // Set errno for invalid argument
        return 0; // Return 0 if invalid parameters
    }

    // Calculate the total number of bytes to read
    size_t __total_bytes = __size * __count;
    ssize_t __bytes_read = read(__stream->fd, __ptr, __total_bytes);

    // Check for errors
    if (__bytes_read < 0) {
        errno = EIO; // Set errno for I/O error
        return 0; // Return 0 on error
    }

    return __bytes_read / __size; // Return the number of elements read
}

/**
 * Write a character to a file stream.
 * 
 * @param __c The character to write.
 * @param __stream The file stream to write to.
 * @return The character written, or EOF on error.
 */
int fputc(int __c, FILE *__stream) {
    unsigned char __char = (unsigned char)__c; // Convert to unsigned char

    // Write the character to the file
    ssize_t result = write(__stream->fd, &__char, 1);

    // Check for errors
    if (result < 0) {
        errno = EIO; // Set errno for I/O error
        return EOF; // Return EOF on error
    }

    return __c; // Return the character written
}

int putc(int __c, FILE *__stream)
{
    return fputc(__c, __stream);
}

int putchar(int __c)
{
    return putc(__c, stdout);
}

/**
 * Format a string and store it in a buffer.
 * 
 * @param __str The buffer to store the formatted string.
 * @param __size The size of the buffer.
 * @param __format The format string.
 * @param __args The variable argument list.
 * @return The number of characters written, or a negative value on error.
 */
int vsnprintf(char *__str, size_t __size, const char *__format, va_list __args) {
    char *__p;
    int __written = 0;

    for (__p = (char *)__format; *__p != '\0' && __written < __size - 1; __p++) {
        if (*__p == '%') {
            __p++; // Move to the next character after '%'
            if (*__p == 'd') { // Integer
                int __value = va_arg(__args, int);
                char __buffer[20]; // Buffer to hold the string representation
                int __i = 0, __is_negative = 0;

                if (__value < 0) {
                    __is_negative = 1;
                    __value = -__value;
                }

                do {
                    __buffer[__i++] = (__value % 10) + '0';
                    __value /= 10;
                } while (__value > 0);

                if (__is_negative) {
                    __buffer[__i++] = '-';
                }

                // Reverse the string in buffer
                for (int __j = 0; __j < __i / 2; __j++) {
                    char __temp = __buffer[__j];
                    __buffer[__j] = __buffer[__i - __j - 1];
                    __buffer[__i - __j - 1] = __temp;
                }

                // Copy to output string
                for (int __j = 0; __j < __i && __written < __size - 1; __j++) {
                    __str[__written++] = __buffer[__j];
                }
            } else if (*__p == 's') { // String
                char *__value = va_arg(__args, char *);
                while (*__value && __written < __size - 1) {
                    __str[__written++] = *__value++;
                }
            } else if (*__p == 'c') { // Character
                char __value = (char)va_arg(__args, int);
                if (__written < __size - 1) {
                    __str[__written++] = __value;
                }
            } else if (*__p == '%') { // "%" character
                if (__written < __size - 1) {
                    __str[__written++] = '%';
                }
        } else {
            if (__written < __size - 1) {
                __str[__written++] = *__p; // Copy regular characters
            }
        }
    }
    __str[__written] = '\0'; // Null-terminate the string
    return __written; // Return the number of characters written
}

/**
 * Read formatted input from a string.
 * 
 * @param __str The input string to read from.
 * @param __size The maximum number of characters to read.
 * @param __format The format string.
 * @param __args The variable argument list.
 * @return The number of items successfully read, or -1 on error.
 */
int vsnscanf(const char *__str, size_t __size, const char *__format, va_list __args) {
    const char *__p = __format;
    int __count = 0;

    while (*__p != '\0' && __size > 0) {
        if (*__p == '%') {
            __p++; // Move to the next character after '%'
            if (*__p == 'd') { // Integer
                int *__value = va_arg(__args, int *);
                int __num = 0, __sign = 1;

                // Skip whitespace
                while (*__str == ' ' && __size > 0) {
                    __str++;
                    __size--;
                }

                if (*__str == '-') {
                    __sign = -1;
                    __str++;
                    __size--;
                } else if (*__str == '+') {
                    __str++;
                    __size--;
                }

                // Read digits
                while (*__str >= '0' && *__str <= '9' && __size > 0) {
                    __num = __num * 10 + (*__str - '0');
                    __str++;
                    __size--;
                }

                *(__value) = __num * __sign; // Store the result
                __count++;
            } else if (*__p == 's') { // String
                char *__value = va_arg(__args, char *);
                // Skip whitespace
                while (*__str == ' ' && __size > 0) {
                    __str++;
                    __size--;
                }
                // Read characters until whitespace or end of string
                while (*__str != ' ' && *__str != '\0' && __size > 0) {
                    *__value++ = *__str++;
                    __size--;
                }
                *__value = '\0'; // Null-terminate the string
                __count++;
            } else if (*__p == 'c') { // Character
                char *__value = va_arg(__args, char *);
                // Skip whitespace
                while (*__str == ' ' && __size > 0) {
                    __str++;
                    __size--;
                }
                if (__size > 0 && *__str != '\0') {
                    *__value = *__str; // Read the character
                    __count++;
                    __str++; // Move to the next character
                    __size--; // Decrease size
                }
            }
        } else {
            // Skip non-format characters
            if (*__str == *__p) {
                __str++;
                __size--;
            }
        }
        __p++;
    }
    return __count; // Return the number of items successfully read
}

int vsprintf(char *__str, const char *__format, va_list __args)
{
    size_t bufsize = 6024;
    return vsnprintf(__str, bufsize, __format, __args);
}

int vsscanf(const char *__str, const char *__format, va_list __args)
{
    size_t bufsize = 6024;
    return vsnscanf(__str, bufsize, __format, __args);
}

int snprintf(char *__str, size_t __size, const char *__format, ...)
{
    int result;
    va_list args;
    va_start(args, __format);
    result = vsnprintf(__str, __size, __format, args);
    va_end(args);
    return result;
}

int snscanf(const char *__str, size_t __size, const char *__format, ...)
{
    int result;
    va_list args;
    va_start(args, __format);
    result = vsnscanf(__str, __size, __format, args);
    va_end(args);
    return result;
}

int sprintf(char *__str, const char *__format, ...)
{
    int result;
    va_list args;
    va_start(args, __format);
    result = vsprintf(__str, __format, args);
    va_end(args);
    return result;
}

int sscanf(const char *__str, const char *__format, ...)
{
    int result;
    va_list args;
    va_start(args, __format);
    result = vsscanf(__str, __format, args);
    va_end(args);
    return result;
}

/**
 * Write formatted output to a file stream.
 * 
 * @param __stream The file stream to write to.
 * @param __format The format string.
 * @param __args The variable argument list.
 * @return The number of characters written, or -1 on error.
 */
int vfprintf(FILE *__stream, const char *__format, va_list __args) {
    char buf[6024]; // Buffer for formatted output
    int len = vsnprintf(buf, sizeof(buf), __format, __args); // Format the string

    if (len < 0) {
        errno = EINVAL; // Set errno for invalid argument
        return -1; // Return -1 on error from vsnprintf
    }

    // Write the formatted string to the output stream
    for (int i = 0; i < len; i++) {
        if (fputc(buf[i], __stream) == EOF) {
            errno = EIO; // Set errno for I/O error
            return -1; // Return -1 on error from fputc
        }
    }

    return len; // Return the number of characters written
}

int fprintf(FILE *__stream, const char *__format, ...)
{
    int result;
    va_list args;
    va_start(args, __format);
    result = vfprintf(__stream, __format, args);
    va_end(args);
    return result;
}

int vprintf(const char* __format, va_list __args)
{
    return vfprintf(stdout, __format, __args);
}

int printf(const char *__format, ...)
{
    int result;
    va_list args;
    va_start(args, __format);
    result = vfprintf(stdout, __format, args);
    va_end(args);
    return result;
}

/**
 * Read formatted input from a file stream.
 * 
 * @param __stream The file stream to read from.
 * @param __format The format string.
 * @param __args The variable argument list.
 * @return The number of items successfully read, or -1 on error.
 */
int vfscanf(FILE *__stream, const char *__format, va_list __args) {
    char buf[6024];
    ssize_t bytesRead = read(__stream->fd, buf, sizeof(buf) - 1); // Read from the stream

    if (bytesRead < 0) {
        errno = EIO; // Set errno for read error
        return -1; // Return -1 on read error
    }

    buf[bytesRead] = '\0'; // Null-terminate the buffer

    // Use vsnscanf to parse the input from the buffer
    int len = vsnscanf(buf, sizeof(buf), __format, __args);

    return len; // Return the number of items successfully read
}

int fscanf(FILE *__stream, const char *__format, ...)
{
    int result;
    va_list args;
    va_start(args, __format);
    result = vfscanf(__stream, __format, args);
    va_end(args);
    return result;
}

int vscanf(const char *__format, va_list __args)
{
    return vfscanf(stdin, __format, __args);
}

int scanf(const char *__format, ...)
{
    int result;
    va_list args;
    va_start(args, __format);
    result = vfscanf(stdin, __format, args);
    va_end(args);
    return result;
}

void perror(const char *__s)
{
    if (__s != NULL) {
        fprintf(stderr, "%s: ", __s);
    }
    fprintf(stderr, "%s\n", strerror(errno));
}

int fgetc(FILE *__stream) {
    if (__stream == NULL) {
        errno = EINVAL;
        return EOF;
    }

    char c;
    ssize_t result = read(__stream->fd, &c, 1);

    if (result < 0) {
        errno = EIO;
        return EOF;
    } else if (result == 0) {
        return EOF;
    }

    return (unsigned char)c;
}

int getc(FILE *__stream)
{
    return fgetc(__stream);
}

int getchar()
{
    return getc(stdin);
}
