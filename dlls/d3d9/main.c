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
#include <d3d9.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_d3d9.h"

#ifdef QEMU_DLL_GUEST

BOOL WINAPI DllMain(HMODULE mod, DWORD reason, void *reserved)
{
    return TRUE;
}

#else

#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_d3d9);

const struct qemu_ops *qemu_ops;

static const syscall_handler dll_functions[] =
{
    qemu_d3d9_AddRef,
    qemu_d3d9_CheckDepthStencilMatch,
    qemu_d3d9_CheckDeviceFormat,
    qemu_d3d9_CheckDeviceFormatConversion,
    qemu_d3d9_CheckDeviceMultiSampleType,
    qemu_d3d9_CheckDeviceType,
    qemu_d3d9_CreateDevice,
    qemu_d3d9_CreateDeviceEx,
    qemu_d3d9_EnumAdapterModes,
    qemu_d3d9_EnumAdapterModesEx,
    qemu_d3d9_GetAdapterCount,
    qemu_d3d9_GetAdapterDisplayMode,
    qemu_d3d9_GetAdapterDisplayModeEx,
    qemu_d3d9_GetAdapterIdentifier,
    qemu_d3d9_GetAdapterLUID,
    qemu_d3d9_GetAdapterModeCount,
    qemu_d3d9_GetAdapterModeCountEx,
    qemu_d3d9_GetAdapterMonitor,
    qemu_d3d9_GetDeviceCaps,
    qemu_d3d9_QueryInterface,
    qemu_d3d9_RegisterSoftwareDevice,
    qemu_d3d9_Release,
    qemu_D3DPERF_BeginEvent,
    qemu_D3DPERF_EndEvent,
    qemu_D3DPERF_GetStatus,
    qemu_D3DPERF_QueryRepeatFrame,
    qemu_D3DPERF_SetMarker,
    qemu_D3DPERF_SetOptions,
    qemu_D3DPERF_SetRegion,
    qemu_DebugSetMute,
    qemu_Direct3DCreate9,
    qemu_Direct3DCreate9Ex,
    qemu_Direct3DShaderValidatorCreate9,
};

const WINAPI syscall_handler *qemu_dll_register(const struct qemu_ops *ops, uint32_t *dll_num)
{
    WINE_TRACE("Loading host-side d3d9 wrapper.\n");

    qemu_ops = ops;
    *dll_num = QEMU_CURRENT_DLL;

    return dll_functions;
}

#endif