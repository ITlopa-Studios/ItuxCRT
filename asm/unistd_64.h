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
#ifndef _ASM_UNISTD_64_
#define _ASM_UNISTD_64_ 1

#define __NR_read          0
#define __NR_write         1
#define __NR_open          2
#define __NR_close         3
#define __NR_stat          4
#define __NR_fstat         5
#define __NR_lstat         6
#define __NR_poll          7
#define __NR_lseek         8
#define __NR_mmap          9
#define __NR_munmap        10
#define __NR_brk           12
#define __NR_rt_sigaction  13
#define __NR_rt_sigprocmask 14
#define __NR_rt_sigreturn  15
#define __NR_ioctl         16
#define __NR_getpid        20
#define __NR_fork          57
#define __NR_execve        59
#define __NR_exit          60

#endif