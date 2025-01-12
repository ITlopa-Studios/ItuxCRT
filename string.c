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
#include "./string.h"
#include "./stddef.h"

size_t strlen(const char *__s)
{
    int i = 0;
    while (__s[i] != '\0') {
        i++;
    }
    return i;
}

char* strdup(const char* __src) {
    size_t __len = strlen(__src); // Get the length of the source string

    // Allocate memory for the new string (+1 for the null terminator)
    char* __dest = (char*)malloc(__len + 1);
    if (__dest == NULL) {
        return NULL; // Return NULL if memory allocation fails
    }

    // Copy the string
    for (size_t i = 0; i < __len; i++) {
        __dest[i] = __src[i]; // Copy the string
    }
    __dest[__len] = '\0'; // Null-terminate the new string

    return __dest; // Return the pointer to the new string
}

int strcmp(const char *__s1, const char *__s2) {
    while (*__s1 && (*__s1 == *__s2)) {
        __s1++;
        __s2++;
    }
    return *(unsigned char *)__s1 - *(unsigned char *)__s2;
}
