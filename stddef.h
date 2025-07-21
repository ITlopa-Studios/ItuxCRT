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
#ifndef _STDDEF_
#define _STDDEF_ 1

#ifdef _FULLEND_
#include <sys/types.h>
#else
#include "./sys/types.h"
#endif

#ifndef NULL
#define NULL ((void *)0)
#endif

#endif
