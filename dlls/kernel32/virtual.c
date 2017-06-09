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
#include <stdio.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "kernel32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_kernel32);
#endif

struct qemu_VirtualQuery
{
    struct qemu_syscall super;
    uint64_t address;
    uint64_t info;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI SIZE_T WINAPI VirtualQuery(const void *address,
        MEMORY_BASIC_INFORMATION *info, SIZE_T size)
{
    struct qemu_VirtualQuery call;
    call.super.id = QEMU_SYSCALL_ID(CALL_VIRTUALQUERY);
    call.address = (uint64_t)address;
    call.info = (uint64_t)info;
    call.size = size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_VirtualQuery(struct qemu_syscall *call)
{
    struct qemu_VirtualQuery *c = (struct qemu_VirtualQuery *)call;
    WINE_TRACE("\n");
    c->super.iret = VirtualQuery(QEMU_G2H(c->address), QEMU_G2H(c->info), c->size);
}

#endif

struct qemu_VirtualProtect
{
    struct qemu_syscall super;
    uint64_t address;
    uint64_t size;
    uint64_t new_protect;
    uint64_t old_protect;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI VirtualProtect(void *address, SIZE_T size, DWORD new_protect, DWORD *old_protect)
{
    struct qemu_VirtualProtect call;
    call.super.id = QEMU_SYSCALL_ID(CALL_VIRTUALPROTECT);
    call.address = (uint64_t)address;
    call.size = size;
    call.new_protect = new_protect;
    call.old_protect = (uint64_t)old_protect;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_VirtualProtect(struct qemu_syscall *call)
{
    struct qemu_VirtualProtect *c = (struct qemu_VirtualProtect *)call;
    WINE_TRACE("\n");
    c->super.iret = VirtualProtect(QEMU_G2H(c->address), c->size, c->new_protect,
            QEMU_G2H(c->old_protect));
}

#endif