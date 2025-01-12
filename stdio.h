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
#ifndef _STDIO_
#define _STDIO_ 1

#ifdef _FULLEND_
#include <sys/types.h>
#include <stdarg.h>
#else
#include "./sys/types.h"
#include "./stdarg.h"
#endif

#define EOF (-1)

typedef struct _iobuf {
    int fd;
    const char *mode
} FILE;

extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;

#define stdin stdin
#define stdout stdout
#define stderr stderr

FILE *fopen(const char* __path, const char *__mode);

int fclose(FILE *__stream);

size_t fwrite(const void *__ptr, size_t __size, size_t __count, FILE *__stream);

size_t fread(void *__ptr, size_t __size, size_t __count, FILE *__stream);

int fputc(int __c, FILE *__stream);

int putc(int __c, FILE *__stream);

int putchar(int __c);

int vsnprintf(char *__str, size_t __size, const char *__format, va_list __args);

int vsnscanf(const char *__str, size_t __size, const char *__format, va_list __args);

int vsprintf(char *__str, const char *__format, va_list __args);

int vsscanf(const char *__str, const char *__format, va_list __args);

int snprintf(char *__str, size_t __size, const char *__format, ...);

int snscanf(const char *__str, size_t __size, const char *__format, ...);

int sprintf(char *__str, const char *__format, ...);

int sscanf(const char *__str, const char *__format, ...);

int vfprintf(FILE *__stream, const char *__format, va_list __args);

int fprintf(FILE *__stream, const char *__format, ...);

int vprintf(const char* __format, va_list __args);

int printf(const char *__format, ...);

int vfscanf(FILE *__stream, const char *__format, va_list __args);

int fscanf(FILE *__stream, const char *__format, ...);

int vscanf(const char *__format, va_list __args);

int scanf(const char *__format, ...);

void perror(const char *__s);

#endif