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
#ifndef _UNISTD_
#define _UNISTD_ 1

#ifdef _FULLEND_
#include <asm/unistd.h>
#include <fcntl.h>
#else
#include "./asm/unistd.h"
#include "./fcntl.h"
#endif

extern int open(const char *__path, int __flags, mode_t __mode);

extern int close(int __fd);

#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

extern ssize_t write(int __fd, const void *__str, size_t __bytes);

extern ssize_t read(int __fd, void *__str, size_t __bytes);

extern int execlp(const char*__file, const char*__arg, ...);

extern pid_t fork(void);

__ituxcrt_no_return void _exit(int __status);

#endif