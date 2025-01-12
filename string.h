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
#ifndef _STRING_
#define _STRING_ 1

#ifdef _FULLEND_
#include <sys/types.h>
#else
#include "./sys/types.h"
#endif

size_t strlen(const char *__s);

char* strdup(const char* __src);

int strcmp(const char *__s1, const char *__s2);

#endif