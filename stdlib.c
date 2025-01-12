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
#include "./stdlib.h"
#include <sys/wait.h>
#include <sys/stat.h>
#include "./unistd.h"
#include <ctype.h>
#include "./stdint.h"
#include <limits.h>

int system(const char *__command) {
    pid_t pid = fork();
    if (pid == 0) {
        // Child process
        execlp("/bin/sh", "sh", "-c", __command, (char *)NULL);
        _exit(127); // If exec fails
    } else if (pid < 0) {
        return -1; // Fork failed
    } else {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
        return status;
    }
}

int atoi(const char *__str) {
    int result = 0;
    int sign = 1;

    // Skip whitespace
    while (isspace(*__str)) {
        __str++;
    }

    // Handle optional sign
    if (*__str == '-') {
        sign = -1;
        __str++;
    } else if (*__str == '+') {
        __str++;
    }

    // Convert digits
    while (isdigit(*__str)) {
        result = result * 10 + (*__str - '0');
        __str++;
    }

    return sign * result;
}

double atof(const char *__str) {
    double result = 0.0;
    double factor = 1.0;
    int sign = 1;

    // Skip whitespace
    while (isspace(*__str)) {
        __str++;
    }

    // Handle optional sign
    if (*__str == '-') {
        sign = -1;
        __str++;
    } else if (*__str == '+') {
        __str++;
    }

    // Convert integer part
    while (isdigit(*__str)) {
        result = result * 10.0 + (*__str - '0');
        __str++;
    }

    // Handle decimal part
    if (*__str == '.') {
        __str++;
        while (isdigit(*__str)) {
            result = result * 10.0 + (*__str - '0');
            factor *= 10.0;
            __str++;
        }
    }

    return sign * result / factor;
}

long strtol(const char *__nptr, char **__endptr, int __base) {
    long __result = 0;
    int __sign = 1;

    // Skip whitespace
    while (isspace(*__nptr)) {
        __nptr++;
    }

    // Handle optional sign
    if (*__nptr == '-') {
        __sign = -1;
        __nptr++;
    } else if (*__nptr == '+') {
        __nptr++;
    }

    // Handle base prefix
    if (__base == 0) {
        if (*__nptr == '0') {
            if (*(__nptr + 1) == 'x' || *(__nptr + 1) == 'X') {
                __base = 16; // Hexadecimal
                __nptr += 2; // Skip "0x"
            } else {
                __base = 8; // Octal
                __nptr++; // Skip "0"
            }
        } else {
            __base = 10; // Decimal
        }
    }

    // Convert digits
    while (1) {
        int __digit = 0;
        if (*__nptr >= '0' && *__nptr <= '9') {
            __digit = *__nptr - '0';
        } else if (*__nptr >= 'a' && *__nptr <= 'f') {
            __digit = *__nptr - 'a' + 10;
        } else if (*__nptr >= 'A' && *__nptr <= 'F') {
            __digit = *__nptr - 'A' + 10;
        } else {
            break; // Stop on invalid character
        }

        if (__digit >= __base) {
            break; // Stop if digit is not valid for the base
        }

        // Check for overflow
        if (__result > (LONG_MAX - __digit) / __base) {
            __result = LONG_MAX; // Set to max value on overflow
            break;
        }

        __result = __result * __base + __digit; // Update result
        __nptr++;
    }

    // Set endptr to the next character
    if (__endptr) {
        *__endptr = (char *)__nptr;
    }

    return __sign * __result; // Return the result with the sign
}

// Define a static memory pool
#define MEMORY_POOL_SIZE 1024

static char memory_pool[MEMORY_POOL_SIZE]; // Static memory pool
static size_t allocated = 0; // Track allocated memory

// Structure to keep track of allocated blocks
typedef struct Block {
    size_t size; // Size of the block
    struct Block* next; // Pointer to the next block
} Block;

static Block* free_list = NULL; // Pointer to the free list

void* malloc(size_t __size) {
    if (__size == 0) {
        return NULL; // No allocation for size 0
    }

    // Align size to the nearest multiple of sizeof(Block)
    size_t __total_size = __size + sizeof(Block);
    if (allocated + __total_size > MEMORY_POOL_SIZE) {
        return NULL; // Not enough memory
    }

    // Check the free list for a suitable block
    Block* current = free_list;
    Block* previous = NULL;
    while (current) {
        if (current->size >= __total_size) {
            // Found a suitable block
            if (current->size > __total_size + sizeof(Block)) {
                // Split the block
                Block* new_block = (Block*)((char*)current + __total_size);
                new_block->size = current->size - __total_size;
                new_block->next = current->next;
                current->size = __size;
                current->next = new_block;
            } else {
                // Remove the block from the free list
                if (previous) {
                    previous->next = current->next;
                } else {
                    free_list = current->next;
                }
            }
            allocated += __total_size;
            return (char*)current + sizeof(Block); // Return pointer to the memory after the Block header
        }
        previous = current;
        current = current->next;
    }

    // If no suitable block was found, allocate from the memory pool
    Block* new_block = (Block*)&memory_pool[allocated];
    new_block->size = __size;
    new_block->next = NULL;
    allocated += __total_size;

    return (char*)new_block + sizeof(Block); // Return pointer to the memory after the Block header
}

void free(void* __ptr) {
    if (!__ptr) {
        return; // Do nothing for NULL pointer
    }

    // Get the block header
    Block* block = (Block*)((char*)__ptr - sizeof(Block));
    block->next = free_list; // Add the block to the free list
    free_list = block; // Update the free list
}

void exit(int __status)
{
    _exit(__status);
}