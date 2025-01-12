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
#ifndef _SYS_TYPES
#define _SYS_TYPES 1

typedef int pid_t;

typedef unsigned int uid_t;

typedef unsigned int gid_t;

typedef unsigned int mode_t;

typedef long off_t;

typedef long ssize_t;

typedef unsigned long size_t;

typedef long time_t;

typedef unsigned long dev_t;

typedef unsigned long ino_t;

typedef unsigned short nlink_t;

typedef long blkcnt_t;

typedef long blksize_t;

#define __ituxcrt_no_return __attribute__((noreturn))

#endif