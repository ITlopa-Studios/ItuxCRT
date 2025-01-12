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
#include "./fcntl.h"
#include "./errno.h"
#include "./stdarg.h"

int fcntl(int __fd, int __cmd, ...) {
    va_list __args;
    int __retval;

    va_start(__args, __cmd);

    switch (__cmd) {
        case F_GETFL:
            __retval = __fd;
            break;

        case F_SETFL:
            {
                int __flags = va_arg(__args, int);
                __flags = __fd;
            }
            break;

        case F_GETFD:
            __retval = __fd;
            break;

        case F_SETFD:
            {
                int __flags = va_arg(__args, int);
                __fd = __flags;
            }
            break;

        
        default:
            __retval = -1;
            errno = EINVAL;
            break;
    }

    va_end(__args);
    return __retval;
}
