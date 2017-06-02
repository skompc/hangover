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

#include <windows.h>
#include <stdio.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "kernel32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_kernel32);
#endif

struct qemu_GetModuleHandleA
{
    struct qemu_syscall super;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HMODULE WINAPI GetModuleHandleA(const char *name)
{
    struct qemu_GetModuleHandleA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETMODULEHANDLEA);
    call.name = (uint64_t)name;
    qemu_syscall(&call.super);
    return (HMODULE)call.super.iret;
}

#else

void qemu_GetModuleHandleA(struct qemu_syscall *call)
{
    struct qemu_GetModuleHandleA *c = (struct qemu_GetModuleHandleA *)call;
    WINE_TRACE("(\"%s\")\n", (char *)QEMU_G2H(c->name));

    c->super.iret = (uint64_t)qemu_ops->qemu_GetModuleHandleEx(
            GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, QEMU_G2H(c->name));
    WINE_TRACE("Returning %p\n", (void *)c->super.iret);
}

#endif

struct qemu_GetModuleHandleExA
{
    struct qemu_syscall super;
    DWORD flags;
    uint64_t name, module;
};
#ifdef QEMU_DLL_GUEST

WINBASEAPI WINBOOL WINAPI GetModuleHandleExA(DWORD flags, const char *name, HMODULE *module)
{
    struct qemu_GetModuleHandleExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETMODULEHANDLEEXA);
    call.flags = flags;
    call.name = (uint64_t)name;

    qemu_syscall(&call.super);

    *module = (HMODULE)call.module;
    return call.super.iret;
}

#else

void qemu_GetModuleHandleExA(struct qemu_syscall *call)
{
    struct qemu_GetModuleHandleExA *c = (struct qemu_GetModuleHandleExA *)call;
    HANDLE m;
    WINE_TRACE("\n");

    m = qemu_ops->qemu_GetModuleHandleEx(c->flags, QEMU_G2H(c->name));

    c->super.iret = !!m;
    c->module = (uint64_t)m;
}

#endif

struct qemu_GetProcAddress
{
    struct qemu_syscall super;
    uint64_t module, name;
};
#ifdef QEMU_DLL_GUEST

WINBASEAPI FARPROC WINAPI GetProcAddress(HMODULE module, const char *name)
{
    struct qemu_GetProcAddress call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETPROCADDRESS);
    call.module = (uint64_t)module;
    call.name = (uint64_t)name;

    qemu_syscall(&call.super);

    return (FARPROC)call.super.iret;
}

#else

void qemu_GetProcAddress(struct qemu_syscall *call)
{
    struct qemu_GetProcAddress *c = (struct qemu_GetProcAddress *)call;
    WINE_TRACE("\n");

    c->super.iret = (uint64_t)qemu_ops->qemu_GetProcAddress((HMODULE)c->module,
            QEMU_G2H(c->name));
}

#endif