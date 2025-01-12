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
#include "./unistd.h"
#include "./stdbool.h"

__ituxcrt_no_return void _exit(int __status) {
    asm volatile (
        "mov %0, %%rdi\n"  // Move the exit status into rdi (1st argument for syscall)
        "mov $60, %%rax\n" // Syscall number for exit (60 on x86_64)
        "syscall"          // Invoke the syscall
        :
        : "r"((long)__status) // Input: status cast to long
        : "%rax", "%rdi"   // Clobbered registers
    );

    while (true) {

    }
}
