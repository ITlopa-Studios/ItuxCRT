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
#ifndef _STDLIB_
#define _STDLIB_ 1

#ifdef _FULLEND_
#include <stddef.h>
#include <sys/types.h>
#else
#include "./stddef.h"
#include "./sys/types.h"
#endif

int system(const char *__command);

int atoi(const char *__str);

double atof(const char *__str);

long strtol(const char *__nptr, char **__endptr, int __base);

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

void* malloc(size_t __size);

void free(void* __ptr);

void exit(int __status);

#endif
