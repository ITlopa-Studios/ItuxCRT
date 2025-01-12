; Copyright (C) 2025 ITlopa
;
; This file is part of ItuxCRT.
;
; ItuxCRT is free software; you can redistribute it and/or modify
; it under the terms of the GNU Lesser General Public License as published by
; the Free Software Foundation; either version 2.1 of the License, or
; (at your option) any later version.
;
; ItuxCRT is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
; GNU Lesser General Public License for more details.
section .data
    filename db 'test.txt', 0          ; Standard filename
    msg db 'Hello, World!', 13          ; Standard message

section .text
    global open
    global close
    global write
    global read
    global fork
    global execlp

; int open(const char *__path, int __flags, mode_t __mode);
open:
    mov rax, 2          ; syscall: open
    syscall             ; invoke syscall
    ret

; int close(int __fd);
close:
    mov rax, 3          ; syscall: close
    syscall             ; invoke syscall
    ret

; ssize_t write(int __fd, const void *__str, size_t __bytes);
write:
    ; rdi - file descriptor (0, 1, or 2)
    ; rsi - message pointer
    ; rdx - number of bytes
    mov rax, 1          ; syscall: write
    syscall             ; invoke syscall
    ret

; ssize_t read(int __fd, void *__str, size_t __bytes);
read:
    ; rdi - file descriptor (0 for stdin)
    ; rsi - buffer pointer
    ; rdx - number of bytes
    mov rax, 0          ; syscall: read
    syscall             ; invoke syscall
    ret

; pid_t fork(void);
fork:
    mov rax, 57         ; syscall: fork
    syscall             ; invoke syscall
    ret

; int execlp(const char *__file, const char *__arg, ...);
execlp:
    ; rdi - file
    ; rsi - first argument
    ; rdx - other arguments

    ; Prepare arguments for execve
    push rdi            ; Save pointer to the file
    mov rax, 0          ; Argument count
    mov rsi, rsp        ; Pointer to the stack (where arguments are)

    ; Prepare the argument array
    mov rdi, rsp        ; Pointer to the stack
    xor rdx, rdx        ; Pointer to the environment array (NULL)

    ; Terminate the argument array with NULL
    push rdx            ; Add NULL to the end of the argument array
    push rsi            ; Add the first argument
    push rdi            ; Add the filename

    mov rax, 59         ; syscall: execve
    syscall             ; invoke syscall
    ret