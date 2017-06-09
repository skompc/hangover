/*
 * Copyright 2017 Stefan Dösinger for CodeWeavers
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

/* NOTE: The guest side uses mingw's headers. The host side uses Wine's headers. */

#include <windows.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "advapi32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_advapi32);
#endif

struct qemu_IsTextUnicode
{
    struct qemu_syscall super;
    uint64_t buf;
    uint64_t size;
    uint64_t result;
};

#ifdef QEMU_DLL_GUEST

WINADVAPI WINBOOL WINAPI IsTextUnicode(const void *buf, int size, int *result)
{
    struct qemu_IsTextUnicode call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISTEXTUNICODE);
    call.buf = (uint64_t)buf;
    call.size = size;
    call.result = (uint64_t)result;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IsTextUnicode(struct qemu_syscall *call)
{
    struct qemu_IsTextUnicode *c = (struct qemu_IsTextUnicode *)call;
    WINE_TRACE("\n");
    c->super.iret = IsTextUnicode(QEMU_G2H(c->buf), c->size, QEMU_G2H(c->result));
}

#endif