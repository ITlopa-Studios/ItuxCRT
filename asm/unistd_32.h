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
#ifndef _ASM_UNISTD_32_
#define _ASM_UNISTD_32_ 1

#define __NR_read        3
#define __NR_write       4
#define __NR_open        5
#define __NR_close       6
#define __NR_stat        106
#define __NR_fstat       108
#define __NR_lstat       107
#define __NR_poll        168
#define __NR_lseek       19
#define __NR_mmap        90
#define __NR_munmap      91
#define __NR_brk         45
#define __NR_rt_sigaction 198
#define __NR_rt_sigprocmask 199
#define __NR_rt_sigreturn 200
#define __NR_ioctl       54
#define __NR_getpid      20
#define __NR_fork        2
#define __NR_execve      11
#define __NR_exit        1

#endif