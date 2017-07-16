/*
 * Copyright 2017 André Hentschel
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
#include "comdlg32.h"

#ifdef QEMU_DLL_GUEST

BOOL WINAPI DllMain(HMODULE mod, DWORD reason, void *reserved)
{
    return TRUE;
}

#else

#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_comdlg32);

const struct qemu_ops *qemu_ops;

static const syscall_handler dll_functions[] =
{
    qemu_ChooseFontA,
    qemu_ChooseFontW,
    qemu_FindTextA,
    qemu_FindTextW,
    qemu_GetFileTitleA,
    qemu_GetFileTitleW,
    qemu_GetOpenSaveFileName,
    qemu_GetOpenSaveFileName,
    qemu_GetOpenSaveFileName,
    qemu_GetOpenSaveFileName,
    qemu_PageSetupDlgA,
    qemu_PageSetupDlgW,
    qemu_PrintDlgA,
    qemu_PrintDlgExA,
    qemu_PrintDlgExW,
    qemu_PrintDlgW,
    qemu_ReplaceTextA,
    qemu_ReplaceTextW,
};

const WINAPI syscall_handler *qemu_dll_register(const struct qemu_ops *ops, uint32_t *dll_num)
{
    WINE_TRACE("Loading host-side comdlg32 wrapper.\n");

    qemu_ops = ops;
    *dll_num = QEMU_CURRENT_DLL;

    comdlg32_tls = TlsAlloc();
    if (comdlg32_tls == TLS_OUT_OF_INDEXES)
        WINE_ERR("Out of TLS indices\n");

    return dll_functions;
}

#endif