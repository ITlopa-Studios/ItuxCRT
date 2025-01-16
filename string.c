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
#include "./errno.h"
#include "./stdlib.h"

size_t strlen(const char *__s) {
    if (__s == NULL) {
        errno = EINVAL; // Invalid argument
        return 0; // Return 0 for NULL pointer
    }

    size_t i = 0;
    while (__s[i] != '\0') {
        i++;
    }
    return i;
}

char* strdup(const char* __src) {
    if (__src == NULL) {
        errno = EINVAL; // Invalid argument
        return NULL; // Return NULL if source string is NULL
    }

    size_t __len = strlen(__src); // Get the length of the source string

    // Allocate memory for the new string (+1 for the null terminator)
    char* __dest = (char*)malloc(__len + 1);
    if (__dest == NULL) {
        errno = ENOMEM; // Set errno to indicate memory allocation failure
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
    if (__s1 == NULL || __s2 == NULL) {
        errno = EINVAL; // Invalid argument
        return 0; // Return 0 for NULL pointer comparison
    }

    while (*__s1 && (*__s1 == *__s2)) {
        __s1++;
        __s2++;
    }
    return *(unsigned char *)__s1 - *(unsigned char *)__s2;
}

/*
 * strchr - Locate the first occurrence of a character in a string.
 * @s: The string to search.
 * @c: The character to find.
 *
 * Return: A pointer to the first occurrence of the character in the string,
 *         or NULL if the character is not found.
 */
char* strchr(const char* __s, int __c) {
    if (__s == NULL) {
        errno = EINVAL; // Invalid argument
        return NULL; // Return NULL for NULL pointer
    }

    // Convert __c to char
    char ch = (char)__c;

    // Iterate through the string
    while (*__s != '\0') {
        if (*__s == ch) {
            return (char*)__s; // Return pointer to the found character
        }
        __s++;
    }

    // If we reach here, the character was not found
    return NULL;
}
