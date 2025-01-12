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
#ifndef _STDARG_
#define _STDARG_ 1

typedef struct __va_list_tag __ituxcrt_va_list[1];

typedef __ituxcrt_va_list va_list;

#define va_start(ap, x) __builtin_va_start(ap, x)

#define va_arg(ap, t) __builtin_va_arg(ap, t)

#define va_copy(ap1, ap2) __builtin_va_copy(ap1, ap2)

#define va_end(ap) __builtin_va_end(ap)

#endif
