/*
 * File     : mem_std.c
 * Brief    : implement standard memory routins.
 *
 * This file is part of Device File System in RT-Thread RTOS
 * COPYRIGHT (C) 2014, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE.
 *
 * Change Logs:
 * 2014-08-03     bernard      Add file header.
 */

#include <common.h>

void* malloc(size_t n)
{
	return _malloc(n);
}

void* realloc(void* rmem, size_t newsize)
{
	return _realloc(rmem, newsize);
}

void* calloc(size_t nelem, size_t elsize)
{
	return _calloc(nelem, elsize);
}

void free(void* rmem)
{
	_free(rmem);
}
