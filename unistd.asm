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
%define SYS_READ    0
%define SYS_WRITE   1
%define SYS_OPEN    2
%define SYS_CLOSE   3
%define SYS_FORK    57
%define SYS_EXECVE  59

section .data
    errno dq 0          ; Global var for errno

section .text
    global open, close, write, read, fork, execlp

open:
    mov rax, SYS_OPEN
    syscall
    cmp rax, 0
    jge .done
    mov [errno], rax
    mov rax, -1
.done:
    ret

close:
    mov rax, SYS_CLOSE
    syscall
    ret

write:
    mov rax, SYS_WRITE
    syscall
    cmp rax, 0
    jge .done
    mov [errno], rax
.done:
    ret

read:
    mov rax, SYS_READ
    syscall
    ret

fork:
    mov rax, SYS_FORK
    syscall
    cmp rax, 0
    jge .done
    mov [errno], rax
.done:
    ret

execlp:
    push 0              ; NULL-terminate argv
    push rsi            ; arg0
    push rdi            ; filename
    mov rsi, rsp        ; argv = [filename, arg0, NULL]
    mov rax, SYS_EXECVE
    syscall
    add rsp, 24         ; Cleanup stack
    ret
