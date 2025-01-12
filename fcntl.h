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
#ifndef _FCNTL_
#define _FCNTL_ 1

#ifdef _FULLEND_
#include <sys/types.h>
#else
#include "./sys/types.h"
#endif

#define O_RDONLY    00
#define O_WRONLY    01
#define O_RDWR      02
#define O_NONBLOCK  04000
#define O_APPEND    02000
#define O_CREAT     01000
#define O_TRUNC     02000

#define F_GETFL     3
#define F_SETFL     4
#define F_GETFD     1
#define F_SETFD     2

struct flock {
    short l_type;
    short l_whence;
    off_t l_start;
    off_t l_len;
    pid_t l_pid;
};

int fcntl(int __fd, int __cmd, ... /* arg */ );

#endif